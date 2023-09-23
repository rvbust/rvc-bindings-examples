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
    // Transform point map's coordinate to left/right(RVC::CameraID_Left/RVC::CameraID_Right) camera or reference
    // plane(RVC::CameraID_NONE)
    cap_opt.transform_to_camera = RVC::CameraID_Left;
    // Set 2d and 3d exposure time. Capture with white light, range [11, 100]ms, others [3, 100]ms.
    cap_opt.exposure_time_2d = 20;
    cap_opt.exposure_time_3d = 20;
    // Set 2d and 3d gain. the default value is 0. The gain value of each series cameras is different, you can call
    // function GetGainRange() to get specific range.
    cap_opt.gain_2d = 0;
    cap_opt.gain_3d = 0;
    // Set 2d and 3d gamma. the default value is 1. The gamma value of each series cameras is different, you can call
    // function GetGammaRange() to get specific range.
    cap_opt.gamma_2d = 1;
    cap_opt.gamma_3d = 1;
    // range in [0, 10]. the default value is 3. The contrast of point less than this value will be treat * as invalid
    // point and be removed.
    cap_opt.light_contrast_threshold = 2;
    // edge control after point matching, range in [0, 10], default = 2. The big the value, the more edge * noise to be
    // removed.
    cap_opt.edge_noise_reduction_threshold = 0;
    // Set projector color. the default value is RVC::ProjectorColor_Blue.
    cap_opt.projector_color = RVC::ProjectorColor_Blue;

    const std::string save_directory = "./Data/";
    MakeDirectories(save_directory);

    // Set ROI
    RVC::ROI roi = RVC::ROI(10, 10, 200, 200);

    // Get auto capture setting, exposure_time_2d, exposure_time_3d, projector_brightness,
    // light_contrast_threshold will be adjusted automatically

    bool ret = x2.GetAutoCaptureSetting(cap_opt);
    if (ret) {
        std::cout << "get auto capture setting success" << std::endl;
        std::cout << "auto exposure_time_2d:" << cap_opt.exposure_time_2d << std::endl;
        std::cout << "auto exposure_time_3d:" << cap_opt.exposure_time_3d << std::endl;
        std::cout << "auto projector_brightness:" << cap_opt.projector_brightness << std::endl;
        std::cout << "auto light_contrast_threshold:" << cap_opt.light_contrast_threshold << std::endl;
    } else {
        std::cout << "get auto capture setting failed, custom setting will be used" << std::endl;
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

    // Close RVC X Camera.
    x2.Close();

    // Destroy RVC X Camera.
    RVC::X2::Destroy(x2);

    // Shutdown RVC X System.
    RVC::SystemShutdown();

    return 0;
}
