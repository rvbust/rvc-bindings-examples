# Copyright (c) RVBUST, Inc - All rights reserved.
import PyRVC as RVC
import os
import numpy as np


# Create a directory.
def TryCreateDir(d):
    if not os.path.exists(d):
        os.makedirs(d)
        return 1
    else:
        return 0

def UseX1():
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

    # Save CameraSetting
    ret1 = x.SaveSettingToFile("d://test.json")
    if(ret1 == False):
        print("RVC Camera failed to SaveSettingToFile !" )
        RVC.X1.Destroy(x)
        RVC.SystemShutdown()
        return 1

    # Load CameraSetting
    ret1 = x.LoadSettingFromFile("d://test.json")
    if(ret1 == False):
        print("RVC Camera failed to LoadSettingFromFile !" )
        RVC.X1.Destroy(x)
        RVC.SystemShutdown()
        return 1

     # Load CaptureOptions
    ret, x1_opts= x.LoadCaptureOptionParameters()

     # Test RVC X Camera is opened or not.
    if ret1 == False:
        print("RVC X Camera is not opened!")
        RVC.X1.Destroy(x)
        RVC.SystemShutdown()
        return 1
    
    
    # Capture a point map and a image.
    ret2 = x.Capture(x1_opts)

    
    if ret2 == True:
        print("RVC X Camera capture successed!")
        # Get image data.
        image = x.GetImage()
    
        # Get point map data (m).
        pm = x.GetPointMap()
        
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


def UseX2():
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

    # Create a RVC X Camera
    x = RVC.X2.Create(devices[0])

    # Test RVC X Camera is valid or not
    if x.IsValid() == False:
        print("RVC X Camera is not valid!")
        RVC.X2.Destroy(x)
        RVC.SystemShutdown()
        exit(1)

    # Open RVC X Camera
    ret1 = x.Open()

    # Test RVC X Camera is opened or not
    if x.IsOpen() == False:
        print("RVC X Camera is not opened!")
        RVC.X2.Destroy(x)
        RVC.SystemShutdown()
        exit(1)

    ret1 = x.SaveSettingToFile("d://test.json")
    if(ret1 == False):
        print("RVC Camera failed to SaveSettingToFile !" )
        RVC.X2.Destroy(x)
        RVC.SystemShutdown()
        return 1

    # Load CameraSetting
    ret1 = x.LoadSettingFromFile("d://test.json")
    if(ret1 == False):
        print("RVC Camera failed to LoadSettingFromFile !" )
        RVC.X2.Destroy(x)
        RVC.SystemShutdown()
        return 1

    # Close RVC X Camera.
    x.Close()

    # Destroy RVC X Camera.
    RVC.X2.Destroy(x)

    # Shutdown RVC X System.
    RVC.SystemShutdown()

    return 0

if __name__ == "__main__":
    UseX1()
    UseX2()
