# Copyright (c) RVBUST, Inc - All rights reserved.
import PyRVC as RVC
import os
import numpy as np
import cv2

# Create a directory.


def TryCreateDir(d):
    if not os.path.exists(d):
        os.makedirs(d)
        return 1
    else:
        return 0


def App():

    # Initialize RVC X system.
    RVC.SystemInit()

    # Choose RVC X Camera type (USB, GigE or All)
    opt = RVC.SystemListDeviceTypeEnum.All

    # Scan all RVC X USB Camera devices.
    ret, devices = RVC.SystemListDevices(opt)

    # Find whether any RVC X Camera is connected or not.
    if len(devices) == 0:
        print("Can not find any RVC X USB Camera!")
        RVC.SystemShutdown()
        return 1
    print("devices size = %d" % len(devices))

    # Create a RVC X Camera and choose use left side camera.
    x = RVC.X1.Create(devices[0], RVC.CameraID_Left)

    # Test RVC X Camera is valid or not.
    if not x.IsValid():
        print("RVC X Camera is not valid!")
        RVC.X1.Destroy(x)
        RVC.SystemShutdown()
        return 1

    # Open RVC X Camera.
    ret1 = x.Open()

    # Test RVC X Camera is opened or not.
    if not ret1:
        print("RVC X Camera is not opened!")
        RVC.X1.Destroy(x)
        RVC.SystemShutdown()
        return 1

    cap_opts = RVC.X1_CaptureOptions()
    cap_opts.transform_to_camera = True
    cap_opts.exposure_time_3d = 11
    # Capture a point map and a image.
    ret2 = x.Capture(cap_opts)

    # Create saving address of image and point map.
    save_address = "Data"
    TryCreateDir(save_address)

    if ret2 == True:
        pm_sz = x.GetPointMap().GetSize()
        width = pm_sz.width
        height = pm_sz.height

        pm = np.array(x.GetPointMap(), copy=False).reshape(-1, 3)
        np.savetxt("Data/point_map.xyz", pm)
        print("Save point map successed!")

        dp = np.array(x.GetDepthMap(), copy=False)

        # convert depthmap to pointmap
        ret, intrinsic_matrix, distortion = x.GetIntrinsicParameters()
        intrinsic_matrix = np.array(intrinsic_matrix).reshape((3, 3))
        k1, k2, k3, p1, p2 = distortion
        distortion_cv = np.array([k1, k2, p1, p2, k3])

        X = range(width)
        Y = range(height)
        XY = np.array(np.meshgrid(X, Y), dtype=float).reshape((2, -1)).T
        undistorted_XY = cv2.undistortPoints(
            XY, intrinsic_matrix, distortion_cv).reshape((height, width, 2))
        convert_pm = np.array([undistorted_XY[:, :, 0] * dp,
                               undistorted_XY[:, :, 1] * dp, dp]).reshape((3, -1)).T

        # compute convert error
        valid_mask0 = ~np.isnan(pm[:, 2])
        valid_mask1 = ~np.isnan(convert_pm[:, 2])
        sub_pm = np.abs(convert_pm[valid_mask0] - pm[valid_mask0])
        print(np.all(valid_mask0 == valid_mask1))
        print(f"min diff (mm): {np.min(sub_pm, axis=0) * 1000}")
        print(f"max diff (mm): {np.max(sub_pm, axis=0) * 1000}")

    # Close RVC X Camera.
    x.Close()

    # Destroy RVC X Camera.
    RVC.X1.Destroy(x)

    # Shutdown RVC X System.
    RVC.SystemShutdown()

    return 0


if __name__ == "__main__":
    App()
