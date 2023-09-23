# Copyright (c) RVBUST, Inc - All rights reserved.
import PyRVC as RVC
import sys
import os
import numpy as np
import cv2

from Utils.CaliBoardUtils import *


def App(gamma, pattern_type, capture_times):

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
    x = RVC.X1.Create(devices[0])

    # Test RVC X Camera is valid or not
    if x.IsValid() == False:
        print("RVC X Camera is not valid!")
        RVC.X1.Destroy(x)
        RVC.SystemShutdown()
        exit(1)

    # Open RVC X Camera
    ret1 = x.Open()

    # Test RVC X Camera is opened or not
    if x.IsOpen() == False:
        print("RVC X Camera is not opened!")
        RVC.X1.Destroy(x)
        RVC.SystemShutdown()
        exit(1)

    # Set capture parameters
    cap_opt = RVC.X1_CaptureOptions()
    # Choose point map's coordinate. True for camera coordinate and False for cali board coordinate
    cap_opt.transform_to_camera = True
    # Set 2d and 3d exposure time. Capture with white light, range [11, 100]ms, others [3, 100]ms.
    cap_opt.exposure_time_2d = 20
    cap_opt.exposure_time_3d = 20

    # Create saving address of image and point map.
    save_dir = "Data"
    if not os.path.exists(save_dir):
        os.makedirs(save_dir)

    valid_cnt = 0
    fail_cnt = 0
    err_list = []

    i = 0
    while valid_cnt < capture_times and fail_cnt < 5:
        # Capture a point map and a image.
        ret2 = x.Capture(cap_opt)
        if ret2 == True:
            # Get image data.
            img = x.GetImage()
            # Convert image to array
            img = np.array(img, copy=False)
            pm = np.array(x.GetPointMap(), copy=False).reshape(-1, 3)

            if 0 == i:
                # Save image and point map data, only save once to save time and space
                cv2.imwrite("{}/test.png".format(save_dir), img)
                print("Save image successed!")

                np.savetxt("{}/test.xyz".format(save_dir), pm)
                print("Save point map successed!")

            # Calculate accuracy by image and point cloud.
            ret3, err_list_mm = CalcAccuracy(img,
                                             pm,
                                             gamma=gamma,
                                             m_type=pattern_type)
            if ret3:
                valid_cnt += 1
                err_list.append(np.mean(err_list_mm))
                print(
                    f"{valid_cnt} times accuracy test, mean error: {np.mean(err_list_mm)} mm, max_error: {np.max(err_list_mm)} mm")
            else:
                fail_cnt += 1

        else:
            fail_cnt += 1

        i += 1

    if len(err_list) > 0:
        PlotError(err_list)

    else:
        print("no valid result, please adjust param as suggested!")

    # Close RVC X Camera
    x.Close()

    # Destroy RVC X Camera
    RVC.X1.Destroy(x)

    # Shut Down RVC X System
    RVC.SystemShutdown()


if __name__ == "__main__":
    """
        This demo shows how to get X2 accuracy.
        argv[1]: gamma (0~1), for adjust image brightness. gamma>1 will increse image brightness
                 and gamma<1 wille decrease image brightness
        argv[2]: pattern_type, type of cali board pattern used. You can choose A2, A3, ..., A10
                 Center distance of circles on cali borad (m):
                 A2:0.08
                 A3:0.056
                 A4:0.04
                 A5:0.028
                 A6:0.02
                 A7:0.014
                 A8:0.01
                 A9:0.007
                 A10:0.0048
        argv[3]: capture times, 10 - 100 recommended. Average error of N capture times will be returned
                 as result
        Please select a cali board pattern of appropriate size according to the working distance
        of 3D camera. For details, please consult technical support.
    """

    if len(sys.argv) != 4:
        sys.exit("Invalid arguments: Usage: python3 X1TestAccuracy.py 1 A4 10")

    gamma = sys.argv[1]
    pattern_type = sys.argv[2]
    capture_times = sys.argv[3]

    print("gamma: {}, pattern_type: {}, capture_times: {}".format(
        gamma, pattern_type, capture_times))

    gamma = float(gamma)
    capture_times = int(capture_times)
    App(gamma, pattern_type, capture_times)
