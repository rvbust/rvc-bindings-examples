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

    # Scan all RVC X Camera devices.
    ret, devices = RVC.SystemListDevices(opt)
    print("RVC X Camera devices number:%d" % len(devices))

    #  Find whether any RVC X Camera is connected or not.
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

    # Continue capture 10 times.
    capture_times = 10

    # Create saving address of image and point map.
    save_address = "Data"
    TryCreateDir(save_address)

    for i in range(capture_times):
        print("capture frame number:%d" % i)
        if x.Capture() == True:
            print("RVC X Camera capture %dth image successed!" % i)
            # Get image data and image size.
            img = x.GetImage()
            width = img.GetSize().cols
            height = img.GetSize().rows

            # Convert image to array and save it.
            img = np.array(img, copy=False)
            cv2.imwrite("Data/test.png", img)

            # Convert point map (m) to array and save it.
            pm = np.array(x.GetPointMap(), copy=False).reshape(-1, 3)
            np.savetxt("Data/point_map.xyz", pm)
            print("Save point map successed!")
        else:
            print("RVC X Camera capture %dth image failed!" % i)
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
