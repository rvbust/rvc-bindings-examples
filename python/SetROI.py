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

    # device = RVC.SystemFindDevice("I1UM358B001")

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

    # Set capture parameters.
    cap_opt = RVC.X1_CaptureOptions()

    cap_opt.exposure_time_3d = 20
    cap_opt.exposure_time_2d = 20
    cap_opt.filter_range = 0

    # Set ROI's width, height, offset x and y
    cap_opt.roi.width = 512
    cap_opt.roi.height = 512
    cap_opt.roi.x = 218
    cap_opt.roi.y = 64

    retRange,roiRange = x.GetRoiRange()


    retRoi = x.CheckRoi(cap_opt.roi)

    if retRoi == False:
        cap_opt.roi =  x.AutoAdjustRoi(cap_opt.roi)


    # Capture a point map and a image with default setting.
    ret2 = x.Capture(cap_opt)

    # Create saving address of image and point map.
    save_address = "Data"
    TryCreateDir(save_address)

    if ret2 == True:
        print("RVC X Camera capture successed!")

        # Get image data.
        img = x.GetImage()
        width = img.GetSize().cols
        height = img.GetSize().rows

        # Get image size and color information.
        print("width=%d, height=%d" % (width, height))
        if img.GetType() == RVC.ImageTypeEnum.Mono8:
            print("This is mono camera")
        else:
            print("This is color camera")

        # convert image to array and save it.
        img = np.array(img, copy=False)
        cv2.imwrite("Data/test.png", img)
        print("Save image successed!")

        # Get point map data (m) and save it.
        pm = np.array(x.GetPointMap(), copy=False).reshape(-1, 3)
        np.savetxt("Data/test.xyz", pm)
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

    # Shut Down RVC X System.
    RVC.SystemShutdown()

    return 0


if __name__ == "__main__":
    App()
