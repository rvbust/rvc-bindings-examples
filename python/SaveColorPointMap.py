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


# Save PointMap to pm_path.
def SavePlyFile(pm_path, pm, image):
    width = pm.GetSize().width
    height = pm.GetSize().height
    pm_num = width * height
    pm_ptr = np.array(pm, copy=False).reshape((-1, 3))
    image_ptr = np.array(image, copy=False)
    if image.GetType() == RVC.ImageTypeEnum.Mono8:
        tmp = image_ptr.copy().flatten()
        image_ptr = np.zeros((height * width, 3))
        image_ptr[:, 0] = tmp
        image_ptr[:, 1] = tmp
        image_ptr[:, 2] = tmp
    else:
        image_ptr = image_ptr.reshape(-1, 3)
        if image.GetType() == RVC.ImageTypeEnum.BGR8:
            image_ptr[:, [0, 2]] = image_ptr[:, [2, 0]]
    data = np.concatenate((pm_ptr, image_ptr), axis=1)
    np.savetxt(pm_path, data, fmt = '%f %f %f %d %d %d')
    with open(pm_path, 'r+') as f:
        old = f.read()
        f.seek(0)
        f.write("{}".format("ply"))
        f.write("\n{}".format("format ascii 1.0"))
        f.write("\n{}".format("comment Created by Rvbust, Inc"))
        f.write("\nelement vertex {}".format(pm_num))
        f.write("\n{}".format("property float x"))
        f.write("\n{}".format("property float y"))
        f.write("\n{}".format("property float z"))
        f.write("\n{}".format("property uchar red"))
        f.write("\n{}".format("property uchar green"))
        f.write("\n{}".format("property uchar blue"))
        f.write("\n{}\n".format("end_header"))
        f.write(old)
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

        # Get image data.
        image = x.GetImage()

        # Get point map data (m).
        pm = x.GetPointMap()
        pm_path = "Data/test.ply"
        SavePlyFile(pm_path, pm, image)
        print("save color point map to file:%s" % pm_path)
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
