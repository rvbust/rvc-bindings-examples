﻿using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
#if Halcon_Enable
using HalconDotNet;
#endif
#if OpenCV_Enable
using OpenCvSharp;
#endif
#if VisionPro_Enable
using Cognex.VisionPro;
#endif
using RVC_CSharp;

namespace RVC_CSharp
{
    /// <summary>
    /// If you have multiple cameras and want them to run in multiple threads, you can refer to the following example.
    /// </summary>
    class Program
    {
        
        private static void Function(object obj)
        {
            Device device = (Device) obj  ;


            // optional 
            // Print Device Info
            DeviceInfo info = new DeviceInfo();
            device.GetDeviceInfo(ref info);
            info.Print();

            X1 camera = RVC_CSharp.X1.Create(device, CameraID.CameraID_Left);
            camera.Open();
            if (false == camera.IsValid() || false == camera.IsOpen())
            {
                Console.WriteLine($"Failed to open camera .Error code = { System.GetLastError() } ");
                RVC_CSharp.System.Shutdown();
                return;
            }


            // *****
            // The function of camera instance should be executed within the same thread.

            int i = 0;

            while (i++<=5)
            {
                // Capture using the internal parameters of the camera.
                // We suggest that you adjust the parameters in RVC Manager first.
                bool ret = camera.Capture();

                if (false == ret)
                {
                    continue;
                }

                Image image = camera.GetImage();
                PointMap pointMap = camera.GetPointMap();

                // Color Point Cloud
                string colorPointCloudFile = $"./{info.name}-{info.sn}/{i}-ColorPointCloud.ply";
                Console.WriteLine($"Save Color-PointMap,path = {colorPointCloudFile}");
                pointMap.SaveColorPointCloud(image, colorPointCloudFile);
            }

            camera.Close();
            camera.Destroy();
        }

        
        static void Main()
        {

            if (false == RVC_CSharp.System.Init())
            {
                Console.WriteLine("Failed to init system.");
                return;
            }

            // ******
            // The Function of System Must Run In the Same thread.
            Device device1 = RVC_CSharp.System.FindDeviceBySN("aaaaaaaaa");
            Device device2 = RVC_CSharp.System.FindDeviceBySN("bbbbbbbbb");

            if (false == device1.IsValid() || false == device1.CheckCanConnected() ||
                false == device2.IsValid() || false == device2.CheckCanConnected())
            {
                Console.WriteLine("Devices are not Can-Connected.\nPlease Check Connection.");
                RVC_CSharp.System.Shutdown();
                return;
            }

            Thread thread1 = new Thread(Function);
            Thread thread2 = new Thread(Function);

            thread1.Start(device1);
            thread2.Start(device2);

            thread1.Join();
            thread2.Join();


            RVC_CSharp.System.Shutdown();
            
            return;
        }

    }
}
