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

    // Create a RVC X Camera
    RVC::X2 x2 = RVC::X2::Create(devices[0]);

    // Open RVC X Camera
    x2.Open();

    // Test RVC X Camera is opened or not
    if (!x2.IsOpen()) {
        std::cout << "RVC X Camera is not opened!" << std::endl;
        RVC::X2::Destroy(x2);
        RVC::SystemShutdown();
        return 1;
    }
    // Set capture parameters
    RVC::X2::CaptureOptions cap_opt;
    // Set HDR exposure times [0, 2, 3]. 0 presents not use hdr. 2 and 3 presents hdr times.
    // Capture with white light, range [11, 100]ms, others [3, 100]ms.
    cap_opt.hdr_exposure_times = 3;
    cap_opt.hdr_exposuretime_content[0] = 11;
    cap_opt.hdr_exposuretime_content[1] = 20;
    cap_opt.hdr_exposuretime_content[2] = 100;

    const std::string save_directory = "./Data/";
    MakeDirectories(save_directory);

    // Capture a point map and a image (default can be x2.Capture();)
    if (x2.Capture(cap_opt) == true) {
        std::cout << "RVC X Camera capture successed!" << std::endl;
        // Get point map data (m)
        RVC::PointMap pm = x2.GetPointMap();
        std::string pm_addr = save_directory + "test.ply";
        std::cout << "save point map to file: " << pm_addr << std::endl;
        SavePlyFile(pm_addr.c_str(), pm);

        // Get image data
        RVC::Image left_img = x2.GetImage(RVC::CameraID_Left);
        RVC::Image right_img = x2.GetImage(RVC::CameraID_Right);
        std::cout << "save image to directory: " << save_directory << std::endl;
        left_img.SaveImage((save_directory + "left.png").c_str());
        right_img.SaveImage((save_directory + "right.png").c_str());
    } else {
        std::cout << "RVC X Camera capture failed!" << std::endl;
    }

    // Close RVC X Camera
    x2.Close();

    // Destroy RVC X Camera
    RVC::X2::Destroy(x2);

    // Shut Down RVC X System
    RVC::SystemShutdown();
    return 0;
}
