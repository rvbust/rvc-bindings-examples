#include <RVC/RVC.h>

#include <iostream>

#include "IO/FileIO.h"
#include "IO/SavePointMap.h"

int main(int argc, char *argv[]) {
    // Initialize RVC X system.
    RVC::SystemInit();

	// Find Device
    RVC::Device devices[10];
    size_t actual_size = 0;
    SystemListDevices(devices, 10, &actual_size, RVC::SystemListDeviceType::All);
    if (actual_size == 0) {
        std::cout << "Can not find any Camera!" << std::endl;
        return -1;
    }
    RVC::Device device = devices[0];
	
    RVC::DeviceInfo info;
    device.GetDeviceInfo(&info);

	// Create and Open
    RVC::X1 x1 = RVC::X1::Create(device);
    x1.Open();
    if (!x1.IsOpen()) {
        std::cout << "RVC X Camera is not opened!" << std::endl;
        RVC::X1::Destroy(x1);
        RVC::SystemShutdown();
        return -1;
    }

	// Capture Options
    RVC::X1::CaptureOptions options;
    bool ret;

    std::cout << "打印拍摄参数---" << std::endl;
    {
        std::string captureMode =
            options.capture_mode == RVC::CaptureMode_Normal ? "标准模式" :
            options.capture_mode == RVC::CaptureMode_Fast ? "快速模式" :
            options.capture_mode == RVC::CaptureMode_Ultra ? "高精度模式" :
            options.capture_mode == RVC::CaptureMode_Robust ? "抗干扰模式" :
            "异常";

        std::cout << "拍摄模式--[capture_mode] = {" << captureMode << "}" << std::endl;
        std::cout << "2D 曝光时间--[exposure_time_2d] = {" << options.exposure_time_2d << "}" << std::endl;
        std::cout << "2D 增益--[gain_2d] = {" << options.gain_2d << "}" << std::endl;
        std::cout << "2D Gamma--[gamma_2d] = {" << options.gamma_2d << " }" << std::endl;
        std::cout << "2D 拍摄是否使用光机--[use_projector_capturing_2d_image] = {" << options.use_projector_capturing_2d_image << "}" << std::endl;
        std::cout << "3D 曝光时间--[exposure_time_3d] = {" << options.exposure_time_3d << "}" << std::endl;
        std::cout << "3D 增益--[gain_3d] = {" << options.gain_3d << "}" << std::endl;
        std::cout << "3D Gamma--[gamma_3d] = {" << options.gamma_3d << "}" << std::endl;
        std::cout << "光强对比度阈值--[light_contrast_threshold] = {" << options.light_contrast_threshold << "}" << std::endl;
        std::cout << "投影亮度--[projector_brightness] = {" << options.projector_brightness << "}" << std::endl;

        std::cout << "HDR 次数--[hdr_exposure_times] = {" << options.hdr_exposure_times << "}" << std::endl;
        std::cout << "HDR 曝光(0,1,2)--[hdr_exposuretime_content] = {" << options.hdr_exposuretime_content[0] << "," << options.hdr_exposuretime_content[1] << "," << options.hdr_exposuretime_content[2] << "}" << std::endl;
        std::cout << "HDR 增益(0,1,2)--[hdr_exposuretime_content] = {" << options.hdr_gain_3d[0] << "," << options.hdr_gain_3d[1] << "," << options.hdr_gain_3d[2] << "}" << std::endl;
        std::cout << "HDR 扫描次数(0,1,2)--[hdr_exposuretime_content] = {" << options.hdr_scan_times[0] << "," << options.hdr_scan_times[1] << "," << options.hdr_scan_times[2] << "}" << std::endl;
        std::cout << "HDR 投影亮度(0,1,2)--[hdr_exposuretime_content] = {" << options.hdr_projector_brightness[0] << "," << options.hdr_projector_brightness[1] << "," << options.hdr_projector_brightness[2] << "}" << std::endl;

        std::cout << "置信度去噪阈值--[confidence_threshold] = {" << options.confidence_threshold << "}" << std::endl;
        std::cout << "聚类降噪距离阈值--[noise_removal_distance] = {" << options.noise_removal_distance << "}" << std::endl;
        std::cout << "聚类降噪有效点数阈值--[noise_removal_point_number] = {" << options.noise_removal_point_number << "}" << std::endl;

        std::string smoothness =
            options.smoothness == RVC::SmoothnessLevel_Off ? "关" :
            options.smoothness == RVC::SmoothnessLevel_Weak ? "弱" :
            options.smoothness == RVC::SmoothnessLevel_Normal ? "中" :
            options.smoothness == RVC::SmoothnessLevel_Strong ? "强" :
            "异常";
        std::cout << "平滑等级--[smoothness] = {" << smoothness << "}" << std::endl;
        std::cout << "下采样距离(m)--[downsample_distance] = {" << options.downsample_distance << "}" << std::endl;
        std::cout << "是否计算法向量--[calc_normal] = {" << options.calc_normal << "}" << std::endl;
        std::cout << "计算法向量距离--[calc_normal_radius] = {" << options.calc_normal_radius << "}" << std::endl;

        std::cout << "ROI(x,y,w,h)--[roi] = {" << options.roi.x << "," << options.roi.y << "," << options.roi.width << "," << options.roi.height << "}" << std::endl;

        //G系列相机，扫描次数
        std::cout << "扫描次数[G系列相机]--[scan_times] = {" << options.scan_times << "}" << std::endl;

        //新增算法参数，双边滤波【暂不支持cuda版本】
        std::cout << "z向截断最小值--[truncate_z_min] = {" << options.truncate_z_min << "}" << std::endl;
        std::cout << "z向截断最大值--[truncate_z_max] = {" << options.truncate_z_max << "}" << std::endl;
        std::cout << "双边滤波窗口大小--[bilateral_filter_kernal_size] = {" << options.bilateral_filter_kernal_size << "}" << std::endl;
        std::cout << "双边滤波深度分布--[bilateral_filter_depth_sigma] = {" << options.bilateral_filter_depth_sigma << "}" << std::endl;
        std::cout << "双边滤波空间分布--[bilateral_filter_space_sigma] = {" << options.bilateral_filter_space_sigma << "}" << std::endl;
    }
	
	// Method 1, Use Default Options and Modify.
    {
        //options = RVC::X1::CaptureOptions();
        // todo:modify options
        //ret = x1.Capture(options);
    }

    // Method 2 , Load Options From Camera and Modify.
    {
        //x1.LoadCaptureOptionParameters(options);
        // todo:modify options
        //ret = x1.Capture(options);
    }

    // *****
    // Method 3 , Using the internal parameters of the camera.
    {
        // We suggest adjusting the camera parameters By RVC Manager.
        // Then, when we use SDK, we directly use the parameters inside the camera.
        ret = x1.Capture();
    }

    // Method 4 , Load Options From File and Capture.
    {
        // If you need to capture multiple scenes, their parameters are different.
        // You can save these parameters as different configuration files  By RVC Manager and then import the files before capture.
        // ret = x1.LoadSettingFromFile("file.json");
        // ret = x1.Capture();
    }

    if(ret == false)
    {
        x1.Close();
        RVC::X1::Destroy(x1);
        RVC::SystemShutdown();
        return -1;
    }

	// Data Process
    std::string dir = "./Data/";
    MakeDirectories(dir);
    dir += info.sn;
    MakeDirectories(dir);
    dir += "/x1";
    MakeDirectories(dir);

    RVC::PointMap pointcloud = x1.GetPointMap();
    RVC::Image image = x1.GetImage();
    pointcloud.Save((dir + "/pointcloud.ply").c_str(), RVC::PointMapUnit::Millimeter, true);
    pointcloud.Save((dir + "/pointcloud_color.ply").c_str(),RVC::PointMapUnit::Millimeter,true,image);
    image.SaveImage((dir + "/image.png").c_str());


    // Close RVC X Camera.
    x1.Close();
    RVC::X1::Destroy(x1);
    RVC::SystemShutdown();

	
    return 0;
}
