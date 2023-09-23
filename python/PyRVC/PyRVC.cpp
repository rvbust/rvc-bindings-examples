// Copyright (c) RVBUST, Inc - All rights reserved.

#include <RVC/RVC.h>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <chrono>
#include <string>
#include <vector>

#define DEVICE_MAX_NUM 16

using namespace RVC;
using namespace pybind11;

struct NormalData {
    NormalData() {}

    NormalData(double *data, RVC::Size size, bool valid) : data(data), size(size), isValid(valid) {}

    static NormalData fromPointMap(PointMap pointMap) {
        return NormalData(pointMap.GetNormalDataPtr(), pointMap.GetSize(), pointMap.GetNormalDataPtr() != nullptr);
    }

    bool IsValid() { return isValid; }

    Size GetSize() { return size; }

    bool isValid = false;
    double *data = nullptr;
    RVC::Size size = RVC::Size(0, 0);
};

PYBIND11_MODULE(PyRVC, m) {

    m.def("GetVersion", &GetVersion, call_guard<gil_scoped_release>());

    m.def("GetLastError", &GetLastError, call_guard<gil_scoped_release>());

    class_<Size>(m, "Size")
        .def(init<>(), call_guard<gil_scoped_release>())
        .def(init<int, int>(), call_guard<gil_scoped_release>())
        .def_readwrite("width", &Size::width)
        .def_readwrite("height", &Size::height)
        .def_readwrite("cols", &Size::cols)
        .def_readwrite("rows", &Size::rows);

    class_<ROI>(m, "ROI")
        .def(init<>(), call_guard<gil_scoped_release>())
        .def(init<int, int, int, int>(), call_guard<gil_scoped_release>())
        .def_readwrite("x", &ROI::x)
        .def_readwrite("y", &ROI::y)
        .def_readwrite("width", &ROI::width)
        .def_readwrite("height", &ROI::height);

    class_<ROIRange>(m, "ROIRange")
        .def(init<>(), call_guard<gil_scoped_release>())
        .def_readwrite("x_step", &ROIRange::x_step)
        .def_readwrite("y_step", &ROIRange::y_step)
        .def_readwrite("width_step", &ROIRange::width_step)
        .def_readwrite("height_step", &ROIRange::height_step)
        .def_readwrite("width_min", &ROIRange::width_min)
        .def_readwrite("height_min", &ROIRange::height_min)
        .def_readwrite("width_max", &ROIRange::width_max)
        .def_readwrite("height_max", &ROIRange::height_max);

    enum_<RVC::CameraID>(m, "CameraID")
        .value("CameraID_NONE", RVC::CameraID::CameraID_NONE)
        .value("CameraID_0", RVC::CameraID::CameraID_0)
        .value("CameraID_1", RVC::CameraID::CameraID_1)
        .value("CameraID_2", RVC::CameraID::CameraID_2)
        .value("CameraID_Left", RVC::CameraID::CameraID_Left)
        .value("CameraID_Right", RVC::CameraID::CameraID_Right)
        .value("CameraID_Both", RVC::CameraID::CameraID_Both)
        .export_values();

    enum_<RVC::PortType>(m, "PortType")
        .value("PortType_NONE", RVC::PortType::PortType_NONE)
        .value("PortType_USB", RVC::PortType::PortType_USB)
        .value("PortType_GIGE", RVC::PortType::PortType_GIGE)
        .export_values();

    enum_<RVC::CameraTempSelector>(m, "CameraTempSelector")
        .value("CameraTempSelector_Camera", RVC::CameraTempSelector::CameraTempSelector_Camera)
        .value("CameraTempSelector_CoreBoard", RVC::CameraTempSelector::CameraTempSelector_CoreBoard)
        .value("CameraTempSelector_FpgaCore", RVC::CameraTempSelector::CameraTempSelector_FpgaCore)
        .value("CameraTempSelector_Framegrabberboard", RVC::CameraTempSelector::CameraTempSelector_Framegrabberboard)
        .value("CameraTempSelector_Sensor", RVC::CameraTempSelector::CameraTempSelector_Sensor)
        .value("CameraTempSelector_SensorBoard", RVC::CameraTempSelector::CameraTempSelector_SensorBoard)
        .export_values();

    enum_<RVC::ProjectorColor>(m, "ProjectorColor")
        .value("ProjectorColor_None", RVC::ProjectorColor::ProjectorColor_None)
        .value("ProjectorColor_Red", RVC::ProjectorColor::ProjectorColor_Red)
        .value("ProjectorColor_Green", RVC::ProjectorColor::ProjectorColor_Green)
        .value("ProjectorColor_Blue", RVC::ProjectorColor::ProjectorColor_Blue)
        .value("ProjectorColor_White", RVC::ProjectorColor::ProjectorColor_White)
        .export_values();

    enum_<RVC::BalanceSelector>(m, "BalanceSelector")
        .value("BalanceSelector_None", RVC::BalanceSelector::BalanceSelector_None)
        .value("BalanceSelector_Red", RVC::BalanceSelector::BalanceSelector_Red)
        .value("BalanceSelector_Green", RVC::BalanceSelector::BalanceSelector_Green)
        .value("BalanceSelector_Blue", RVC::BalanceSelector::BalanceSelector_Blue)
        .export_values();

    enum_<RVC::NetworkType>(m, "NetworkType")
        .value("NetworkType_DHCP", RVC::NetworkType::NetworkType_DHCP)
        .value("NetworkType_STATIC", RVC::NetworkType::NetworkType_STATIC)
        .export_values();

    enum_<RVC::NetworkDevice>(m, "NetworkDevice")
        .value("NetworkDevice_LightMachine", RVC::NetworkDevice::NetworkDevice_LightMachine)
        .value("NetworkDevice_LeftCamera", RVC::NetworkDevice::NetworkDevice_LeftCamera)
        .value("NetworkDevice_RightCamera", RVC::NetworkDevice::NetworkDevice_RightCamera)
        .export_values();

    enum_<RVC::X1::CustomTransformOptions::CoordinateSelect>(m, "X1CustomTransformCoordinate")
        .value("CoordinateSelect_Disabled", RVC::X1::CustomTransformOptions::CoordinateSelect_Disabled)
        .value("CoordinateSelect_Camera", RVC::X1::CustomTransformOptions::CoordinateSelect_Camera)
        .value("CoordinateSelect_CaliBoard", RVC::X1::CustomTransformOptions::CoordinateSelect_CaliBoard)
        .export_values();

    enum_<RVC::X2::CustomTransformOptions::CoordinateSelect>(m, "X2CustomTransformCoordinate")
        .value("CoordinateSelect_Disabled", RVC::X2::CustomTransformOptions::CoordinateSelect_Disabled)
        .value("CoordinateSelect_CameraLeft", RVC::X2::CustomTransformOptions::CoordinateSelect_CameraLeft)
        .value("CoordinateSelect_CameraRight", RVC::X2::CustomTransformOptions::CoordinateSelect_CameraRight)
        .value("CoordinateSelect_CaliBoard", RVC::X2::CustomTransformOptions::CoordinateSelect_CaliBoard)
        .export_values();

    class_<RVC::DeviceInfo>(m, "DeviceInfo")
        .def_readonly("name", &RVC::DeviceInfo::name)
        .def_readonly("sn", &RVC::DeviceInfo::sn)
        .def_readonly("factroydate", &RVC::DeviceInfo::factroydate)
        .def_readonly("port", &RVC::DeviceInfo::port)
        .def_readonly("type", &RVC::DeviceInfo::type)
        .def_readonly("cameraid", &RVC::DeviceInfo::cameraid)
        .def_readonly("boardmodel", &RVC::DeviceInfo::boardmodel)
        .def_readonly("support_x2", &RVC::DeviceInfo::support_x2)
        .def_readonly("support_color", &RVC::DeviceInfo::support_color)
        .def_readonly("workingdist_near_mm", &RVC::DeviceInfo::workingdist_near_mm)
        .def_readonly("workingdist_far_mm", &RVC::DeviceInfo::workingdist_far_mm);

    class_<Device>(m, "Device")
        .def_static("Destroy", &Device::Destroy, call_guard<gil_scoped_release>())
        .def("IsValid", &Device::IsValid, call_guard<gil_scoped_release>())
        .def("Print", &Device::Print, call_guard<gil_scoped_release>())
        .def("GetDeviceInfo",
             [](Device &self) {
                 DeviceInfo info;
                 bool ret = self.GetDeviceInfo(&info);
                 return std::make_pair(ret, info);
             },
             call_guard<gil_scoped_release>())
#ifndef NOT_EXPORT_TO_USER
        .def("SetDeviceCalibrationData",
             [](Device &self, const char *left_norm, const char *left_535a, const char *right_norm,
                const char *right_535a) {
                 return self.SetDeviceCalibrationData(left_norm, left_535a, right_norm, right_535a) == 0 ? true : false;
             },
             call_guard<gil_scoped_release>())
        .def("GetDeviceCalibrationData",
             [](Device &self) {
                 char left_norm[2048], left_535A[2048], right_norm[2048], right_535A[2048];
                 memset(left_norm, 0, sizeof(char) * 2048);
                 memset(left_535A, 0, sizeof(char) * 2048);
                 memset(right_norm, 0, sizeof(char) * 2048);
                 memset(right_535A, 0, sizeof(char) * 2048);
                 int ret = self.GetDeviceCalibrationData(left_norm, left_535A, right_norm, right_535A);
                 return std::make_tuple(ret, left_norm, left_535A, right_norm, right_535A);
             },
             call_guard<gil_scoped_release>())
#endif
        .def("SetNetworkConfig",
             [](Device &self, const RVC::NetworkDevice d, const RVC::NetworkType type, const char *ip,
                const char *netMask, const char *gateway) {
                 return self.SetNetworkConfig(d, type, ip, netMask, gateway) == 0 ? true : false;
             },
             call_guard<gil_scoped_release>())
        .def("GetNetworkConfig",
             [](Device &self, const RVC::NetworkDevice d) {
                 RVC::NetworkType type;
                 char ip[16];
                 char netmask[16];
                 char gateway[16];
                 memset(ip, 0, sizeof(char) * 16);
                 memset(netmask, 0, sizeof(char) * 16);
                 memset(gateway, 0, sizeof(char) * 16);
                 int status = 0;
                 int ret = self.GetNetworkConfig(d, &type, &ip[0], &netmask[0], &gateway[0], &status);
                 return std::make_tuple(type, bytes(ip), bytes(netmask), bytes(gateway), status);
             },
             call_guard<gil_scoped_release>());

    enum_<SystemListDeviceType::Enum>(m, "SystemListDeviceTypeEnum")
        .value("USB", SystemListDeviceType::USB)
        .value("GigE", SystemListDeviceType::GigE)
        .value("All", SystemListDeviceType::All)
        .export_values();

    enum_<PointMapUnit::Enum>(m, "PointMapUnitEnum")
        .value("Meter", PointMapUnit::Meter)
        .value("Millimeter", PointMapUnit::Millimeter)
        .export_values();

    m.def("SystemListDeviceTypeToString",
          [](const SystemListDeviceType::Enum &e) { return SystemListDeviceType::ToString(e); },
          call_guard<gil_scoped_release>());

    m.def("SystemListDevices",
          [](SystemListDeviceType::Enum opt = SystemListDeviceType::USB) {
              std::vector<Device> devices(DEVICE_MAX_NUM);
              size_t actualsize = 0;
              int ret = SystemListDevices(&devices[0], DEVICE_MAX_NUM, &actualsize, opt);
              devices.resize(actualsize);
              return std::make_pair(ret, devices);
          },
          call_guard<gil_scoped_release>());

    enum_<ImageType::Enum>(m, "ImageTypeEnum")
        .value("None", ImageType::None)
        .value("Mono8", ImageType::Mono8)
        .value("RGB8", ImageType::RGB8)
        .value("BGR8", ImageType::BGR8)
        .export_values();

    m.def("ImageTypeToString", [](const ImageType::Enum &e) { return ImageType::ToString(e); },
          call_guard<gil_scoped_release>());
    m.def("ImageTypeGetPixelSize", [](const ImageType::Enum &e) { return ImageType::GetPixelSize(e); },
          call_guard<gil_scoped_release>());

    m.def("ImageCreate", [](const ImageType::Enum it, const Size &sz) { return Image::Create(it, sz, nullptr, true); },
          call_guard<gil_scoped_release>());

    m.def("ImageDestroy", [](Image &img, bool no_reuse = true) { Image::Destroy(img, no_reuse); }, "Destroy the image",
          arg("img"), arg("no_reuse") = true, call_guard<gil_scoped_release>());

    class_<Image>(m, "Image", buffer_protocol())
        .def("IsValid", &Image::IsValid, call_guard<gil_scoped_release>())
        .def("GetSize", &Image::GetSize, call_guard<gil_scoped_release>())
        .def("SaveImage", &Image::SaveImage, call_guard<gil_scoped_release>())
        .def("GetType", &Image::GetType, call_guard<gil_scoped_release>())
        // construct a proper buffer object a.k.a numpy array for Image
        // If the image is mono type, it will return a buffer object with two dimension: shape == (rows, cols)
        // if the image is 2,3,4 channels, it will return a buffer object with three dimension: shape = (rows, cols, cn)
        .def_buffer([](Image &im) -> buffer_info {
            Size size = im.GetSize();
            ImageType::Enum it = im.GetType();
            size_t cn = it;  // directly to channel type
            size_t w = size.width, h = size.height;

            if (it == 0 || w <= 0 || h <= 0)
                return buffer_info();  // return empty buffer object.

            if (it == 1) {
                return buffer_info(im.GetDataPtr(), {h, w}, {sizeof(char) * w, sizeof(char)});
            } else {
                return buffer_info(im.GetDataPtr(), {h, w, cn},
                                       {sizeof(char) * w * cn, sizeof(char) * cn, sizeof(char)});
            }
        });

    class_<DepthMap>(m, "DepthMap", buffer_protocol())
        .def(init<>(), call_guard<gil_scoped_release>())
        .def("IsValid", &DepthMap::IsValid, call_guard<gil_scoped_release>())
        .def("GetSize", &DepthMap::GetSize, call_guard<gil_scoped_release>())
        .def("SaveDepthMap", &DepthMap::SaveDepthMap, call_guard<gil_scoped_release>())
        .def_buffer([](DepthMap &self) -> buffer_info {
            Size sz = self.GetSize();
            double *p = self.GetDataPtr();
            const auto dsize = sizeof(double);

            return buffer_info(p, {sz.height, sz.width}, {dsize * sz.width * 1, dsize});
        });
    class_<ConfidenceMap>(m, "ConfidenceMap", buffer_protocol())
        .def(init<>())
        .def("IsValid", &ConfidenceMap::IsValid)
        .def("GetSize", &ConfidenceMap::GetSize)
        .def_buffer([](ConfidenceMap &self) -> buffer_info {
            Size sz = self.GetSize();
            double *p = self.GetDataPtr();
            const auto dsize = sizeof(double);

            return buffer_info(p, {sz.height, sz.width}, {dsize * sz.width * 1, dsize});
        });

    enum_<PointMapType::Enum>(m, "PointMapTypeEnum")
        .value("None", PointMapType::None)
        .value("PointsOnly", PointMapType::PointsOnly)
        .value("PointsNormals", PointMapType::PointsNormals)
        .export_values();

    m.def("PointMapTypeToString", [](const PointMapType::Enum &e) { return PointMapType::ToString(e); },
          call_guard<gil_scoped_release>());

    m.def("PointMapCreate",
          [](const PointMapType::Enum it, const Size &sz) { return PointMap::Create(it, sz, nullptr, true); },
          call_guard<gil_scoped_release>());

    m.def("PointMapDestroy", [](PointMap &img) { PointMap::Destroy(img); }, call_guard<gil_scoped_release>());

    class_<PointMap>(m, "PointMap", buffer_protocol())
        .def(init<>(), call_guard<gil_scoped_release>())
        .def("IsValid", &PointMap::IsValid, call_guard<gil_scoped_release>())
        .def("GetSize", &PointMap::GetSize, call_guard<gil_scoped_release>())

        // TODO: Implement and use protocol buffer
        .def("GetNormalDataPtr", [](PointMap &self) { return NormalData::fromPointMap(self); },
             call_guard<gil_scoped_release>())
	

        .def("Save",
            [](PointMap& self, const char* filename, PointMapUnit::Enum unit, bool isBinary) {
                bool ret = self.Save(filename, unit, isBinary, Image());
                return ret;
            },
            arg("filename") , arg("unit") = PointMapUnit::Millimeter,  arg("isBinary") = true,
            call_guard<gil_scoped_release>())


        .def("SaveWithImage",
            [](PointMap& self, const char* filename, Image image, PointMapUnit::Enum unit, bool isBinary) {
                bool ret = self.Save(filename, unit, isBinary, image);
                return ret;
            },
            arg("filename"), arg("image"),  arg("unit") = PointMapUnit::Millimeter, arg("isBinary") = true,
            call_guard<gil_scoped_release>())

        .def_buffer([](PointMap &self) -> buffer_info {
            Size sz = self.GetSize();
            double *p = self.GetPointDataPtr();
            const auto dsize = sizeof(double);

            return buffer_info(p, {sz.height, sz.width, 3}, {dsize * sz.width * 3, dsize * 3, dsize});
        });

    class_<NormalData>(m, "NormalData", buffer_protocol())
        .def(init<>(), call_guard<gil_scoped_release>())
        .def("IsValid", &NormalData::IsValid, call_guard<gil_scoped_release>())
        .def("GetSize", &NormalData::GetSize, call_guard<gil_scoped_release>())

        .def_buffer([](NormalData &self) -> buffer_info {
            Size sz = self.GetSize();
            const auto dsize = sizeof(double);
            return buffer_info(self.data, {sz.height, sz.width, 3}, {dsize * sz.width * 3, dsize * 3, dsize});
        });

    m.def("SystemInit", &SystemInit, "Initialize system.", call_guard<gil_scoped_release>());
    m.def("SystemIsInited", &SystemIsInited, "System Is Inited?", call_guard<gil_scoped_release>());
    m.def("SystemShutdown", &SystemShutdown, "Shut down the system.", call_guard<gil_scoped_release>());

    m.def("SystemFindDevice", [](const char *serialNumber) { return SystemFindDevice(serialNumber); },
          "Find the device with serial number.", arg("serialNumber"), call_guard<gil_scoped_release>());

    class_<X1::CaptureOptions>(m, "X1_CaptureOptions")
        .def(init<>(), call_guard<gil_scoped_release>())
        .def_readwrite("calc_normal", &X1::CaptureOptions::calc_normal)
        .def_readwrite("calc_normal_radius", &X1::CaptureOptions::calc_normal_radius)
        .def_readwrite("light_contrast_threshold", &X1::CaptureOptions::light_contrast_threshold)
        .def_readwrite("transform_to_camera", &X1::CaptureOptions::transform_to_camera)
        .def_readwrite("filter_range", &X1::CaptureOptions::filter_range)
        .def_readwrite("noise_removal_distance", &X1::CaptureOptions::noise_removal_distance)
        .def_readwrite("noise_removal_point_number", &X1::CaptureOptions::noise_removal_point_number)
        .def_readwrite("phase_filter_range", &X1::CaptureOptions::phase_filter_range)
        .def_readwrite("projector_brightness", &X1::CaptureOptions::projector_brightness)
        .def_readwrite("exposure_time_2d", &X1::CaptureOptions::exposure_time_2d)
        .def_readwrite("exposure_time_3d", &X1::CaptureOptions::exposure_time_3d)
        .def_readwrite("gain_2d", &X1::CaptureOptions::gain_2d)
        .def_readwrite("gain_3d", &X1::CaptureOptions::gain_3d)
        .def_readwrite("gamma_2d", &X1::CaptureOptions::gamma_2d)
        .def_readwrite("gamma_3d", &X1::CaptureOptions::gamma_3d)
        .def_readwrite("hdr_exposure_times", &X1::CaptureOptions::hdr_exposure_times)
        .def_readwrite("use_projector_capturing_2d_image", &X1::CaptureOptions::use_projector_capturing_2d_image)
        .def_readwrite("smoothness", &X1::CaptureOptions::smoothness)
        .def_readwrite("downsample_distance", &X1::CaptureOptions::downsample_distance)
        .def_readwrite("scan_times", &X1::CaptureOptions::scan_times)
        .def_readwrite("truncate_z_min", &X1::CaptureOptions::truncate_z_min)
        .def_readwrite("truncate_z_max", &X1::CaptureOptions::truncate_z_max)
        .def_readwrite("bilateral_filter_kernal_size", &X1::CaptureOptions::bilateral_filter_kernal_size)
        .def_readwrite("bilateral_filter_depth_sigma", &X1::CaptureOptions::bilateral_filter_depth_sigma)
        .def_readwrite("bilateral_filter_space_sigma", &X1::CaptureOptions::bilateral_filter_space_sigma)
        .def("GetHDRExposureTimeContent",
             [](X1::CaptureOptions &opt, int num) {
                 int exp = -1;
                 if (num > 0 && num < 4) {
                     exp = opt.hdr_exposuretime_content[num - 1];
                 }
                 return exp;
             },
             call_guard<gil_scoped_release>())
        .def("SetHDRExposureTimeContent",
             [](X1::CaptureOptions &opt, int num, int exposure_time) {
                 if (num > 0 && num < 4) {
                     if (exposure_time >= 3 && exposure_time <= 100) {
                         opt.hdr_exposuretime_content[num - 1] = exposure_time;
                         return true;
                     }
                 }
                 return false;
             },
             call_guard<gil_scoped_release>())
        .def("GetHDRGainContent",
             [](X1::CaptureOptions &opt, int num) {
                 int exp = -1;
                 if (num > 0 && num < 4) {
                     exp = opt.hdr_gain_3d[num - 1];
                 }
                 return exp;
             },
             call_guard<gil_scoped_release>())
        .def("SetHDRGainContent",
             [](X1::CaptureOptions &opt, int num, int gain_3d) {
                 if (num > 0 && num < 4) {
                     if (gain_3d >= 0 && gain_3d <= 20) {
                         opt.hdr_gain_3d[num - 1] = gain_3d;
                         return true;
                     }
                 }
                 return false;
             },
             call_guard<gil_scoped_release>())
        .def("GetHDRScanTimesContent",
             [](X1::CaptureOptions &opt, int num) {
                 int exp = -1;
                 if (num > 0 && num < 4) {
                     exp = opt.hdr_scan_times[num - 1];
                 }
                 return exp;
             },
             call_guard<gil_scoped_release>())
        .def("SetHDRScanTimesContent",
             [](X1::CaptureOptions &opt, int num, int scan_times) {
                 if (num > 0 && num < 4) {
                     if (scan_times >= 2 && scan_times <= 4) {
                         opt.hdr_scan_times[num - 1] = scan_times;
                         return true;
                     }
                 }
                 return false;
             },
             call_guard<gil_scoped_release>())
        .def("GetHDRProjectorBrightnessContent",
             [](X1::CaptureOptions &opt, int num) {
                 int exp = -1;
                 if (num > 0 && num < 4) {
                     exp = opt.hdr_projector_brightness[num - 1];
                 }
                 return exp;
             },
             call_guard<gil_scoped_release>())
        .def("SetHDRProjectorBrightnessContent",
             [](X1::CaptureOptions &opt, int num, int projector_brightness) {
                 if (num > 0 && num < 4) {
                     if (projector_brightness >= 1 && projector_brightness <= 240) {
                         opt.hdr_projector_brightness[num - 1] = projector_brightness;
                         return true;
                     }
                 }
                 return false;
             },
             call_guard<gil_scoped_release>())
        .def_readwrite("capture_mode", &X1::CaptureOptions::capture_mode)
        .def_readwrite("confidence_threshold", &X1::CaptureOptions::confidence_threshold)
        .def_readwrite("roi", &X1::CaptureOptions::roi);

    class_<X1::CustomTransformOptions>(m, "X1_CustomTransformOptions")
        .def(init<>(), call_guard<gil_scoped_release>())
        .def_readwrite("coordinate_select", &X1::CustomTransformOptions::coordinate_select)
        .def("SetTransform",
             [](X1::CustomTransformOptions &self, array_t<double> &transform) {
                 buffer_info buf = transform.request();
                 double *ptr = (double *)buf.ptr;
                 for (size_t i = 0; i < 16; i++) {
                     self.transform[i] = *(ptr + i);
                 }
             },
             call_guard<gil_scoped_release>());

#ifndef NOT_EXPORT_TO_USER
    class_<Projector>(m, "Projector")
        .def(init<>(), call_guard<gil_scoped_release>())
        .def_static("Create", [](const Device &d) { return Projector::Create(d); }, arg("device"),
                    call_guard<gil_scoped_release>())
        .def_static("Destroy", &Projector::Destroy, call_guard<gil_scoped_release>())
        .def("IsValid", &Projector::IsValid, call_guard<gil_scoped_release>())
        .def("Open", &Projector::Open, call_guard<gil_scoped_release>())
        .def("Close", &Projector::Close, call_guard<gil_scoped_release>())
        .def("IsOpen", &Projector::IsOpen, call_guard<gil_scoped_release>())
        .def("GetStatus",
             [](Projector &p) {
                 int status = 0;
                 int ret = p.GetStatus(&status);
                 return std::make_pair(ret, status);
             },
             call_guard<gil_scoped_release>())
        .def("SetProjectorColor", &Projector::SetProjectorColor, call_guard<gil_scoped_release>())
        .def("GetProjectorColor",
             [](Projector &self) {
                 ProjectorColor val = ProjectorColor_None;
                 int ret = self.GetProjectorColor(&val);
                 return std::make_pair(ret, val);
             },
             call_guard<gil_scoped_release>())
        .def("SetBrightness", &Projector::SetBrightness, call_guard<gil_scoped_release>())
        .def("GetBrightness",
             [](Projector &self) {
                 uint8_t val = 0;
                 int ret = self.GetBrightness(&val);
                 return std::make_pair(ret, val);
             },
             call_guard<gil_scoped_release>())
        .def("SetIlluminationTime", &Projector::SetIlluminationTime, call_guard<gil_scoped_release>())
        .def("GetIlluminationTime",
             [](Projector &self) {
                 uint32_t us = 0;
                 int ret = self.GetIlluminationTime(&us);
                 return std::make_pair(ret, us);
             },
             call_guard<gil_scoped_release>())
        .def("GetProjectorTemperature",
             [](Projector &self) {
                 float val = 0;
                 int ret = self.GetProjectorTemperature(&val);
                 return std::make_pair(ret, val);
             },
             call_guard<gil_scoped_release>())
        .def("Project",
             [](Projector &self, const uint16_t rounds, std::vector<uint16_t> imgs) {
                 return self.Project(rounds, imgs.data(), imgs.size());
             },
             call_guard<gil_scoped_release>())

        .def("StopProject", &Projector::StopProject, call_guard<gil_scoped_release>())
        .def("ProjectAndTrigger",
             [](Projector &self, const uint16_t rounds, std::vector<uint16_t> cams, std::vector<uint16_t> imgs) {
                 return self.ProjectAndTrigger(rounds, cams.data(), cams.size(), imgs.data(), imgs.size());
             },
             call_guard<gil_scoped_release>());
#endif

    enum_<SmoothnessLevel>(m, "SmoothnessLevel")
        .value("SmoothnessLevel_Off", SmoothnessLevel_Off)
        .value("SmoothnessLevel_Weak", SmoothnessLevel_Weak)
        .value("SmoothnessLevel_Normal", SmoothnessLevel_Normal)
        .value("SmoothnessLevel_Strong", SmoothnessLevel_Strong)
        .export_values();

    enum_<CaptureMode>(m, "CaptureMode")
        .value("CaptureMode_Fast", CaptureMode_Fast)
        .value("CaptureMode_Normal", CaptureMode_Normal)
        .value("CaptureMode_Ultra", CaptureMode_Ultra)
        .value("CaptureMode_Robust", CaptureMode_Robust)
        .export_values();

    class_<X1>(m, "X1")
        .def(init<>(), call_guard<gil_scoped_release>())
        .def_static("Create", [](const Device &d, enum CameraID camid) { return X1::Create(d, camid); },
                    arg("device"), arg("camid") = RVC::CameraID_Left, call_guard<gil_scoped_release>())
        .def_static("Destroy", &X1::Destroy, call_guard<gil_scoped_release>())
        .def("Open", &X1::Open, call_guard<gil_scoped_release>())
        .def("IsOpen", &X1::IsOpen, call_guard<gil_scoped_release>())
        .def("Close", &X1::Close, call_guard<gil_scoped_release>())
        .def("IsValid", &X1::IsValid, call_guard<gil_scoped_release>())
        .def("IsPhysicallyConnected", &X1::IsPhysicallyConnected, call_guard<gil_scoped_release>())
        .def("Capture",
             [](X1 &self, X1::CaptureOptions opts) {
                 bool ret = false;
                 ret = self.Capture(opts);
                 return ret;
             }, call_guard<gil_scoped_release>())
        .def("Capture",
            [](X1& self) {
                bool ret = false;
                ret = self.Capture();
                return ret;
            }, call_guard<gil_scoped_release>())
        .def("Capture2D",
             [](X1 &self, const X1::CaptureOptions &opts) {
                 bool ret = false;
                 ret = self.Capture2D(opts);
                 return ret;
             },
             arg("opts") = X1::CaptureOptions(), call_guard<gil_scoped_release>())
        .def("Capture2D",
             [](X1 &self) {
                 bool ret = false;
                 ret = self.Capture2D();
                 return ret;
             },
             call_guard<gil_scoped_release>())
        .def("SetBandwidth", &X1::SetBandwidth, call_guard<gil_scoped_release>())
        .def("SetCustomTransformation",
             [](X1 &self, X1::CustomTransformOptions opts) {
                 bool ret = self.SetCustomTransformation(opts);
                 return ret;
             },
             call_guard<gil_scoped_release>())
        .def("GetCustomTransformation",
             [](X1 &self) {
                 X1::CustomTransformOptions opts;
                 bool ret = self.GetCustomTransformation(opts);
                 return std::make_tuple(ret, opts);
             },
             call_guard<gil_scoped_release>())
        .def("GetImage", &X1::GetImage, call_guard<gil_scoped_release>())
        .def("GetExposureTimeRange",
             [](X1 &self) {
                 int min_v, max_v;
                 bool ret = self.GetExposureTimeRange(&min_v, &max_v);
                 return std::make_tuple(ret, min_v, max_v);
             },
             call_guard<gil_scoped_release>())
        .def("GetGainRange",
             [](X1 &self) {
                 float min_v, max_v;
                 bool ret = self.GetGainRange(&min_v, &max_v);
                 return std::make_tuple(ret, min_v, max_v);
             },
             call_guard<gil_scoped_release>())
        .def("GetGammaRange",
             [](X1 &self) {
                 float min_v, max_v;
                 bool ret = self.GetGammaRange(&min_v, &max_v);
                 return std::make_tuple(ret, min_v, max_v);
             },
             call_guard<gil_scoped_release>())
        .def("GetCameraTemperature",
             [](X1 &self, CameraTempSelector sel) {
                 float temperature;
                 bool ret = self.GetCameraTemperature(sel, temperature);
                 return std::make_pair(ret, temperature);
             },
             call_guard<gil_scoped_release>())
        .def("GetDepthMap", &X1::GetDepthMap, call_guard<gil_scoped_release>())
        .def("GetPointMap", &X1::GetPointMap, call_guard<gil_scoped_release>())
        .def("GetConfidenceMap", &X1::GetConfidenceMap, call_guard<gil_scoped_release>())
#ifndef NOT_EXPORT_TO_USER
        .def("GenerateEncodedMap", &X1::GenerateEncodedMap, call_guard<gil_scoped_release>())
        .def("SaveEncodedImagesData", &X1::SaveEncodedImagesData, call_guard<gil_scoped_release>())
        .def("GetEncodeMap", &X1::GetEncodeMap, call_guard<gil_scoped_release>())
        .def("GetEncodedRawImage", &X1::GetEncodedRawImage, call_guard<gil_scoped_release>())
        .def("GetRawImage", static_cast<Image (X1::*)(uint16_t, const bool)>(&X1::GetRawImage),
             call_guard<gil_scoped_release>())
        .def("GetRawImage", static_cast<bool (X1::*)(Image &, uint16_t)>(&X1::GetRawImage),
             call_guard<gil_scoped_release>())
        .def("GetProjector", &X1::GetProjector, call_guard<gil_scoped_release>())
        .def("GetCamera", &X1::GetCamera, call_guard<gil_scoped_release>())
#endif
        .def("SetBalanceRatio", &X1::SetBalanceRatio, call_guard<gil_scoped_release>())
        .def("GetBalanceRatio",
             [](X1 &self, BalanceSelector selector) {
                 float value;
                 bool ret = self.GetBalanceRatio(selector, &value);
                 return std::make_tuple(ret, value);
             },
             call_guard<gil_scoped_release>())
        .def("GetBalanceRange",
             [](X1 &self, BalanceSelector selector) {
                 float min_v, max_v;
                 bool ret = self.GetBalanceRange(selector, &min_v, &max_v);
                 return std::make_tuple(ret, min_v, max_v);
             },
             call_guard<gil_scoped_release>())
        .def("AutoWhiteBalance", &X1::AutoWhiteBalance, call_guard<gil_scoped_release>())
        .def("GetExtrinsicMatrix",
             [](X1 &self) {
                 std::vector<float> matrix = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
                 bool ret = self.GetExtrinsicMatrix(&matrix[0]);
                 return std::make_pair(ret, matrix);
             },
             call_guard<gil_scoped_release>())
        .def("GetIntrinsicParameters",
             [](X1 &self) {
                 std::vector<float> intrinsic_matrix = {0, 0, 0, 0, 0, 0, 0, 0, 0};
                 std::vector<float> distortion = {0, 0, 0, 0, 0};
                 bool ret = self.GetIntrinsicParameters(&intrinsic_matrix[0], &distortion[0]);
                 return std::make_tuple(ret, intrinsic_matrix, distortion);
             },
             call_guard<gil_scoped_release>())
        .def("SaveCaptureOptionParameters", &X1::SaveCaptureOptionParameters, call_guard<gil_scoped_release>())
        .def("LoadCaptureOptionParameters",
             [](X1 &self) {
                 X1::CaptureOptions opts;
                 bool ret = self.LoadCaptureOptionParameters(opts);
                 return std::make_pair(ret, opts);
             },
             call_guard<gil_scoped_release>())
        .def("GetAutoCaptureSetting",
             [](X1 &self, X1::CaptureOptions opts, ROI roi) {
                 bool ret = false;
                 ret = self.GetAutoCaptureSetting(opts, roi);
                 return std::make_pair(ret, opts);
             },
             arg("opts") = X1::CaptureOptions(), arg("roi") = ROI(), call_guard<gil_scoped_release>())
        .def("GetAutoHdrCaptureSetting",
             [](X1 &self, X1::CaptureOptions opts, ROI roi) {
                 bool ret = false;
                 ret = self.GetAutoHdrCaptureSetting(opts, roi);
                 return std::make_pair(ret, opts);
             },
             arg("opts") = X1::CaptureOptions(), arg("roi") = ROI(), call_guard<gil_scoped_release>())
        .def("GetAutoNoiseRemovalSetting",
             [](X1 &self, X1::CaptureOptions opts) {
                 bool ret = false;
                 ret = self.GetAutoNoiseRemovalSetting(opts);
                 return std::make_pair(ret, opts);
             },
             call_guard<gil_scoped_release>())
        .def("LoadSettingFromFile", &X1::LoadSettingFromFile, call_guard<gil_scoped_release>())
        .def("SaveSettingToFile", &X1::SaveSettingToFile, call_guard<gil_scoped_release>())
        .def("CheckRoi", &X1::CheckRoi, call_guard<gil_scoped_release>())
        .def("AutoAdjustRoi", &X1::AutoAdjustRoi, call_guard<gil_scoped_release>())
        .def("GetRoiRange",
             [](X1 &self) {
                 bool ret = false;
                 ROIRange range;
                 ret = self.GetRoiRange(range);
                 return std::make_pair(ret, range);
             },
             call_guard<gil_scoped_release>());

#ifndef NOT_EXPORT_TO_USER
    class_<Camera>(m, "Camera")
        .def(init<>(), call_guard<gil_scoped_release>())
        .def_static("Create", [](const Device &d, enum CameraID camid) { return Camera::Create(d, camid); },
                    arg("device"), arg("camid") = RVC::CameraID_Left, call_guard<gil_scoped_release>())
        .def_static("Destroy", &Camera::Destroy, call_guard<gil_scoped_release>())
        .def("Open", &Camera::Open, call_guard<gil_scoped_release>())
        .def("Close", &Camera::Close, call_guard<gil_scoped_release>())
        .def("IsValid", &Camera::IsValid, call_guard<gil_scoped_release>())
        .def("StartGrabbing", &Camera::StartGrabbing, call_guard<gil_scoped_release>())
        .def("StopGrabbing", &Camera::StopGrabbing, call_guard<gil_scoped_release>())
        .def("GetGrabbingImg", &Camera::GetGrabbingImg, call_guard<gil_scoped_release>())
        .def("GetGrabbingImgBufferCount", &Camera::GetGrabbingImgBufferCount, call_guard<gil_scoped_release>())
        .def("GetFailedGrabbingCount", &Camera::GetFailedGrabbingCount, call_guard<gil_scoped_release>())
        .def("SetBandwidth", &Camera::SetBandwidth, call_guard<gil_scoped_release>())
        .def("IsOpen", &Camera::IsOpen, call_guard<gil_scoped_release>())
        .def("Capture", &Camera::Capture, call_guard<gil_scoped_release>())
        .def("GetCaptureImg", &Camera::GetCaptureImg, call_guard<gil_scoped_release>())
        .def("IsColorCamera", &Camera::IsColorCamera, call_guard<gil_scoped_release>())
        .def("GetWidth", &Camera::GetWidth, call_guard<gil_scoped_release>())
        .def("GetHeight", &Camera::GetHeight, call_guard<gil_scoped_release>())
        .def("GetGain", &Camera::GetGain, call_guard<gil_scoped_release>())
        .def("SetGain", &Camera::SetGain, call_guard<gil_scoped_release>())
        .def("GetGamma", &Camera::GetGamma, call_guard<gil_scoped_release>())
        .def("SetGamma", &Camera::SetGamma, call_guard<gil_scoped_release>())
        .def("GetGainRange",
             [](Camera &self) {
                 float min_value, max_value;
                 int ret = self.GetGainRange(&min_value, &max_value);
                 return std::make_tuple(ret, min_value, max_value);
             },
             call_guard<gil_scoped_release>())
        .def("GetGammaRange",
             [](Camera &self) {
                 float min_value, max_value;
                 int ret = self.GetGammaRange(&min_value, &max_value);
                 return std::make_tuple(ret, min_value, max_value);
             },
             call_guard<gil_scoped_release>())
        .def("SetExposureTime", &Camera::SetExposureTime, call_guard<gil_scoped_release>())
        .def("GetExposureTime", &Camera::GetExposureTime, call_guard<gil_scoped_release>());
#endif

    class_<X2::CaptureOptions>(m, "X2_CaptureOptions")
        .def(init<>(), call_guard<gil_scoped_release>())
        .def_readwrite("transform_to_camera", &X2::CaptureOptions::transform_to_camera)
        .def_readwrite("projector_brightness", &X2::CaptureOptions::projector_brightness)
        .def_readwrite("calc_normal", &X2::CaptureOptions::calc_normal)
        .def_readwrite("calc_normal_radius", &X2::CaptureOptions::calc_normal_radius)
        .def_readwrite("light_contrast_threshold", &X2::CaptureOptions::light_contrast_threshold)
        .def_readwrite("edge_noise_reduction_threshold", &X2::CaptureOptions::edge_noise_reduction_threshold)
        .def_readwrite("noise_removal_distance", &X2::CaptureOptions::noise_removal_distance)
        .def_readwrite("noise_removal_point_number", &X2::CaptureOptions::noise_removal_point_number)
        .def_readwrite("exposure_time_2d", &X2::CaptureOptions::exposure_time_2d)
        .def_readwrite("exposure_time_3d", &X2::CaptureOptions::exposure_time_3d)
        .def_readwrite("gain_2d", &X2::CaptureOptions::gain_2d)
        .def_readwrite("gain_3d", &X2::CaptureOptions::gain_3d)
        .def_readwrite("hdr_exposure_times", &X2::CaptureOptions::hdr_exposure_times)
        .def_readwrite("use_projector_capturing_2d_image", &X2::CaptureOptions::use_projector_capturing_2d_image)
        .def_readwrite("smoothness", &X2::CaptureOptions::smoothness)
        .def_readwrite("downsample_distance", &X2::CaptureOptions::downsample_distance)
        .def("GetHDRExposureTimeContent",
             [](X2::CaptureOptions &opt, int num) {
                 int exp = -1;
                 if (num > 0 && num < 4) {
                     exp = opt.hdr_exposuretime_content[num - 1];
                 }
                 return exp;
             },
             call_guard<gil_scoped_release>())
        .def("SetHDRExposureTimeContent",
             [](X2::CaptureOptions &opt, int num, int exposure_time) {
                 if (num > 0 && num < 4) {
                     if (exposure_time >= 3 && exposure_time <= 100) {
                         opt.hdr_exposuretime_content[num - 1] = exposure_time;
                         return true;
                     }
                 }
                 return false;
             },
             call_guard<gil_scoped_release>())

        .def(
            "GetHDRGainContent",
            [](X2::CaptureOptions& opt, int num) {
                int exp = -1;
                if (num > 0 && num < 4) {
                    exp = opt.hdr_gain_3d[num - 1];
                }
                return exp;
            },
            call_guard<gil_scoped_release>())
        .def(
            "SetHDRGainContent",
            [](X2::CaptureOptions& opt, int num, float gain_3d) {
                if (num > 0 && num < 4) {
                    if (gain_3d >= 0 && gain_3d <= 20) {
                        opt.hdr_gain_3d[num - 1] = gain_3d;
                        return true;
                    }
                }
                return false;
            },
            call_guard<gil_scoped_release>())
        .def(
            "GetHDRProjectorBrightnessContent",
            [](X2::CaptureOptions& opt, int num) {
                int exp = -1;
                if (num > 0 && num < 4) {
                    exp = opt.hdr_projector_brightness[num - 1];
                }
                return exp;
            },
            call_guard<gil_scoped_release>())
        .def(
            "SetHDRProjectorBrightnessContent",
            [](X2::CaptureOptions& opt, int num, int projector_brightness) {
                if (num > 0 && num < 4) {
                    if (projector_brightness >= 1 && projector_brightness <= 240) {
                        opt.hdr_projector_brightness[num - 1] = projector_brightness;
                        return true;
                    }
                }
                return false;
            },
            call_guard<gil_scoped_release>())
        .def_readwrite("gamma_2d", &X2::CaptureOptions::gamma_2d)
        .def_readwrite("gamma_3d", &X2::CaptureOptions::gamma_3d)
        // .def_readwrite("confidence_filter_threshold", &X2::CaptureOptions::confidence_filter_threshold)
        .def_readwrite("projector_color", &X2::CaptureOptions::projector_color)
        .def_readwrite("capture_mode", &X2::CaptureOptions::capture_mode)
        .def_readwrite("confidence_threshold", &X2::CaptureOptions::confidence_threshold);
    class_<X2::CustomTransformOptions>(m, "X2_CustomTransformOptions")
        .def(init<>(), call_guard<gil_scoped_release>())
        .def_readwrite("coordinate_select", &X2::CustomTransformOptions::coordinate_select)
        .def("SetTransform",
             [](X2::CustomTransformOptions &self, array_t<double> &transform) {
                 buffer_info buf = transform.request();
                 double *ptr = (double *)buf.ptr;
                 for (size_t i = 0; i < 16; i++) {
                     self.transform[i] = *(ptr + i);
                 }
             },
             call_guard<gil_scoped_release>());

    class_<X2>(m, "X2")
        .def(init<>(), call_guard<gil_scoped_release>())
        .def_static("Create", [](const Device &d) { return X2::Create(d); }, arg("device"),
                    call_guard<gil_scoped_release>())
        .def_static("Destroy", &X2::Destroy, call_guard<gil_scoped_release>())
        .def("Open", &X2::Open, call_guard<gil_scoped_release>())
        .def("IsOpen", &X2::IsOpen, call_guard<gil_scoped_release>())
        .def("Close", &X2::Close, call_guard<gil_scoped_release>())
        .def("IsValid", &X2::IsValid, call_guard<gil_scoped_release>())
        .def("IsPhysicallyConnected", &X2::IsPhysicallyConnected, call_guard<gil_scoped_release>())
        .def("Capture",
             [](X2 &self, X2::CaptureOptions opts) {
                 bool ret = false;
                 ret = self.Capture(opts);
                 return ret;
             }, call_guard<gil_scoped_release>())
        .def("Capture",
            [](X2& self) {
                bool ret = false;
                ret = self.Capture();
                return ret;
            }, call_guard<gil_scoped_release>())
        .def("Capture2D",
             [](X2 &self, const CameraID cid, const X2::CaptureOptions &opts) {
                 bool ret = false;
                 ret = self.Capture2D(cid, opts);
                 return ret;
             },
             arg("cid"), arg("opts") = X2::CaptureOptions(), call_guard<gil_scoped_release>())
        .def("Capture2D",
             [](X2 &self, const CameraID cid) {
                 bool ret = false;
                 ret = self.Capture2D(cid);
                 return ret;
             },
             arg("cid"),  call_guard<gil_scoped_release>())
        .def("SetBandwidth", &X2::SetBandwidth, call_guard<gil_scoped_release>())
        .def("SetCustomTransformation",
             [](X2 &self, X2::CustomTransformOptions opts) {
                 bool ret = self.SetCustomTransformation(opts);
                 return ret;
             },
             call_guard<gil_scoped_release>())
        .def("GetCustomTransformation",
             [](X2 &self) {
                 X2::CustomTransformOptions opts;
                 bool ret = self.GetCustomTransformation(opts);
                 return std::make_tuple(ret, opts);
             },
             call_guard<gil_scoped_release>())
        .def("GetImage", &X2::GetImage, call_guard<gil_scoped_release>())
        .def("GetPointMap", &X2::GetPointMap, call_guard<gil_scoped_release>())
        .def("GetConfidenceMap", &X2::GetConfidenceMap, call_guard<gil_scoped_release>())
#ifndef NOT_EXPORT_TO_USER
        .def("GenerateEncodedMap", &X2::GenerateEncodedMap, call_guard<gil_scoped_release>())
        .def("SaveEncodedImagesData", &X2::SaveEncodedImagesData, call_guard<gil_scoped_release>())
        .def("GetEncodeMap", &X2::GetEncodeMap, call_guard<gil_scoped_release>())
        .def("GetEncodedRawImage", &X2::GetEncodedRawImage, call_guard<gil_scoped_release>())
        .def("GetRawImage", static_cast<Image (X2::*)(const CameraID, const int)>(&X2::GetRawImage),
             call_guard<gil_scoped_release>())
        .def("GetRawImage", static_cast<bool (X2::*)(Image &, const CameraID, const int)>(&X2::GetRawImage),
             call_guard<gil_scoped_release>())
        .def("GetProjector", &X2::GetProjector, call_guard<gil_scoped_release>())
        .def("GetCamera", &X2::GetCamera, call_guard<gil_scoped_release>())
#endif
        .def("GetDepthMap", &X2::GetDepthMap, call_guard<gil_scoped_release>())
        .def("AutoWhiteBalance", &X2::AutoWhiteBalance, call_guard<gil_scoped_release>())
        .def("GetExtrinsicMatrix",
             [](X2 &self, CameraID cid) {
                 std::vector<float> matrix(16);
                 bool ret = self.GetExtrinsicMatrix(cid, matrix.data());
                 return std::make_pair(ret, matrix);
             },
             call_guard<gil_scoped_release>())
        .def("GetIntrinsicParameters",
             [](X2 &self, CameraID cid) {
                 std::vector<float> intrinsic_matrix(9);
                 std::vector<float> distortion(5);
                 bool ret = self.GetIntrinsicParameters(cid, intrinsic_matrix.data(), distortion.data());
                 return std::make_tuple(ret, intrinsic_matrix, distortion);
             },
             call_guard<gil_scoped_release>())
        .def("GetExposureTimeRange",
             [](X2 &self) {
                 int min_v, max_v;
                 bool ret = self.GetExposureTimeRange(&min_v, &max_v);
                 return std::make_tuple(ret, min_v, max_v);
             },
             call_guard<gil_scoped_release>())
        .def("GetGainRange",
             [](X2 &self) {
                 float min_v, max_v;
                 bool ret = self.GetGainRange(&min_v, &max_v);
                 return std::make_tuple(ret, min_v, max_v);
             },
             call_guard<gil_scoped_release>())
        .def("GetGammaRange",
             [](X2 &self) {
                 float min_v, max_v;
                 bool ret = self.GetGammaRange(&min_v, &max_v);
                 return std::make_tuple(ret, min_v, max_v);
             },
             call_guard<gil_scoped_release>())
        .def("GetCameraTemperature",
             [](X2 &self, CameraID cid, CameraTempSelector sel) {
                 float temperature;
                 bool ret;
                 ret = self.GetCameraTemperature(cid, sel, temperature);
                 return std::make_pair(ret, temperature);
             },
             call_guard<gil_scoped_release>())
        .def("SaveCaptureOptionParameters", &X2::SaveCaptureOptionParameters, call_guard<gil_scoped_release>())
        .def("LoadCaptureOptionParameters",
             [](X2 &self) {
                 X2::CaptureOptions opts;
                 bool ret = self.LoadCaptureOptionParameters(opts);
                 return std::make_pair(ret, opts);
             },
             call_guard<gil_scoped_release>())
        .def("GetAutoCaptureSetting",
             [](X2 &self, X2::CaptureOptions opts, ROI roi) {
                 bool ret = false;
                 ret = self.GetAutoCaptureSetting(opts, roi);
                 return std::make_pair(ret, opts);
             },
             arg("opts") = X2::CaptureOptions(), arg("roi") = ROI(), call_guard<gil_scoped_release>())
        .def("GetAutoHdrCaptureSetting",
             [](X2 &self, X2::CaptureOptions opts, ROI roi) {
                 bool ret = false;
                 ret = self.GetAutoHdrCaptureSetting(opts, roi);
                 return std::make_pair(ret, opts);
             },
             arg("opts") = X2::CaptureOptions(), arg("roi") = ROI(), call_guard<gil_scoped_release>())
        .def("GetAutoNoiseRemovalSetting",
             [](X2 &self, X2::CaptureOptions opts) {
                 bool ret = false;
                 ret = self.GetAutoNoiseRemovalSetting(opts);
                 return std::make_pair(ret, opts);
             },
             call_guard<gil_scoped_release>())
        .def("LoadSettingFromFile", &X2::LoadSettingFromFile, call_guard<gil_scoped_release>())
        .def("SaveSettingToFile", &X2::SaveSettingToFile, call_guard<gil_scoped_release>());
}
