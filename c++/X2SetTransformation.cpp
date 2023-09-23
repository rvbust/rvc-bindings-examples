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
    cap_opt.exposure_time_2d = 20;
    cap_opt.exposure_time_3d = 20;

    double transformation[16] = {0.9981883352,
                                 0.0502378577,
                                 0.0331089875,
                                 -0.0472612266,
                                 0.0505828392,
                                 -0.9986731004,
                                 -0.0096651386,
                                 0.076352919,
                                 0.0325794993,
                                 0.0113223752,
                                 -0.999405013,
                                 0.9951857984,
                                 0.,
                                 0.,
                                 0.,
                                 1.

    };

    RVC::X2::CustomTransformOptions custom_trans_opt;
    custom_trans_opt.coordinate_select = RVC::X2::CustomTransformOptions::CoordinateSelect_CaliBoard;
    for (size_t i = 0; i < 16; i++) {
        custom_trans_opt.transform[i] = transformation[i];
    }
    bool ret = x2.SetCustomTransformation(custom_trans_opt);

    if (ret) {
        std::cout << "set transformation success" << std::endl;
    } else {
        std::cout << "set transformation failed! custom transformation will not be used!" << std::endl;
    }

    const std::string save_directory = "./Data/";
    MakeDirectories(save_directory);

    // Capture a point map and a image with custom setting.
    if (x2.Capture(cap_opt) == true) {
        std::cout << "RVC X Camera capture successed!" << std::endl;

        // Get point map data (m).
        RVC::PointMap pm = x2.GetPointMap();
        std::string pm_addr = save_directory + "test.ply";
        std::cout << "save point map to file: " << pm_addr << std::endl;
        SavePlyFile(pm_addr.c_str(), pm);

        // Get image data.
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
