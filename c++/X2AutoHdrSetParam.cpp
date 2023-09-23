#include <RVC/RVC.h>

#include <iostream>

#include "IO/FileIO.h"
#include "IO/SavePointMap.h"

int main(int argc, char *argv[]) {
    // Initialize RVC X system.
    RVC::SystemInit();

    // Choose RVC X Camera type (USB or GigE).
    RVC::Device devices[10];
    size_t actual_size = 0;
    SystemListDevices(devices, 10, &actual_size, RVC::SystemListDeviceType::All);

    // Find whether any Camera is connected or not.
    if (actual_size == 0) {
        std::cout << "Can not find any Camera!" << std::endl;
        return -1;
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
        return 1;
    }

    // Set capture parameters
    RVC::X2::CaptureOptions cap_opt;

    const std::string save_directory = "./Data/";
    MakeDirectories(save_directory);

    // Set ROI
    RVC::ROI roi = RVC::ROI(10, 10, 200, 200);

    // get hdr exposure parameters.
    bool ret = x2.GetAutoHdrCaptureSetting(cap_opt, roi);
    if (ret) {
        std::cout << "projector_brightness: " << cap_opt.projector_brightness << std::endl;
        if (cap_opt.hdr_exposure_times == 0) {
            std::cout << "hdr exposure setting will not be used" << std::endl;
            std::cout << "exposure_time_3d: " << cap_opt.exposure_time_3d << std::endl;
        } else {
            std::cout << "hdr_exposure_times: " << cap_opt.hdr_exposure_times << std::endl;
            for (size_t i = 0; i < cap_opt.hdr_exposure_times; i++) {
                std::cout << "hdr exposure index: " << i << " exposure time: " << cap_opt.hdr_exposuretime_content[i]
                          << std::endl;
            }
        }
        // Capture a point map and a image with default setting.
        if (x2.Capture(cap_opt) == true) {
            // Get point map data (m).
            RVC::PointMap pm = x2.GetPointMap();
            std::string pm_addr = save_directory + "test.ply";
            std::cout << "save point map to file: " << pm_addr << std::endl;
            SavePlyFile(pm_addr.c_str(), pm);

            // Get image data. choose left or right side. the point map is map to left image.
            RVC::Image img = x2.GetImage(RVC::CameraID_Left);
            std::string img_addr = save_directory + "test.png";
            std::cout << "save image to file: " << img_addr << std::endl;
            img.SaveImage(img_addr.c_str());
        } else {
            std::cout << "RVC X Camera capture failed!" << std::endl;
        }
    } else {
        std::cout << "get auto hdr capture setting failed" << std::endl;
    }

    // Close RVC X Camera.
    x2.Close();

    // Destroy RVC X Camera.
    RVC::X2::Destroy(x2);

    // Shutdown RVC X System.
    RVC::SystemShutdown();

    return 0;
}
