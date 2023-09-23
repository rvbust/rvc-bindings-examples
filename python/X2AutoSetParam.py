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
    # Transform point map's coordinate to left/right(RVC.CameraID_Left/RVC.CameraID_Right) camera or reference
    # plane(RVC.CameraID_NONE)
    cap_opt.transform_to_camera = RVC.CameraID_Left
    # Set 2d and 3d exposure time. Capture with white light, range [11, 100]ms, others [3, 100]ms.
    cap_opt.exposure_time_2d = 20
    cap_opt.exposure_time_3d = 100
    # Set 2d and 3d gain. the default value is 0. The gain value of each series cameras is different, you can call function GetGainRange() to get specific range.
    cap_opt.gain_2d = 0
    cap_opt.gain_3d = 0
    # Set 2d and 3d gamma. the default value is 1. The gamma value of each series cameras is different, you can call function GetGammaRange() to get specific range.
    cap_opt.gamma_2d = 1
    cap_opt.gamma_3d = 1
    # range in [0, 10]. the default value is 3. The contrast of point less than this value will be treat * as invalid point and be removed.
    cap_opt.light_contrast_threshold = 3
    # edge control after point matching, range in [0, 10], default = 2. The big the value, the more edge * noise to be
    # removed.
    cap_opt.edge_noise_reduction_threshold = 0
    # Set projector color. the default value is RVC.ProjectorColor_Blue.
    cap_opt.projector_color = RVC.ProjectorColor_Blue

    # ROI Setting
    start_x = 10
    start_y = 10
    width = 200
    height = 200

    roi = RVC.ROI(start_x, start_y, width, height)

    # Get auto capture setting, exposure_time_2d, exposure_time_3d, projector_brightness,
    # light_contrast_threshold will be adjusted automatically
    ret2, cap_opt = x.GetAutoCaptureSetting(cap_opt, roi)

    if ret2:
        print("get auto capture setting success!")
        print("auto exposure_time_2d: {} ms".format(cap_opt.exposure_time_2d))
        print("auto exposure_time_3d: {} ms".format(cap_opt.exposure_time_3d))
        print("auto projector_brightness: {}".format(cap_opt.projector_brightness))
        print("auto light_contrast_threshold: {}".format(cap_opt.light_contrast_threshold))
    else:
        print("get auto capture setting failed, custom setting will be used.")

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
        x.Close()
        RVC.X2.Destroy(x)
        RVC.SystemShutdown()
        exit(0)
    # Close RVC X Camera
    x.Close()

    # Destroy RVC X Camera
    RVC.X2.Destroy(x)

    # Shut Down RVC X System
    RVC.SystemShutdown()
