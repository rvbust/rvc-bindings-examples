#include <RVC/RVC.h>
#include <iostream>
#include "IO/FileIO.h"
#include "IO/SavePointMap.h"

int main(int argc, char* argv[]) {
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

    // Set capture parameters.
    RVC::X1::CaptureOptions cap_opt;

    // Transform point map's coordinate to camera or reference plane.
    cap_opt.transform_to_camera = true;

    // Set noise points filter range (0~30).
    cap_opt.filter_range = 0;

    // Set camera 2D exposure time (3~100) ms.
    cap_opt.exposure_time_2d = 6;

    // Set camera 3D exposure time (3~100) ms.
    cap_opt.exposure_time_3d = 6;

    // calculate normal or not.
    cap_opt.calc_normal = true;

    // Neighborhood radius in pixel of calculating normal, > 0.
    cap_opt.calc_normal_radius = 5;

    const std::string save_directory = "./Data/";
    MakeDirectories(save_directory);

    // Capture a point map and a image with default setting.
    if (x1.Capture(cap_opt) == true) {
        std::cout << "RVC X Camera capture successed!" << std::endl;

        // Get point map data (m).
        RVC::PointMap pm = x1.GetPointMap();
        std::string pm_addr = save_directory + "test.ply";
        std::cout << "save point map to file: " << pm_addr << std::endl;
        SavePlyFile(pm_addr.c_str(), pm, true);

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