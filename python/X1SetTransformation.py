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
        print("Can not find any RVC X  Camera!")
        RVC.SystemShutdown()
        return 1
    print("devices size =%d" % len(devices))

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

    # Set custom transformation.To get your transformation,please see GetCaliBoardPose.py
    # Note: coordinate select here should be the same as the capture setting when you
    #       get your transformation. The correctness of transformation matrix will be check
    #       in SetCustomTransformation()
    transformation = np.array([[-0.99532179, -0.0892033, -0.03711218,  0.26125841],
                               [-0.08950467, 0.99596495, 0.00653654,   0.1388469],
                               [0.03637935,  0.00982767, -0.99928973,  0.99669197],
                               [0.,          0.,         0.,           1.]])

    custom_transform_opt = RVC.X1_CustomTransformOptions()
    custom_transform_opt.coordinate_select = RVC.X1CustomTransformCoordinate.CoordinateSelect_CaliBoard
    custom_transform_opt.SetTransform(transformation)
    ret2 = x.SetCustomTransformation(custom_transform_opt)

    if ret2:
        print("set transformation success")
    else:
        print("set transformation failed!custom transformation will not be used!")

    # Set capture parameters
    cap_opt = RVC.X1_CaptureOptions()
    # Transform point map's coordinate to left/right(RVC.CameraID_Left/RVC.CameraID_Right) camera or reference
    # plane(RVC.CameraID_NONE)
    cap_opt.transform_to_camera = True
    # Set camera exposure time (3~100) ms
    cap_opt.exposure_time_2d = 20
    cap_opt.exposure_time_3d = 20

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

        # Check the camera color information.
        print("width=%d, height=%d" % (width, height))
        if img.GetType() == RVC.ImageTypeEnum.Mono8:
            print("This is mono camera")
        else:
            print("This is color camera")

        # Convert image to array and save it.
        img = np.array(img, copy=False)
        cv2.imwrite("Data/test.png", img)
        print("Save image successed!")

        # Convert point map to array and save it.
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
