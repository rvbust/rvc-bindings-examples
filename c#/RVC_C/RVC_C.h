// Copyright (c) RVBUST, Inc - All rights reserved.
#pragma once

#include <RVC/RVC.h>

#define RVC_EXTERN_DLL extern "C" __declspec(dllexport)

extern "C"
{

struct CSize {
    int width;
    int height;
};

struct CHandle
{
    int sid;
    int gid;
};

struct CROI
{
    int x;
    int y;
    int width;
    int height;
};

}

RVC_EXTERN_DLL char* __stdcall ImageType_ToString(RVC::ImageType::Enum type);
RVC_EXTERN_DLL int __stdcall ImageType_GetPixelSize(RVC::ImageType::Enum type);
RVC_EXTERN_DLL char* __stdcall PointMapType_ToString(RVC::PointMapType::Enum type);
RVC_EXTERN_DLL bool __stdcall  System_Init();
RVC_EXTERN_DLL bool __stdcall  System_IsInit();
RVC_EXTERN_DLL void __stdcall  System_ShutDown();
RVC_EXTERN_DLL void __stdcall  System_ListDevices(int* pdevices, int len,int& actual_size, RVC::SystemListDeviceType::Enum opt = RVC::SystemListDeviceType::Enum::All);
RVC_EXTERN_DLL bool __stdcall  System_FindDevice(char* serialNumber, CHandle & deviceHandle);
RVC_EXTERN_DLL int __stdcall  System_GetLastError();
RVC_EXTERN_DLL char* __stdcall  System_GetVersion();
RVC_EXTERN_DLL void __stdcall  Device_Destroy(CHandle devicehandle);
RVC_EXTERN_DLL bool __stdcall  Device_IsValid(CHandle devicehandle);
RVC_EXTERN_DLL void __stdcall  Device_Print(CHandle devicehandle);
RVC_EXTERN_DLL bool __stdcall  Device_GetDeviceInfo(CHandle devicehandle, RVC::DeviceInfo& pinfo);
RVC_EXTERN_DLL int __stdcall  Device_SetNetworkConfig(CHandle devicehandle, RVC::NetworkDevice d, RVC::NetworkType type, char* ip, char* netMask, char* gateway);
RVC_EXTERN_DLL int __stdcall  Device_GetNetworkConfig(CHandle devicehandle, RVC::NetworkDevice d, RVC::NetworkType& type, char* ip, char* netMask, char* gateway, RVC::NetworkDeviceStatus_& status);
RVC_EXTERN_DLL CHandle __stdcall  X1_Create(CHandle deviceHandle, RVC::CameraID id);
RVC_EXTERN_DLL void __stdcall  X1_Destroy(CHandle x1Handle);
RVC_EXTERN_DLL bool __stdcall  X1_IsValid(CHandle x1Handle);
RVC_EXTERN_DLL bool __stdcall  X1_Open(CHandle x1Handle);
RVC_EXTERN_DLL void __stdcall  X1_Close(CHandle x1Handle);
RVC_EXTERN_DLL bool __stdcall  X1_IsOpen(CHandle x1Handle);
RVC_EXTERN_DLL bool __stdcall  X1_IsPhysicallyConnected(CHandle x1Handle);
RVC_EXTERN_DLL bool  __stdcall X1_Capture(CHandle x1Handle, RVC::X1::CaptureOptions opts);
RVC_EXTERN_DLL bool  __stdcall X1_Capture_(CHandle x1Handle);
RVC_EXTERN_DLL bool __stdcall  X1_Capture2D(CHandle x1Handle, RVC::X1::CaptureOptions opts);
RVC_EXTERN_DLL bool __stdcall  X1_Capture2D_(CHandle x1Handle);
RVC_EXTERN_DLL bool __stdcall  X1_SetBandwidth(CHandle x1Handle, float percent);
RVC_EXTERN_DLL bool __stdcall  X1_GetBandwidth(CHandle x1Handle,  float& percent);
RVC_EXTERN_DLL bool __stdcall  X1_SetCustomTransformation(CHandle x1Handle, RVC::X1::CustomTransformOptions opts);
RVC_EXTERN_DLL bool __stdcall  X1_GetCustomTransformation(CHandle x1Handle, RVC::X1::CustomTransformOptions& opts);
RVC_EXTERN_DLL CHandle __stdcall  X1_GetImage(CHandle x1Handle);
RVC_EXTERN_DLL CHandle  __stdcall X1_GetDepthMap(CHandle x1Handle);
RVC_EXTERN_DLL CHandle __stdcall  X1_GetPointMap(CHandle x1Handle);
RVC_EXTERN_DLL CHandle  __stdcall X1_GetConfidenceMap(CHandle x1Handle);
RVC_EXTERN_DLL bool __stdcall  X1_GetExtrinsicMatrix(CHandle x1Handle, float* matrix);
RVC_EXTERN_DLL bool __stdcall  X1_GetIntrinsicParameters(CHandle x1Handle, float* instrinsic_matrix, float* distortion);
RVC_EXTERN_DLL bool  __stdcall X1_GetCameraTemperature(CHandle x1Handle, RVC::CameraTempSelector seletor,  float& temperature);
RVC_EXTERN_DLL bool  __stdcall X1_SetBalanceRatio(CHandle x1Handle, RVC::BalanceSelector selector, float value);
RVC_EXTERN_DLL bool  __stdcall X1_GetBalanceRatio(CHandle x1Handle, RVC::BalanceSelector selector, float& value);
RVC_EXTERN_DLL bool  __stdcall X1_GetBalanceRange(CHandle x1Handle, RVC::BalanceSelector selector, float& min_value, float& max_value);
RVC_EXTERN_DLL bool  __stdcall X1_AutoWhiteBalance(CHandle x1Handle, int wb_times, RVC::X1::CaptureOptions opts, CROI roi);
RVC_EXTERN_DLL bool __stdcall  X1_GetExposureTimeRange(CHandle x1Handle, int& min_value, int& max_value);
RVC_EXTERN_DLL bool __stdcall  X1_GetGainRange(CHandle x1Handle, float& min_value, float& max_value);
RVC_EXTERN_DLL bool __stdcall  X1_GetGammaRange(CHandle x1Handle, float& min_value, float& max_value);
RVC_EXTERN_DLL bool __stdcall X1_SaveCaptureOptionParameters(CHandle x1Handle, RVC::X1::CaptureOptions opts);
RVC_EXTERN_DLL bool __stdcall  X1_LoadCaptureOptionParameters(CHandle x1Handle, RVC::X1::CaptureOptions& opts);
RVC_EXTERN_DLL bool __stdcall  X1_GetAutoCaptureSetting(CHandle x1Handle, RVC::X1::CaptureOptions& opts, CROI roi);
RVC_EXTERN_DLL bool __stdcall  X1_GetAutoHdrCaptureSetting(CHandle x1Handle, RVC::X1::CaptureOptions& opts, CROI roi);
RVC_EXTERN_DLL bool __stdcall  X1_GetAutoNoiseRemovalSetting(CHandle x1Handle, RVC::X1::CaptureOptions& opts);
RVC_EXTERN_DLL bool __stdcall  X1_LoadSettingFromFile(CHandle x1Handle, char* filename);
RVC_EXTERN_DLL bool __stdcall  X1_SaveSettingToFile(CHandle x1Handle, char* filename);
RVC_EXTERN_DLL bool __stdcall   X1_CheckRoi(CHandle x1Handle, CROI roi);
RVC_EXTERN_DLL CROI __stdcall  X1_AutoAdjustRoi(CHandle x1Handle, CROI roi);
RVC_EXTERN_DLL bool __stdcall X1_GetRoiRange(CHandle x1Handle, RVC::ROIRange& range);
RVC_EXTERN_DLL CHandle __stdcall  X2_Create(CHandle deviceHandle);
RVC_EXTERN_DLL void __stdcall  X2_Destroy(CHandle x2Handle);
RVC_EXTERN_DLL bool __stdcall  X2_IsValid(CHandle x2Handle);
RVC_EXTERN_DLL bool  __stdcall X2_Open(CHandle x2Handle);
RVC_EXTERN_DLL void __stdcall  X2_Close(CHandle x2Handle);
RVC_EXTERN_DLL bool __stdcall  X2_IsOpen(CHandle x2Handle);
RVC_EXTERN_DLL bool __stdcall  X2_IsPhysicallyConnected(CHandle x2Handle);
RVC_EXTERN_DLL bool __stdcall  X2_Capture(CHandle x2Handle, RVC::X2::CaptureOptions opts);
RVC_EXTERN_DLL bool __stdcall  X2_Capture_(CHandle x2Handle);
RVC_EXTERN_DLL bool __stdcall  X2_Capture2D(CHandle x2Handle, RVC::CameraID cid, RVC::X2::CaptureOptions opts);
RVC_EXTERN_DLL bool __stdcall  X2_Capture2D_(CHandle x2Handle, RVC::CameraID cid);
RVC_EXTERN_DLL bool __stdcall  X2_SetBandwidth(CHandle x2Handle, float percent);
RVC_EXTERN_DLL bool __stdcall  X2_GetBandwidth(CHandle x2Handle, float& percent);
RVC_EXTERN_DLL bool __stdcall  X2_SetCustomTransformation(CHandle x2Handle, RVC::X2::CustomTransformOptions opts);
RVC_EXTERN_DLL bool __stdcall  X2_GetCustomTransformation(CHandle x2Handle, RVC::X2::CustomTransformOptions& opts);
RVC_EXTERN_DLL CHandle __stdcall  X2_GetPointMap(CHandle x2Handle);
RVC_EXTERN_DLL CHandle __stdcall  X2_GetImage(CHandle x2Handle, RVC::CameraID cid);
RVC_EXTERN_DLL CHandle __stdcall  X2_GetDepthMap(CHandle x2Handle);
RVC_EXTERN_DLL CHandle __stdcall  X2_GetConfidenceMap(CHandle x2Handle);
RVC_EXTERN_DLL bool __stdcall  X2_GetExtrinsicMatrix(CHandle x2Handle, RVC::CameraID cid, float* matrix);
RVC_EXTERN_DLL bool __stdcall  X2_GetIntrinsicParameters(CHandle x2Handle, RVC::CameraID cid, float* instrinsicMatrix, float* distortion);
RVC_EXTERN_DLL bool __stdcall  X2_GetCameraTemperature(CHandle x2Handle, RVC::CameraID cid, RVC::CameraTempSelector seletor, float& temperature);
RVC_EXTERN_DLL bool __stdcall  X2_AutoWhiteBalance(CHandle x2Handle, int wb_times, RVC::X2::CaptureOptions opts, CROI roi);
RVC_EXTERN_DLL bool __stdcall  X2_GetExposureTimeRange(CHandle x2Handle, int& min_value, int& max_value);
RVC_EXTERN_DLL bool __stdcall  X2_GetGainRange(CHandle x2Handle, float& min_value, float& max_value);
RVC_EXTERN_DLL bool __stdcall  X2_GetGammaRange(CHandle x2Handle, float& min_value, float& max_value);
RVC_EXTERN_DLL bool __stdcall  X2_SaveCaptureOptionParameters(CHandle x2Handle, RVC::X2::CaptureOptions opts);
RVC_EXTERN_DLL bool __stdcall  X2_LoadCaptureOptionParameters(CHandle x2Handle, RVC::X2::CaptureOptions& opts);
RVC_EXTERN_DLL bool __stdcall  X2_GetAutoCaptureSetting(CHandle x2Handle, RVC::X2::CaptureOptions& opts, CROI roi);
RVC_EXTERN_DLL bool  __stdcall X2_GetAutoHdrCaptureSetting(CHandle x2Handle, RVC::X2::CaptureOptions& opts, CROI roi);
RVC_EXTERN_DLL bool __stdcall  X2_GetAutoNoiseRemovalSetting(CHandle x2Handle, RVC::X2::CaptureOptions& opts);
RVC_EXTERN_DLL bool __stdcall  X2_LoadSettingFromFile(CHandle x2Handle, char* filename);
RVC_EXTERN_DLL bool __stdcall  X2_SaveSettingToFile(CHandle x2Handle, char* filename);
RVC_EXTERN_DLL CHandle __stdcall  Image_Create(RVC::ImageType::Enum it, CSize sz, unsigned char* data, bool own_data = true);
RVC_EXTERN_DLL void __stdcall  Image_Destroy(CHandle imageHandle, bool no_reuse = true);
RVC_EXTERN_DLL bool __stdcall  Image_IsValid(CHandle imageHandle);
RVC_EXTERN_DLL CSize __stdcall  Image_GetSize(CHandle imageHandle);
RVC_EXTERN_DLL RVC::ImageType::Enum __stdcall  Image_GetType(CHandle imageHandle);
RVC_EXTERN_DLL unsigned char* __stdcall  Image_GetDataPtr(CHandle imageHandle);
RVC_EXTERN_DLL bool __stdcall  Image_SaveImage(CHandle imageHandle, char* addr);
RVC_EXTERN_DLL CHandle __stdcall  DepthMap_Create(CSize sz, double* data, bool own_data = true);
RVC_EXTERN_DLL void __stdcall  DepthMap_Destroy(CHandle depthHandle, bool no_reuse = true);
RVC_EXTERN_DLL bool __stdcall  DepthMap_IsValid(CHandle depthHandle);
RVC_EXTERN_DLL CSize __stdcall  DepthMap_GetSize(CHandle depthHandle);
RVC_EXTERN_DLL double* __stdcall  DepthMap_GetDataPtr(CHandle depthHandle);
RVC_EXTERN_DLL bool __stdcall  DepthMap_SaveDepthMap(CHandle depthHandle, char* address, bool is_m = true);
RVC_EXTERN_DLL CHandle __stdcall  PointMap_Create(RVC::PointMapType::Enum type, CSize size, double* data, bool owndata = true);
RVC_EXTERN_DLL void  __stdcall PointMap_Destroy(CHandle pointMapHandle, bool no_reuse = true);
RVC_EXTERN_DLL bool  __stdcall PointMap_IsValid(CHandle pointMapHandle);
RVC_EXTERN_DLL CSize  __stdcall PointMap_GetSize(CHandle pointMapHandle);
RVC_EXTERN_DLL  double* __stdcall PointMap_GetPointDataPtr(CHandle pointMapHandle);
RVC_EXTERN_DLL  double* __stdcall  PointMap_GetNormalDataPtr(CHandle pointMapHandle);
RVC_EXTERN_DLL bool __stdcall  PointMap_GetPointMapSeperated(CHandle pointMapHandle, double* x, double* y, double* z, double scale = 1.0);
RVC_EXTERN_DLL bool __stdcall  PointMap_Save(CHandle pointMapHandle, char* filename, RVC::PointMapUnit::Enum unit, bool isBinary, CHandle imageHandle );
RVC_EXTERN_DLL CHandle __stdcall  ConfidenceMap_Create(CSize sz, double* data, bool own_data = true);
RVC_EXTERN_DLL void  __stdcall ConfidenceMap_Destroy(CHandle confidenceHandle, bool no_reuse = true);
RVC_EXTERN_DLL bool __stdcall  ConfidenceMap_IsValid(CHandle confidenceHandle);
RVC_EXTERN_DLL CSize  __stdcall ConfidenceMap_GetSize(CHandle confidenceHandle);
RVC_EXTERN_DLL  double* __stdcall  ConfidenceMap_GetDataPtr(CHandle confidenceHandle);

