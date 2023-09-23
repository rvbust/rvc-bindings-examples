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

	// Create and Open
    RVC::X1 x1 = RVC::X1::Create(device);
    x1.Open();
    if (!x1.IsOpen()) {
        std::cout << "RVC X Camera is not opened!" << std::endl;
        RVC::X1::Destroy(x1);
        RVC::SystemShutdown();
        return -1;
    }

	// Capture
    // Capture using the internal parameters of the camera.
    // We suggest that you adjust the parameters in RVC Manager first.
    bool ret = x1.Capture();
    if(ret == false)
    {
        x1.Close();
        RVC::X1::Destroy(x1);
        RVC::SystemShutdown();
        return -1;
    }

	// Data Process
    std::string dir = "./Data/";
    MakeDirectories(dir);
    dir += info.sn;
    MakeDirectories(dir);
    dir += "/x1";
    MakeDirectories(dir);

    RVC::PointMap pointcloud = x1.GetPointMap();
    RVC::Image image = x1.GetImage();
    pointcloud.Save((dir + "/pointcloud.ply").c_str(), RVC::PointMapUnit::Millimeter, true);
    pointcloud.Save((dir + "/pointcloud_color.ply").c_str(),RVC::PointMapUnit::Millimeter,true,image);
    image.SaveImage((dir + "/image.png").c_str());


    // Close RVC X Camera.
    x1.Close();
    RVC::X1::Destroy(x1);
    RVC::SystemShutdown();

	
    return 0;
}
