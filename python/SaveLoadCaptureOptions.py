# Copyright (c) RVBUST, Inc - All rights reserved.
import PyRVC as RVC
import os
import numpy as np


def PrintCaptureOptionX1(x1):
    print("x1.calc_normal =", x1.calc_normal)
    print("x1.transform_to_camera =", x1.transform_to_camera)
    print("x1.filter_range =", x1.filter_range)
    print("x1.phase_filter_range =", x1.phase_filter_range)
    print("x1.projector_brightness =", x1.projector_brightness)
    print("x1.exposure_time_2d =", x1.exposure_time_2d)
    print("x1.exposure_time_3d =", x1.exposure_time_3d)
    print("x1.gain_2d =", x1.gain_2d)
    print("x1.gain_3d =", x1.gain_3d)
    print("x1.hdr_exposure_times =", x1.hdr_exposure_times)
    print("x1.hdr_exposure_times[1] =", x1.GetHDRExposureTimeContent(1))
    print("x1.hdr_exposure_times[2] =", x1.GetHDRExposureTimeContent(2))
    print("x1.hdr_exposure_times[3] =", x1.GetHDRExposureTimeContent(3))
    print("x1.calc_normal_radius =", x1.calc_normal_radius)
    print("x1.gamma_2d =", x1.gamma_2d)
    print("x1.gamma_3d =", x1.gamma_3d)
    print("x1.use_projector_capturing_2d_image =", x1.use_projector_capturing_2d_image)
    print("x1.smoothness =", x1.smoothness)
    print("x1.downsample_distance =", x1.downsample_distance)

def PrintCaptureOptionX2(x2):
    print("x2.transform_to_camera =", x2.transform_to_camera)
    print("x2.projector_brightness =", x2.projector_brightness)
    print("x2.calc_normal =", x2.calc_normal)
    print("x2.calc_normal_radius =", x2.calc_normal_radius)
    print("x2.light_contrast_threshold =", x2.light_contrast_threshold)
    print("x2.edge_noise_reduction_threshold =", x2.edge_noise_reduction_threshold)
    print("x2.exposure_time_2d =", x2.exposure_time_2d)
    print("x2.exposure_time_3d =", x2.exposure_time_3d)
    print("x2.gain_2d =", x2.gain_2d)
    print("x2.gain_3d =", x2.gain_3d)
    print("x2.hdr_exposure_times =", x2.hdr_exposure_times)
    print("x2.hdr_exposure_times[1] =", x2.GetHDRExposureTimeContent(1))
    print("x2.hdr_exposure_times[2] =", x2.GetHDRExposureTimeContent(2))
    print("x2.hdr_exposure_times[3] =", x2.GetHDRExposureTimeContent(3))
    print("x2.gamma_2d =", x2.gamma_2d)
    print("x2.gamma_3d =", x2.gamma_3d)
    print("x2.projector_color =", x2.projector_color)
    print("x2.use_projector_capturing_2d_image =", x2.use_projector_capturing_2d_image)
    print("x2.smoothness =", x2.smoothness)
    print("x2.downsample_distance =", x2.downsample_distance)

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

    # Save CaptureOptions
    x1_save_opts = RVC.X1_CaptureOptions()
    x1_save_opts.exposure_time_3d = 20
    x1_save_opts.exposure_time_2d = 21
    x.SaveCaptureOptionParameters(x1_save_opts)

    # Load CaptureOptions
    ret, x1_opts= x.LoadCaptureOptionParameters()
    PrintCaptureOptionX1(x1_opts)

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

    # Set capture parameters
    cap_opt = RVC.X2_CaptureOptions()
    # Transform point map's coordinate to left/right(RVC.CameraID_Left/RVC.CameraID_Right) camera or reference
    # plane(RVC.CameraID_NONE)
    cap_opt.transform_to_camera = RVC.CameraID_Left
    # Set camera exposure time (3~100) ms
    cap_opt.exposure_time_2d = 20
    cap_opt.exposure_time_3d = 20
    # range in [0, 10]. the default value is 3. The contrast of point less than this value will be treat * as invalid point and be removed.
    cap_opt.light_contrast_threshold = 2
    # edge control after point matching, range in [0, 10], default = 2. The big the value, the more edge * noise to be
    # removed.
    cap_opt.edge_noise_reduction_threshold = 0
    # Set projector color, defult is RVC.ProjectorColor_Blue
    cap_opt.projector_color = RVC.ProjectorColor_Blue
    x.SaveCaptureOptionParameters(cap_opt)

    # Load CaptureOptions
    ret, x2_opts= x.LoadCaptureOptionParameters()
    PrintCaptureOptionX2(x2_opts)

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
