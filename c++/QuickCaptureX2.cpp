﻿#include <RVC/RVC.h>

#include <iostream>

#include "IO/FileIO.h"
#include "IO/SavePointMap.h"

int main(int argc, char *argv[]) {
    // Initialize RVC X system.
    RVC::SystemInit();

	// Find Device
    RVC::Device device;

	// Method 1,Find device by index.
    {

        RVC::Device devices[10];
        size_t actual_size = 0;
        SystemListDevices(devices, 10, &actual_size, RVC::SystemListDeviceType::All);
        if (actual_size == 0) {
            std::cout << "Can not find any Camera!" << std::endl;
            return -1;
        }
        device = devices[0];
    }

	// Method 2,Find device by sn
	// This is the most recommended method when you have multiple cameras.
    {
        //device = RVC::SystemFindDevice("12345678");
    }
	
    RVC::DeviceInfo info;
    device.GetDeviceInfo(&info);

	if(info.support_x2 == false)
	{
        std::cout << "The camera does not support the x2 function!" << std::endl;
        RVC::SystemShutdown();
        return -1;
    }
	
	// Create and Open
    RVC::X2 x2 = RVC::X2::Create(device);
    x2.Open();
    if (!x2.IsOpen()) {
        std::cout << "RVC X Camera is not opened!" << std::endl;
        RVC::X2::Destroy(x2);
        RVC::SystemShutdown();
        return -1;
    }

	// Capture
    // Capture using the internal parameters of the camera.
    // We suggest that you adjust the parameters in RVC Manager first.
    bool ret = x2.Capture();
    if(ret == false)
    {
        x2.Close();
        RVC::X2::Destroy(x2);
        RVC::SystemShutdown();
        return -1;
    }

	// Data Process
    std::string dir = "./Data/";
    MakeDirectories(dir);
    dir += info.sn;
    MakeDirectories(dir);
    dir += "/x2";
    MakeDirectories(dir);

    RVC::PointMap pointcloud = x2.GetPointMap();
    RVC::Image image = x2.GetImage(RVC::CameraID_Left);
    pointcloud.Save((dir + "/pointcloud.ply").c_str(), RVC::PointMapUnit::Millimeter, true);
    pointcloud.Save((dir + "/pointcloud_color.ply").c_str(),RVC::PointMapUnit::Millimeter,true,image);
    image.SaveImage((dir + "/image.png").c_str());


    // Close RVC X Camera.
    x2.Close();
    RVC::X2::Destroy(x2);
    RVC::SystemShutdown();

    return 0;
}
