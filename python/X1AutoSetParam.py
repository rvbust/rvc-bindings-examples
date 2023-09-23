# Copyright (c) RVBUST, Inc - All rights reserved.
import PyRVC as RVC
import os
import numpy as np
import cv2

import time

from numpy.lib.npyio import save
from IPython import embed

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

    # Scan all RVC X Camera devices.
    ret, devices = RVC.SystemListDevices(opt)
    print("RVC X Camera devices number:%d" % len(devices))

    # Find whether any RVC X Camera is connected or not.
    if len(devices) == 0:
        print("Can not find any RVC X Camera!")
        RVC.SystemShutdown()
        return 1
    print("devices size = %d" % len(devices))

    # Create a RVC X Camera and choose use left side camera.
    x = RVC.X1.Create(devices[0], RVC.CameraID_Left)

    # Test RVC X Camera is valid or not.
    if x.IsValid() == True:
        print("RVC X Camera is valid!")
    else:
        print("RVC X Camera is not valid!")
        RVC.X1.Destroy(x)
        RVC.SystemShutdown()
        return 1

    # Open RVC X Camera.
    ret1 = x.Open()

    # Test RVC X Camera is opened or not.
    if ret1 and x.IsOpen() == True:
        print("RVC X Camera is opened!")
    else:
        print("RVC X Camera is not opened!")
        RVC.X1.Destroy(x)
        RVC.SystemShutdown()
        return 1

    cap_opt = RVC.X1_CaptureOptions()
    cap_opt.transform_to_camera = True

    # Set 2d and 3d exposure time. Capture with white light, range [11, 100]ms, others [3, 100]ms.
    exposure_time = 100
    cap_opt.exposure_time_2d = exposure_time
    cap_opt.exposure_time_3d = exposure_time

    cap_opt.filter_range = 0
    cap_opt.phase_filter_range = 0

    cap_opt.projector_brightness = 240
    cap_opt.light_contrast_threshold = 3

    # ROI Setting
    start_x = 10
    start_y = 10
    width = 200
    height = 200

    roi = RVC.ROI(start_x, start_y, width, height)

    # Get auto capture setting.exposure_time_3d,projector_brightness,
    # light_contrast_threshold will be adjusted automatically
    ret2, cap_opt = x.GetAutoCaptureSetting(cap_opt, roi)

    if ret2:
        print("get auto capture setting success!")
        print("auto exposure_time_2d: {} ms".format(cap_opt.exposure_time_2d))
        print("auto exposure_time_3d: {} ms".format(cap_opt.exposure_time_3d))
        print("auto projector_brightness: {}".format(cap_opt.projector_brightness))
        print("auto light_contrast_threshold: {}".format(cap_opt.light_contrast_threshold))
    else:
        print("get auto capture setting failed, custom setting will be used.")

    # Capture a point map and a image.
    ret3 = x.Capture(cap_opt)

    # Create saving address of image and point map.
    save_address = "Data"
    TryCreateDir(save_address)

    if ret3 == True:
        print("RVC X Camera capture successed!")

        # Get image data and image size.
        img = x.GetImage()
        width = img.GetSize().cols
        height = img.GetSize().rows

        # Convert image to array and save it.
        img = np.array(img, copy=False)
        cv2.imwrite("Data/test.png", img)
        print("Save image successed!")

        # Convert point map (m) to array and save it.
        pm = np.array(x.GetPointMap(), copy=False).reshape(-1, 3)
        np.savetxt("Data/point_map.xyz", pm)
        print("Save point map successed!")
    else:
        print("RVC X Camera capture failed!")
        x.Close()
        RVC.X1.Destroy(x)
        RVC.SystemShutdown()
        return 1

    # Close RVC X Camera.
    x.Close()

    # Destroy RVC X Camera.
    RVC.X1.Destroy(x)

    # Shutdown RVC X System.
    RVC.SystemShutdown()

    return 0


if __name__ == "__main__":
    App()
