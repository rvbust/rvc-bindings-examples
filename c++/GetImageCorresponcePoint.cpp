#include <RVC/RVC.h>
#include <stdio.h>
#include <iostream>
#include "IO/FileIO.h"
#include "IO/SavePointMap.h"

int main(int argc, char **argv) {
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

    // Capture a point map and a image with default setting.
    if (x1.Capture() == true) {
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

        const unsigned char *img_data;
        const double *xyz;
        const size_t img_w = img.GetSize().width, img_h = img.GetSize().height;
        bool is_color = img.GetType() == RVC::ImageType::Mono8 ? false : true;
        for (size_t r = 0; r < img_h; r += 10) {
            for (size_t c = 0; c < img_w; c += 10) {
                xyz = pm.GetPointDataPtr() + (r * img_w + c) * 3;
                if (is_color) {
                    img_data = img.GetDataPtr() + (r * img_w + c) * 3;
                    printf("image position(xy): (%zd, %zd) color: (%d, %d, %d), corresponce xyz: (%.6f, %.6f, %.6f)\n", c,
                           r, img_data[0], img_data[1], img_data[2], xyz[0], xyz[1], xyz[2]);
                } else {
                    img_data = img.GetDataPtr() + (r * img_w + c);
                    printf("image position(xy): (%zd, %zd) density: %d, corresponce xyz: (%.6f, %.6f, %.6f)\n", c, r,
                           img_data[0], xyz[0], xyz[1], xyz[2]);
                }
            }
        }
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