// Copyright (c) RVBUST, Inc - All rights reserved.

#include <RVC/RVC.h>
#include <fstream>
#include <iostream>
#include <IO/FileIO.h>
#include <IO/SavePointMap.h>

static void UseX1() {
    RVC::SystemInit();
    RVC::Device devices[10];
    size_t actual_size = 0;
    SystemListDevices(devices, 10, &actual_size, RVC::SystemListDeviceType::All);

    if (actual_size == 0) {
        std::cout << "Can not find any Camera!" << std::endl;
        return;
    }

    // Create a RVC X Camera and choose use left side camera
    RVC::X1 x1 = RVC::X1::Create(devices[0], RVC::CameraID_Left);

    // Open RVC X Camera
    x1.Open();

    if (!x1.IsOpen()) {
        std::cout << "RVC amera is not opened!" << std::endl;
        RVC::X1::Destroy(x1);
        RVC::SystemShutdown();
        return;
    }
    
    bool ret = x1.SaveSettingToFile("d://test.json");
	if(!ret)
	{
        std::cout << "RVC Camera failed to SaveSettingToFile !" << std::endl;
        RVC::X1::Destroy(x1);
        RVC::SystemShutdown();
        return;
	}

    ret = x1.LoadSettingFromFile("d://test.json");
    if (!ret)
    {
        std::cout << "RVC Camera failed to LoadSettingFromFile !" << std::endl;
        RVC::X1::Destroy(x1);
        RVC::SystemShutdown();
        return;
    }

    RVC::X1::CaptureOptions stored_opt_1;
    x1.LoadCaptureOptionParameters(stored_opt_1);

    const std::string save_directory = "./Data/";
    MakeDirectories(save_directory);

    // Capture a point map and a image with default setting.
    if (x1.Capture(stored_opt_1) == true) {
        std::cout << "RVC X Camera capture successed!" << std::endl;

        // Get point map data (m).
        RVC::PointMap pm = x1.GetPointMap();
        std::string pm_addr = save_directory + "test.ply";
        std::cout << "save point map to file: " << pm_addr << std::endl;
        SavePlyFile(pm_addr.c_str(), pm);

        // Get image data.
        RVC::Image img = x1.GetImage();
        std::string img_addr = save_directory + "test.png";
        std::cout << "save image to file: " << img_addr << std::endl;
        img.SaveImage(img_addr.c_str());
    }
    else {
        std::cout << "RVC X Camera capture failed!" << std::endl;
    }

	
    x1.Close();
    RVC::X1::Destroy(x1);

    RVC::SystemShutdown();
    return;
}

static void UseX2() {
    RVC::SystemInit();
    // Scan all RVC X Camera devices
    RVC::Device devices[10];
    size_t actual_size = 0;
    SystemListDevices(devices, 10, &actual_size, RVC::SystemListDeviceType::All);

    // Find whether any Camera is connected or not.
    if (actual_size == 0) {
        std::cout << "Can not find any Camera!" << std::endl;
        return;
    }

    // Create a RVC X Camera.
    RVC::X2 x2 = RVC::X2::Create(devices[0]);

    // Open RVC X Camera.
    x2.Open();

    // Test RVC X Camera is opened or not.
    if (!x2.IsOpen()) {
        std::cout << "RVC X Camera is not opened!" << std::endl;
        RVC::X2::Destroy(x2);
        RVC::SystemShutdown();
        return;
    }
	
    bool ret = x2.SaveSettingToFile("d://test.json");
    if (!ret)
    {
        std::cout << "RVC Camera failed to SaveSettingToFile !" << std::endl;
        RVC::X2::Destroy(x2);
        RVC::SystemShutdown();
        return;
    }

    ret = x2.LoadSettingFromFile("d://test.json");
    if (!ret)
    {
        std::cout << "RVC Camera failed to LoadSettingFromFile !" << std::endl;
        RVC::X2::Destroy(x2);
        RVC::SystemShutdown();
        return;
    }

    x2.Close();
    RVC::X2::Destroy(x2);

    RVC::SystemShutdown();
    return;
}

int main(int argc, char *argv[]) {
    UseX1();
    UseX2();
    return 0;
}
