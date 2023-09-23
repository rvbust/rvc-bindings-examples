# Copyright (c) RVBUST, Inc - All rights reserved.
import PyRVC as RVC
import sys
import os
import numpy as np
import cv2

from Utils.CaliBoardUtils import *



def App(gamma, pattern_type):

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
    #
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
    # Set camera exposure time (3~100) ms
    cap_opt.exposure_time_2d = 15
    cap_opt.exposure_time_3d = 15
    # Set 2d and 3d gain. the default value is 0. The gain value of each series cameras is different, you can call function GetGainRange() to get specific range.
    cap_opt.gain_2d = 0
    cap_opt.gain_3d = 0
    # Set 2d and 3d gamma. the default value is 1. The gamma value of each series cameras is different, you can call function GetGammaRange() to get specific range.
    cap_opt.gamma_2d = 1
    cap_opt.gamma_3d = 1
    # range in [0, 10], default = 5. The contrast of point less than this value will be treat * as invalid point and be removed.
    cap_opt.light_contrast_threshold = 3
    # edge control after point matching, range in [0, 10], default = 2. The big the value, the more edge * noise to be
    # removed.
    cap_opt.edge_noise_reduction_threshold = 1

    # Capture a point map and a image.
    ret2 = x.Capture(cap_opt)

    # Create saving address of image and point map.
    save_dir = "Data"
    if not os.path.exists(save_dir):
        os.makedirs(save_dir)

    if ret2 == True:
        # Here should always be left to get correct 2D-3D mapping
        img = x.GetImage(RVC.CameraID_Left)
        # Convert image to array and save it.
        img = np.array(img, copy=False)
        cv2.imwrite("{}/test.png".format(save_dir), img)
        print("Save image successed!")
        # Convert point map (m) to array and save it.
        pm = np.array(x.GetPointMap(), copy=False).reshape(-1, 3)
        np.savetxt("{}/test.xyz".format(save_dir), pm)
        print("Save point map successed!")

        # Get cali borad pose by image and point cloud
        cali_board_pose = GetCaliBoardPose(img,
                                           pm,
                                           gamma=gamma,
                                           m_type=pattern_type)
        if cali_board_pose is not None:
            print("transformation:{}".format(np.linalg.inv(cali_board_pose)))
            print("This transformation helps you transform point cloud from left camera coordinate of X2 to cali board coordinate")
        else:
            print("Get pose failed!")
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


if __name__ == "__main__":
    """
        This demo shows how to get cali borad pose based on the X2 left camera coordinate.
        For more details about order of circles center please see OpenCV documentation of 
        api findCirclesGrid().

        argv[1]: gamma (gamma>0), for adjust image brightness. gamma>1 will increse image brightness
                 and gamma<1 will decrease image brightness
        argv[2]: pattern_type, type of cali board pattern used. You can choose A2,A3, ..., A10
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

        Please select a cali board pattern of appropriate size according to the working distance
        of 3D camera. For details, please consult technical support.
    """

    if len(sys.argv) != 3:
        sys.exit("Invalid arguments: Usage: python3 GetCaliBoardPose.py 1 A4")

    gamma = sys.argv[1]
    pattern_type = sys.argv[2]

    print("gamma:{},pattern_type:{}".format(gamma, pattern_type))

    gamma = float(gamma)
    App(gamma, pattern_type)