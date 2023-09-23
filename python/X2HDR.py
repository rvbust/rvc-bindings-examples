# Copyright (c) RVBUST, Inc - All rights reserved.
import PyRVC as RVC
import numpy as np
import cv2
import os


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

    # Find whether any RVC X Camera is connected or not.
    if len(devices) == 0:
        print("Can not find any RVC X Camera!")
        RVC.SystemShutdown()
        return 1
    print("devices size = %d" % len(devices))

    # Create a RVC X Camera
    x = RVC.X2.Create(devices[0])

    # Test RVC X Camera is valid or not.
    if x.IsValid() == True:
        print("RVC X Camera is valid!")
    else:
        print("RVC X Camera is not valid!")
        RVC.X2.Destroy(x)
        RVC.SystemShutdown()
        return 1

    # Open RVC X Camera.
    ret1 = x.Open()

    # Test RVC X Camera is opened or not.
    if ret1 and x.IsOpen() == True:
        print("RVC X Camera is opened!")
    else:
        print("RVC X Camera is not opened!")
        RVC.X2.Destroy(x)
        RVC.SystemShutdown()
        return 1

    # Set capture parameters.
    cap_opt = RVC.X2_CaptureOptions()

    # Set HDR exposure times [0, 2, 3]. 0 presents not use hdr. 2 and 3 presents hdr times.
    # Capture with white light, range [11, 100]ms, others [3, 100]ms.
    cap_opt.hdr_exposure_times = 3
    # Set the first capture exposure time
    cap_opt.SetHDRExposureTimeContent(1, 11)
    # Set the second capture exposure time
    cap_opt.SetHDRExposureTimeContent(2, 20)
    # Set the third capture exposure time
    cap_opt.SetHDRExposureTimeContent(3, 100)

    # Capture a point map and a image with default setting.
    ret2 = x.Capture(cap_opt)

    # Create saving address of image and point map.
    save_address = "Data"
    TryCreateDir(save_address)

    if ret2 == True:
        print("RVC X Camera capture successed!")

        # Get image data.
        left_img = x.GetImage(RVC.CameraID_Left)
        right_img = x.GetImage(RVC.CameraID_Right)
        width = left_img.GetSize().cols
        height = left_img.GetSize().rows

        # Get image size and color information.
        print("width=%d, height=%d" % (width, height))
        if left_img.GetType() == RVC.ImageTypeEnum.Mono8:
            print("This is mono camera")
        else:
            print("This is color camera")

        # convert image to array and save it.
        left_img = np.array(left_img, copy=False)
        cv2.imwrite("Data/left.png", left_img)
        right_img = np.array(right_img, copy=False)
        cv2.imwrite("Data/right.png", right_img)
        print("Save image successed!")

        # Get point map data (m) and save it.
        pm = np.array(x.GetPointMap(), copy=False).reshape(-1, 3)
        np.savetxt("Data/test.xyz", pm)
        print("Save point map successed!")
    else:
        print("RVC X Camera capture failed!")
        x.Close()
        RVC.X2.Destroy(x)
        RVC.SystemShutdown()
        return 1

    # Close RVC X Camera.
    x.Close()

    # Destroy RVC X Camera.
    RVC.X2.Destroy(x)

    # Shut Down RVC X System.
    RVC.SystemShutdown()

    return 0


if __name__ == "__main__":
    App()
