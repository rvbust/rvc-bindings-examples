# Copyright (c) RVBUST, Inc - All rights reserved.
import PyRVC as RVC
import os
import numpy as np
import cv2


# Create a directory.color
def TryCreateDir(d):
    if not os.path.exists(d):
        os.makedirs(d)


def App():

    # Initialize RVC X system.
    RVC.SystemInit()

    # Choose RVC X Camera type (USB, GigE or All)
    opt = RVC.SystemListDeviceTypeEnum.USB

    # Scan all RVC X GigE Camera devices.
    ret, devices = RVC.SystemListDevices(opt)

    #  Find whether any RVC X GigE Camera is connected or not.
    if len(devices) == 0:
        print("Can not find any RVC X Camera!")
        RVC.SystemShutdown()
        return 1

    # Create a RVC X Camera and choose use left side camera.
    x = RVC.X1.Create(devices[0], RVC.CameraID_Left)

    # Test RVC X Camera is valid or not.
    if x.IsValid() is not True:
        print("RVC X Camera is not valid!")
        RVC.X1.Destroy(x)
        RVC.SystemShutdown()
        return 1

    # Open RVC X Camera.
    ret1 = x.Open()

    # Test RVC X Camera is opened or not.
    if not ret1:
        print("open camera failed!")
        RVC.X1.Destroy(x)
        RVC.SystemShutdown()
        return 1

    cap_opt = RVC.X1_CaptureOptions()
    cap_opt.noise_removal_distance = 0.5  # unit: mm
    cap_opt.noise_removal_point_number = 40

    # Capture a point map and a image.
    ret2 = x.Capture(cap_opt)

    # Create saving address of image and point map.
    save_address = "Data"
    TryCreateDir(save_address)

    if ret2 == True:
        print("RVC X Camera capture successed!")

        # Get image data and image size.
        img = x.GetImage()

        # Convert image to array and save it.
        img = np.array(img, copy=False)
        cv2.imwrite("Data/test.png", img)
        print("Save image successed!")

        # Convert point map (m) to array and save it.
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

    # Shutdown RVC X System.
    RVC.SystemShutdown()

    return 0


if __name__ == "__main__":
    App()
