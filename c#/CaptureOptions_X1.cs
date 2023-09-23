using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
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
    class Program
    {

        static void Main()
        {
            #region Step 0 ,Init & Find & Open

            if (false == RVC_CSharp.System.Init() )
            {
                Console.WriteLine("Failed to init system.");
                return;
            }

            Device device = RVC_CSharp.System.FindDeviceByIndex(0);
            if (false == device.IsValid() || false == device.CheckCanConnected())
            {
                Console.WriteLine("Device Can not be Connected.\nPlease Check Connection.");
                RVC_CSharp.System.Shutdown();
                return;
            }

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


            #endregion

            #region Step 1 ,[Main Step] Modify Options And Capture

            X1.CaptureOptions options = X1.CaptureOptions.Default();
            bool ret = false;

            // Print Options
            {
                Console.WriteLine($"打印拍摄参数---");

                Console.WriteLine($"拍摄模式--[capture_mode] = {options.capture_mode.Name()}");
                Console.WriteLine($"2D 曝光时间--[exposure_time_2d] = {options.exposure_time_2d}");
                Console.WriteLine($"2D 增益--[gain_2d] = {options.gain_2d}");
                Console.WriteLine($"2D Gamma--[gamma_2d] = {options.gamma_2d}");
                Console.WriteLine($"2D 拍摄是否使用光机--[use_projector_capturing_2d_image] = {options.use_projector_capturing_2d_image}");
                Console.WriteLine($"3D 曝光时间--[exposure_time_3d] = {options.exposure_time_3d}");
                Console.WriteLine($"3D 增益--[gain_3d] = {options.gain_3d}");
                Console.WriteLine($"3D Gamma--[gamma_3d] = {options.gamma_3d}");
                Console.WriteLine($"光强对比度阈值--[light_contrast_threshold] = {options.light_contrast_threshold}");
                Console.WriteLine($"投影亮度--[projector_brightness] = {options.projector_brightness}");

                Console.WriteLine($"HDR 次数--[hdr_exposure_times] = {options.hdr_exposure_times}");
                Console.WriteLine($"HDR 曝光(0,1,2)--[hdr_exposuretime_content] = {options.hdr_exposuretime_content[0]},{options.hdr_exposuretime_content[1]},{options.hdr_exposuretime_content[2]}");
                Console.WriteLine($"HDR 增益(0,1,2)--[hdr_gain_3d] = {options.hdr_gain_3d[0]},{options.hdr_gain_3d[1]},{options.hdr_gain_3d[2]}");
                Console.WriteLine($"HDR 扫描次数(0,1,2)--[hdr_exposuretime_content] = {options.hdr_scan_times[0]},{options.hdr_scan_times[1]},{options.hdr_scan_times[2]}");
                Console.WriteLine($"HDR 投影亮度(0,1,2)--[hdr_exposuretime_content] = {options.hdr_projector_brightness[0]},{options.hdr_projector_brightness[1]},{options.hdr_projector_brightness[2]}");

                Console.WriteLine($"置信度去噪阈值--[confidence_threshold] = {options.confidence_threshold}");
                Console.WriteLine($"聚类降噪距离阈值--[noise_removal_distance] = {options.noise_removal_distance}");
                Console.WriteLine($"聚类降噪有效点数阈值--[noise_removal_point_number] = {options.noise_removal_point_number}");
                Console.WriteLine($"平滑等级--[smoothness] = {options.smoothness.Name()}");
                Console.WriteLine($"下采样距离(m)--[downsample_distance] = {options.downsample_distance}");
                Console.WriteLine($"是否计算法向量--[calc_normal] = {options.calc_normal}");
                Console.WriteLine($"计算法向量距离--[calc_normal_radius] = {options.calc_normal_radius}");

                Console.WriteLine($"ROI(x,y,w,h)--[roi] = {options.roi.x},{options.roi.y},{options.roi.width},{options.roi.height}");

                //G系列相机，扫描次数
                Console.WriteLine($"扫描次数[G系列相机]--[scan_times] = {options.scan_times}");

                //新增算法参数，双边滤波
                Console.WriteLine($"z向截断最小值--[truncate_z_min] = {options.truncate_z_min}");
                Console.WriteLine($"z向截断最大值--[truncate_z_max] = {options.truncate_z_max}");
                Console.WriteLine($"双边滤波窗口大小--[bilateral_filter_kernal_size] = {options.bilateral_filter_kernal_size}");
                Console.WriteLine($"双边滤波深度分布--[bilateral_filter_depth_sigma] = {options.bilateral_filter_depth_sigma}");
                Console.WriteLine($"双边滤波空间分布--[bilateral_filter_space_sigma] = {options.bilateral_filter_space_sigma}");

            }

            // Method 1 , Use Default Options and Modify.
            // X1.CaptureOptions options = X1.CaptureOptions.Default();
            // TODO:modify options
            // ret = camera.Capture(options);

            // Method 2 , Load Options From Camera and Modify.
            // X1.CaptureOptions options = new X1.CaptureOptions();
            // camera.LoadCaptureOptionParameters(ref options);
            // TODO:modify options
            // ret = camera.Capture(options);

            // *****
            // Method 3 , Using the internal parameters of the camera.
            // We suggest adjusting the camera parameters By RVC Manager.
            // Then, when we use SDK, we directly use the parameters inside the camera.
            ret = camera.Capture();

            // Method 4 , Load Options From File and Capture.
            // If you need to capture multiple scenes, their parameters are different.
            // You can save these parameters as different configuration files  By RVC Manager and then import the files before capture.
            // ret = camera.LoadSettingFromFile("file.json");
            // ret = camera.Capture();


            if (false == ret)
            {
                Console.WriteLine($"Failed to Capture .Error code = { System.GetLastError() } ");
                camera.Close();
                camera.Destroy();
                RVC_CSharp.System.Shutdown();
                return;
            }

            Image image = camera.GetImage();
            DepthMap depth = camera.GetDepthMap();
            PointMap pointMap = camera.GetPointMap();

            #endregion

            #region Step 2 , Data Process And Close

            Directory.CreateDirectory($"./{info.name}-{info.sn}");

            // 2D Image
            string imageFile = $"./{info.name}-{info.sn}/Image.bmp";
            Console.WriteLine($"Save Image,path = {imageFile}");
            image.SaveImage(imageFile);

            // Depth
            string depthFile = $"./{info.name}-{info.sn}/Depth.tiff";
            Console.WriteLine($"Save Depth,path = {depthFile}");
            depth.SaveDepthMap(depthFile);

            // Point Cloud 
            string pointCloudFile = $"./{info.name}-{info.sn}/PointCloud.ply";
            Console.WriteLine($"Save PointMap,path = {pointCloudFile}");
            pointMap.SavePlyBinary(pointCloudFile);

            // Color Point Cloud
            string colorPointCloudFile = $"./{info.name}-{info.sn}/ColorPointCloud.ply";
            Console.WriteLine($"Save Color-PointMap,path = {colorPointCloudFile}");
            pointMap.SaveColorPointCloud(image, colorPointCloudFile);

            camera.Close();
            camera.Destroy();

            RVC_CSharp.System.Shutdown();
            Console.WriteLine("System close.");

            #endregion

            return;
        }

    }
}
