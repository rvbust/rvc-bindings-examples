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

    # Capture a point map and a image.
    ret2 = x.Capture()

    # Create saving address of image and point map.
    save_address = "Data"
    TryCreateDir(save_address)

    if ret2 == True:
        print("RVC X Camera capture successed!")

        # Get image data and image size.
        img = x.GetImage()
        width = img.GetSize().cols
        height = img.GetSize().rows
        print("width=%d, height=%d" % (width, height))

        # Get image type. 
        # Mono camera type is RVC.ImageTypeEnum.Mono8
        # Color camera type is RVC.ImageTypeEnum.RGB8 or RVC.ImageTypeEnum.BGR8
        img_type = img.GetType()

        # Convert image to array and save it.
        img = np.array(img, copy=False)
        cv2.imwrite("Data/test.png", img)
        print("Save image successed!")

        # Convert point map (m) to array and save it.
        pm = np.array(x.GetPointMap(), copy=False).reshape(-1, 3)
        np.savetxt("Data/test.xyz", pm)
        print("Save point map successed!")
        pm = pm.reshape((height, width, 3))
        px = height // 2
        py = width // 2

        # Get each 2D image points pixel value
        if img_type == RVC.ImageTypeEnum.Mono8:
            print("image pixel value at position (x,y)=(%d,%d) is (%d)" %
                  (px, py, img[px, py]))
        else:
            print("image pixel valud at position (x,y)=(%d,%d) is (%d,%d,%d)" %
                  (px, py, img[px, py, 0], img[px, py, 1], img[px, py, 2]))
        # Get each 3D points value
        print("corresponse xyz in point map is(%.6f, %.6f, %.6f)" %
              (pm[px, py, 0], pm[px, py, 1], pm[px, py, 2]))
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

    # Shutdwwn RVC X System.
    RVC.SystemShutdown()

    return 0


if __name__ == "__main__":
    App()
