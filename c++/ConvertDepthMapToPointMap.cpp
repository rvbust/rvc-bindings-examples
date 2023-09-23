#include <RVC/RVC.h>

#include <iostream>
#include <opencv2/calib3d.hpp>

#include "IO/FileIO.h"
#include "IO/SavePointMap.h"

static RVC::PointMap ConvertDepthMapToPointMap(RVC::DepthMap &dp, const float intrinsicMatrix[9],
                                               const float distortion[5]) {
    RVC::Size sz = dp.GetSize();
    const int width = sz.width, height = sz.height, image_size = width * height;
    RVC::PointMap pm;
    pm = RVC::PointMap::Create(RVC::PointMapType::PointsOnly, sz);
    std::vector<cv::Point2f> pts(width * height);
    cv::Point2f *pts_ptr = pts.data();
    for (size_t r = 0; r < height; r++) {
        for (size_t c = 0; c < width; c++, pts_ptr++) {
            pts_ptr->x = c;
            pts_ptr->y = r;
        }
    }
    const float distortion_cv[5] = {distortion[0], distortion[1], distortion[3], distortion[4], distortion[2]};
    std::vector<cv::Point2f> undistorted_pts;
    cv::undistortPoints(pts, undistorted_pts, cv::Mat(3, 3, CV_32FC1, const_cast<float *>(intrinsicMatrix)),
                        cv::Mat(1, 5, CV_32FC1, const_cast<float *>(distortion_cv)));
    double *pm_ptr = pm.GetPointDataPtr();
    pts_ptr = undistorted_pts.data();
    const double *z = dp.GetDataPtr();
    for (size_t i = 0; i < image_size; i++, pts_ptr++, pm_ptr += 3, z++) {
        pm_ptr[0] = pts_ptr->x * z[0];
        pm_ptr[1] = pts_ptr->y * z[0];
        pm_ptr[2] = z[0];
    }
    return pm;
}

static bool IsPointMapEqual(RVC::PointMap &pm0, RVC::PointMap &pm1, double &maxDiff, const double tol = 1.0e-6) {
    bool rtf;
    const RVC::Size sz0 = pm0.GetSize(), sz1 = pm1.GetSize();
    rtf = sz0.width == sz1.width && sz0.height == sz1.height;
    maxDiff = -1;
    if (!rtf) {
        return rtf;
    }
    const double *data_ptr0 = pm0.GetPointDataPtr(), *data_ptr1 = pm1.GetPointDataPtr();
    const int data_size = sz0.width * sz0.height * 3;
    double sub_abs;
    bool data0_is_valid, data1_is_valid;
    for (size_t i = 0; i < data_size && rtf; i++) {
        data0_is_valid = data_ptr0[i] == data_ptr0[i];
        data1_is_valid = data_ptr1[i] == data_ptr1[i];
        if (data0_is_valid != data1_is_valid) {
            rtf = false;
        } else if (data0_is_valid) {
            sub_abs = fabs(data_ptr0[i] - data_ptr1[i]);
            if (sub_abs > maxDiff) {
                maxDiff = sub_abs;
            }
        }
    }
    rtf = rtf && maxDiff < tol;
    return rtf;
}

int main(int argc, char *argv[]) {
    // Initialize RVC X system.
    RVC::SystemInit();

    // Scan all USB RVC X Camera devices.
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

    RVC::X1::CaptureOptions cap_opts;
    cap_opts.transform_to_camera = true;
    cap_opts.exposure_time_3d = 11;

    const std::string save_directory = "./Data/";
    MakeDirectories(save_directory);

    // Capture a point map and a image with default setting.
    if (x1.Capture(cap_opts) == true) {
        RVC::PointMap pm = x1.GetPointMap();
        std::string pm_addr = save_directory + "test.ply";
        std::cout << "save point map to file: " << pm_addr << std::endl;
        SavePlyFile(pm_addr.c_str(), pm);

        RVC::DepthMap dp = x1.GetDepthMap();
        float intrinsic_matrix[9], distortion[5];
        x1.GetIntrinsicParameters(intrinsic_matrix, distortion);
        RVC::PointMap convert_pm = ConvertDepthMapToPointMap(dp, intrinsic_matrix, distortion);
        double max_diff;
        bool rtf = IsPointMapEqual(pm, convert_pm, max_diff, 1.0e-6);  // compare accuracy: um
        printf("pointmap is %s, max_diff (mm): %f\n", rtf ? "equal" : "not equal", max_diff * 1000);
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