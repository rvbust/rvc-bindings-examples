# Copyright (c) RVBUST, Inc - All rights reserved.
import PyRVC
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

    # Find Device

    # Method 1,Find device by index.
    ret, devices = RVC.SystemListDevices(RVC.SystemListDeviceTypeEnum.All)
    if len(devices) == 0:
        print("Can not find any Device!")
        RVC.SystemShutdown()
        return -1
    device = devices[0]

    # Method 2,Find device by sn.
    # This is the most recommended method when you have multiple cameras.
    # device = RVC.SystemFindDevice("M2GM012W019")

    ret, info = device.GetDeviceInfo()
    print(info.name + "-" + info.sn)

    if not info.support_x2:
        print("Device does not support x2 function !")
        RVC.SystemShutdown()
        return -1

    # Create and Open
    x2 = RVC.X2.Create(device)
    ret = x2.Open()
    if ret and x2.IsValid():
        print("Camera is valid!")
    else:
        print("Camera is not valid!")
        RVC.X2.Destroy(x2)
        RVC.SystemShutdown()
        return -1

    # Capture
    ret = x2.Capture()
    if ret:
        print("Capture successed!")
    else:
        print("Capture failed!")
        x2.Close()
        RVC.X2.Destroy(x2)
        RVC.SystemShutdown()
        return -1

    # Data Process
    save_address = "Data"
    TryCreateDir(save_address)
    save_address += "/" + info.sn
    TryCreateDir(save_address)
    save_address += "/x2"
    TryCreateDir(save_address)

    img = x2.GetImage(PyRVC.CameraID_Left)
    pm = x2.GetPointMap()

    pm.Save(save_address + "/pointmap.ply", RVC.PointMapUnitEnum.Millimeter, True)
    pm.SaveWithImage(save_address + "/pointmap_color.ply", img, RVC.PointMapUnitEnum.Millimeter, True)
    img.SaveImage(save_address + "/image.png")

    # numpy extension
    img_np = np.array(img, copy=False)
    pm_np = np.array(pm, copy=False).reshape(-1, 3)
    size = img_np.size

    # Release
    x2.Close()
    RVC.X2.Destroy(x2)
    RVC.SystemShutdown()

    return 0


if __name__ == "__main__":
    App()
