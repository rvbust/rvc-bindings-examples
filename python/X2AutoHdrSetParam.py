import PyRVC as RVC
import numpy as np
import cv2
import os

if __name__ == "__main__":
    # Initialize RVC X system
    RVC.SystemInit()

    # Choose RVC X Camera type (USB, GigE or All)
    opt = RVC.SystemListDeviceTypeEnum.All

    # Scan all RVC X Camera devices
    ret, devices = RVC.SystemListDevices(opt)
    print("RVC X Camera devices number:", len(devices))

    # Find whether any RVC X Camera is connected or not
    if len(devices) == 0:
        print("Can not find any RVC X Camera!")
        RVC.SystemShutdown()
        exit(1)

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

    # Set capture parameters
    cap_opt = RVC.X2_CaptureOptions()

    # ROI Setting
    roi = RVC.ROI(10, 10, 200, 200)

    # get hdr exposure parameters.
    ret2, cap_opt = x.GetAutoHdrCaptureSetting(cap_opt, roi)
    if ret2:
        print(f"projector_brightness: {cap_opt.projector_brightness}")
        if cap_opt.hdr_exposure_times == 0:
            print("hdr exposure setting will not be used")
            print("exposure_time_3d: {}".format(cap_opt.exposure_time_3d))
        else:
            print("hdr_exposure_times: {}".format(cap_opt.hdr_exposure_times))
            for i in range(cap_opt.hdr_exposure_times):
                print("hdr exposure index: {} exposure time: {}".format(
                    i + 1, cap_opt.GetHDRExposureTimeContent(i + 1)))

        # Capture a point map and a image.
        ret3 = x.Capture(cap_opt)

        # Create saving address of image and point map.
        save_dir = "Data"
        if not os.path.exists(save_dir):
            os.makedirs(save_dir)

        if ret3 == True:
            # Get image data. choose left or right side. the point map is map to left image.
            img = x.GetImage(RVC.CameraID_Left)

            # Convert image to array and save it.
            img = np.array(img, copy=False)
            cv2.imwrite("{}/test.png".format(save_dir), img)
            print("Save image successed!")

            # Convert point map (m) to array and save it.
            pm = np.array(x.GetPointMap(), copy=False).reshape(-1, 3)
            np.savetxt("{}/test.xyz".format(save_dir), pm)
            print("Save point map successed!")
        else:
            print("RVC X Camera capture failed!")
    else:
        print("get auto capture setting failed, custom setting will be used.")

    # Close RVC X Camera
    x.Close()

    # Destroy RVC X Camera
    RVC.X2.Destroy(x)

    # Shut Down RVC X System
    RVC.SystemShutdown()
