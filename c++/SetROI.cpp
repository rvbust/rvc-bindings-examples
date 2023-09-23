#include <RVC/RVC.h>

#include <iostream>

#include "IO/FileIO.h"
#include "IO/SavePointMap.h"

int main(int argc, char* argv[]) {
    // Initialize RVC X system
    RVC::SystemInit();

    // Scan all RVC X Camera devices
    RVC::Device devices[10];
    size_t actual_size = 0;
    SystemListDevices(devices, 10, &actual_size, RVC::SystemListDeviceType::All);

    // Find whether any RVC X Camera is connected or not
    if (actual_size == 0) {
        std::cout << "Can not find any RVC X Camera!" << std::endl;
        return -1;
    }

    // RVC::Device device = RVC::SystemFindDevice("X2GM053W031");

    // Create a RVC X Camera and choose use left side camera
    RVC::X1 x1 = RVC::X1::Create(devices[0], RVC::CameraID_Left);

    // Open RVC X Camera
    x1.Open();

    // Test RVC X Camera is opened or not
    if (!x1.IsOpen()) {
        std::cout << "RVC X Camera is not opened!" << std::endl;
        RVC::X1::Destroy(x1);
        RVC::SystemShutdown();
        return 1;
    }
    // Set capture parameters
    RVC::X1::CaptureOptions cap_opt;
    cap_opt.exposure_time_3d = 3;
    cap_opt.exposure_time_2d = 3;
    cap_opt.filter_range = 0;

    // Set ROI's width, height, offset x and y
    cap_opt.roi.width = 0;
    cap_opt.roi.height = 0;
    cap_opt.roi.x = 0;
    cap_opt.roi.y = 0;

	// Check ROI 
	if(x1.CheckRoi(cap_opt.roi) == false)
	{
        std::cout << "roi is not valid,need to adjust. "<< std::endl;

		// Auto Adjust Roi
        cap_opt.roi = x1.AutoAdjustRoi(cap_opt.roi);
	}

    const std::string save_directory = "./Data/";
    MakeDirectories(save_directory);

    // Capture a point map and a image (default can be x1.Capture();)
    if (x1.Capture(cap_opt) == true) {
        std::cout << "RVC X Camera capture successed!" << std::endl;
        // Get point map data (m).
        RVC::PointMap pm = x1.GetPointMap();
        std::string pm_addr = save_directory + "test.ply";
        std::cout << "save point map to file: " << pm_addr << std::endl;
        SavePlyFile(pm_addr.c_str(), pm);

        // Get image data
        RVC::Image img = x1.GetImage();
        std::string img_addr = save_directory + "test.png";
        std::cout << "save image to file: " << img_addr << std::endl;
        img.SaveImage(img_addr.c_str());
    } else {
        std::cout << "RVC X Camera capture failed!" << std::endl;
    }

    // Close RVC X Camera
    x1.Close();

    // Destroy RVC X Camera
    RVC::X1::Destroy(x1);

    // Shut Down RVC X System
    RVC::SystemShutdown();
    return 0;
}
