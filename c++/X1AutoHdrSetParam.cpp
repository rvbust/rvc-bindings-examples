#include <RVC/RVC.h>

#include <iostream>

#include "IO/FileIO.h"
#include "IO/SavePointMap.h"

int main(int argc, char *argv[]) {
    // Initialize RVC X system.
    RVC::SystemInit();

    // Scan all RVC X Camera devices.
    RVC::Device devices[10];
    size_t actual_size = 0;
    SystemListDevices(devices, 10, &actual_size, RVC::SystemListDeviceType::All);

    // Find whether any RVC X Camera is connected or not.
    if (actual_size == 0) {
        std::cout << "Can not find any RVC X Camera!" << std::endl;
        return -1;
    }

    // Create a RVC X Camera and choose use left side camera.
    RVC::X1 x1 = RVC::X1::Create(devices[0], RVC::CameraID_Left);

    // Open RVC X Camera.
    x1.Open();

    // Test RVC X Camera is opened or not.
    if (!x1.IsOpen()) {
        std::cout << "RVC X Camera is not opened!" << std::endl;
        RVC::X1::Destroy(x1);
        RVC::SystemShutdown();
        return 1;
    }

    const std::string save_directory = "./Data/";
    MakeDirectories(save_directory);

    RVC::X1::CaptureOptions cap_opt;

    // Set ROI
    RVC::ROI roi = RVC::ROI(10, 10, 200, 200);

    // get hdr exposure parameters.
    bool ret = x1.GetAutoHdrCaptureSetting(cap_opt, roi);
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
    } else {
        std::cout << "get auto hdr capture setting failed" << std::endl;
        exit(0);
    }

    // Capture a point map and a image.
    if (x1.Capture(cap_opt) == true) {
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
    } else {
        std::cout << "RVC X Camera capture failed!" << std::endl;
    }

    // Close RVC X Camera.
    x1.Close();

    // Destroy RVC X Camera.
    RVC::X1::Destroy(x1);

    // Shutdown RVC X System.
    RVC::SystemShutdown();

    return 0;
}
