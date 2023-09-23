# Copyright (c) RVBUST, Inc - All rights reserved.
import PyRVC as RVC
import numpy as np
import os
# Make sure you install the opencv-python.
import cv2


# Create directory.
def TryCreateDir(d):
    if not os.path.exists(d):
        os.makedirs(d)
        return 1
    else:
        return 0


def SavePointMapWithNormal(pm, normal, p_sz, save_path):
    with open(save_path, "w") as f:
        f.write("{}".format("ply"))
        f.write("\n{}".format("format ascii 1.0"))
        f.write("\n{}".format("comment Created by Rvbust, Inc"))
        f.write("\nelement vertex {}".format(p_sz))
        f.write("\n{}".format("property float x"))
        f.write("\n{}".format("property float y"))
        f.write("\n{}".format("property float z"))
        f.write("\n{}".format("property float nx"))
        f.write("\n{}".format("property float ny"))
        f.write("\n{}".format("property float nz"))
        f.write("\n{}\n".format("end_header"))
        for i in range(p_sz):
            f.write("{} {} {} {} {} {}\n".format(
                pm[i, 0], pm[i, 1], pm[i, 2], normal[i, 0], normal[i, 1], normal[i, 2]))
    f.close()
    return


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

    # Set capture parameters.
    cap_opt = RVC.X1_CaptureOptions()

    # Transform point map's coordinate to camera or reference plane.
    cap_opt.transform_to_camera = True

    # Set noise points filter range (0~30).
    cap_opt.filter_range = 0

    # Set camera exposure time (3~100) ms.
    cap_opt.exposure_time_2d = 30
    cap_opt.exposure_time_3d = 30

    # Calculate normal or not.
    cap_opt.calc_normal = True

    # Neighborhood radius in pixel of calculating normal, > 0.
    cap_opt.calc_normal_radius = 5

    # Capture a point map and a image with default setting.
    ret2 = x.Capture(cap_opt)

    # Create saving address of image and point map.
    save_address = "Data"
    TryCreateDir(save_address)

    if ret2 == True:
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

        # Convert point map (m) and normals to array and save it.
        pm = x.GetPointMap()

        normals = pm.GetNormalDataPtr()
        # Modified the usage of normals
        # normals = normals.reshape(-1, 3)
        normals = np.array(normals, copy=False).reshape(-1, 3)

        pm = np.array(pm, copy=False).reshape(-1, 3)
        SavePointMapWithNormal(pm, normals, height*width, "Data/test.ply")
        print("Save point map with normal successed!")

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


if __name__ == '__main__':
    App()
