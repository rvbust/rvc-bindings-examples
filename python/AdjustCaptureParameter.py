# Copyright (c) RVBUST, Inc - All rights reserved.
import PyRVC as RVC
import numpy as np
import os
# Make sure you install the opencv-python.
import cv2


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


def SavePointMap(pm, p_sz, save_path):
    with open(save_path, "w") as f:
        f.write("{}".format("ply"))
        f.write("\n{}".format("format ascii 1.0"))
        f.write("\n{}".format("comment Created by Rvbust, Inc"))
        f.write("\nelement vertex {}".format(p_sz))
        f.write("\n{}".format("property float x"))
        f.write("\n{}".format("property float y"))
        f.write("\n{}".format("property float z"))
        f.write("\n{}\n".format("end_header"))
        for i in range(p_sz):
            f.write("{} {} {}\n".format(
                pm[i, 0], pm[i, 1], pm[i, 2]))
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

    # Whether calculate 3D points normal vector
    cap_opt.calc_normal = False
    # calculate normal radius
    cap_opt.calc_normal_radius = 5

    # Transform point map's coordinate to camera or reference plane.
    cap_opt.transform_to_camera = True

    # Set noise points filter range (0~30).
    cap_opt.filter_range = 0

    # Set phase filter range (0~40)
    cap_opt.phase_filter_range = 0

    # Set projector brightness (1~240)
    cap_opt.projector_brightness = 240

    # Set 2d and 3d exposure time (3~100) ms.
    cap_opt.exposure_time_2d = 30
    cap_opt.exposure_time_3d = 30

    # Set 2d and 3d gain. the default value is 0. The gain value of each series cameras is different, you can call function GetGainRange() to get specific range.
    cap_opt.gain_2d = 0
    cap_opt.gain_3d = 0

    # Set 2d and 3d gamma. the default value is 1. The gamma value of each series cameras is different, you can call function GetGammaRange() to get specific range.
    cap_opt.gamma_2d = 1
    cap_opt.gamma_3d = 1

    # For color camera, it needs only once auto white balance before the first capture when the light condition of scene has no big change.
    # white_balace_times is how many images used for automatic calculate the white balance parameters. range (0, 20). we commend 10 times for usual case.
    use_auto_white_balance = False
    if use_auto_white_balance:
        white_balace_times = 10
        ret2 = x.AutoWhiteBalance(white_balace_times)
        if ret2:
            print("Success AutoWhiteBalance")
        else:
            print("Failed AutoWhiteBalance")

    # Set camera bandwidth [0.3, 1]
    ret3 = x.SetBandwidth(0.5)
    if not ret3:
        print("Failed SetBandwidth")
    else:
        print("Success SetBandwidth")
        
    # Set 2d image whether use projector. Only gray camera setting this option work.
    cap_opt.use_projector_capturing_2d_image = True

    # Capture a point map and a image with default setting.
    ret4 = x.Capture(cap_opt)

    # Create saving address of image and point map.
    save_address = "Data"
    TryCreateDir(save_address)

    if ret4:
        print("RVC X Camera capture successed!")

        # Get image data.
        img = x.GetImage()
        width = img.GetSize().cols
        height = img.GetSize().rows

        # Get image size and color information.
        print("width=%d, height=%d" % (width, height))
        img_type = img.GetType()
        if img_type == RVC.ImageTypeEnum.Mono8:
            print("This is mono camera")
        else:
            print("This is color camera")

        # convert image to array and save it.
        img = np.array(img, copy=False)
        cv2.imwrite("Data/image.png", img)
        print("Save image successed!")

        # Get point map data (m) and save it.
        if cap_opt.calc_normal:
            pm = x.GetPointMap()

            normals = pm.GetNormalDataPtr()
            # Modified the usage of normals
            # normals = normals.reshape(-1, 3)
            normals = np.array(normals, copy=False).reshape(-1, 3)

            pm = np.array(pm, copy=False).reshape(-1, 3)
            SavePointMapWithNormal(pm, normals, height*width, "Data/test.ply")
        else:
            pm = np.array(x.GetPointMap(), copy=False).reshape(-1, 3)
            SavePointMap(pm,  height*width, "Data/test.ply")
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


if __name__ == '__main__':
    App()
