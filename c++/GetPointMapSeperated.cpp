#include <RVC/RVC.h>
#include <iostream>
#include "IO/FileIO.h"
#include "IO/SavePointMap.h"

#include <cmath>

int main(int argc, char *argv[]) {
    // Initialize RVC X system.
    RVC::SystemInit();

    // Scan all RVC X Camera devices.
    RVC::Device devices[10];
    size_t actual_size = 0;
    SystemListDevices(devices, 10, &actual_size, RVC::SystemListDeviceType::All);

    // Find whether any RVC X Camera is connected or not.
    if (actual_size == 0) {
        std::cout << "Can not find any USB RVC X Camera!" << std::endl;
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

        RVC::Size sz = pm.GetSize();
        int pm_num = sz.width * sz.height;

        // Please make sure allocate correct size memory

        double *x = new double[pm_num];
        double *y = new double[pm_num];
        double *z = new double[pm_num];

        // scale = 1.0 get points unit m, scale = 1000.0 get unit mm
        bool ret = pm.GetPointMapSeperated(x, y, z, 1.0);

        if (ret) {
            for (size_t i = 0, valid_num = 0; valid_num < 100; i++) {
                if (std::isnan(x[i])) {
                    continue;
                }
                printf("index:%zd, x:%f, y:%f, z:%f\n", i, x[i], y[i], z[i]);
                valid_num++;
            }
        } else {
            std::cout << "Get point map seperated failed!" << std::endl;
        }

        delete[] x;
        delete[] y;
        delete[] z;

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