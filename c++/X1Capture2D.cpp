#include <RVC/RVC.h>
#include <iostream>
#include "IO/FileIO.h"

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

    const std::string save_directory = "./Data/";
    MakeDirectories(save_directory);
    
    RVC::X1::CaptureOptions cap_opt;
    cap_opt.exposure_time_2d = 50;
    // X1 Capture 2D
    if (x1.Capture2D(cap_opt)) {
        std::cout << "Capture 2D success!" << std::endl;
        RVC::Image img = x1.GetImage();
        std::string img_addr = save_directory + "test_2d.png";
        std::cout << "Save image to file: " << img_addr << std::endl;
        img.SaveImage(img_addr.c_str());
    } else {
        std::cout << "Capture 2D failed!" << std::endl;
    }

    // X1 Capture 3D
    if (x1.Capture()) {
        std::cout << "Capture 3D successed!" << std::endl;
    } else {
        std::cout << "Capture 3D failed!" << std::endl;
    }

    // Close RVC X Camera
    x1.Close();

    // Destroy RVC X Camera
    RVC::X1::Destroy(x1);

    // Shut Down RVC X System
    RVC::SystemShutdown();
    return 0;
}