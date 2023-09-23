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

    const std::string save_directory = "./Data/";
    MakeDirectories(save_directory);

    RVC::X2::CaptureOptions cap_opt;
    cap_opt.exposure_time_2d = 50;
    // X2 Capture 2D with left camera
    if (x2.Capture2D(RVC::CameraID_Left, cap_opt)) {
        std::cout << "Capture 2D success!" << std::endl;
        RVC::Image img = x2.GetImage(RVC::CameraID_Left);
        std::string img_addr = save_directory + "test_2d.png";
        std::cout << "Save image to file: " << img_addr << std::endl;
        img.SaveImage(img_addr.c_str());
    } else {
        std::cout << "Capture 2D failed!" << std::endl;
    }

    // X2 Capture 3D
    if (x2.Capture()) {
        std::cout << "Capture 3D successed!" << std::endl;
    } else {
        std::cout << "Capture 3D failed!" << std::endl;
    }

    // Close RVC X Camera
    x2.Close();

    // Destroy RVC X Camera
    RVC::X2::Destroy(x2);

    // Shut Down RVC X System
    RVC::SystemShutdown();
    return 0;
}