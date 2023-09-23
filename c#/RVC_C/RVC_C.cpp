#include "RVC_C.h"

using namespace RVC;

Image GetImage(CHandle handle) { Image ret; ret.m_handle = Handle(handle.sid,handle.gid); return ret; }

DepthMap GetDepthMap(CHandle handle) { DepthMap ret; ret.m_handle = Handle(handle.sid,handle.gid); return ret; }

PointMap GetPointMap(CHandle handle) { PointMap ret; ret.m_handle = Handle(handle.sid,handle.gid); return ret; }

ConfidenceMap GetConfidenceMap(CHandle handle) { ConfidenceMap ret; ret.m_handle = Handle(handle.sid,handle.gid); return ret; }

Device GetDevice(CHandle handle) { Device ret; ret.m_handle = Handle(handle.sid,handle.gid); return ret; }

X1 GetX1(CHandle handle) { X1 ret; ret.m_handle = Handle(handle.sid,handle.gid); return ret; }

X2 GetX2(CHandle handle) { X2 ret; ret.m_handle = Handle(handle.sid,handle.gid); return ret; }

Size GetSize(CSize size) { return Size(size.width, size.height); }

CSize GetCSize(Size size) { CSize ret; ret.width = size.width; ret.height = size.height; return ret; }

CHandle GetCHandle(Handle handle) { CHandle ret; ret.sid = handle.sid; ret.gid = handle.gid; return ret; }

RVC::ROI GetRoi(CROI roi)
{
	RVC::ROI ret;
	ret.x = roi.x;
	ret.y = roi.y;
	ret.width = roi.width;
	ret.height = roi.height;
	return  ret;
}

CROI GetCROI(RVC::ROI roi)
{
	CROI ret;
	ret.x = roi.x;
	ret.y = roi.y;
	ret.width = roi.width;
	ret.height = roi.height;
	return  ret;
}

RVC_EXTERN_DLL char* __stdcall ImageType_ToString(RVC::ImageType::Enum type)
{
	return (char*)ImageType::ToString(type);
}

RVC_EXTERN_DLL int __stdcall ImageType_GetPixelSize(RVC::ImageType::Enum type)
{
	return ImageType::GetPixelSize(type);
}

RVC_EXTERN_DLL char* __stdcall PointMapType_ToString(RVC::PointMapType::Enum type)
{
	return (char*)PointMapType::ToString(type);
}

RVC_EXTERN_DLL bool __stdcall System_Init()
{
	return SystemInit();
}

RVC_EXTERN_DLL bool __stdcall System_IsInit()
{
	return SystemIsInited();
}

RVC_EXTERN_DLL void __stdcall System_ShutDown()
{
	return SystemShutdown();
}

RVC_EXTERN_DLL void __stdcall System_ListDevices(int* pdevices, int len, int& actual_size, RVC::SystemListDeviceType::Enum opt )
{
	if (len >= 100)
		len = 100;
	Device deviceList[100];
	size_t size = 0;
	SystemListDevices(deviceList, len, &size, opt);
	actual_size = size;
	for (int i = 0 ; i < actual_size && i< len ; i++)
	{
		pdevices[i * 2] = deviceList[i].m_handle.sid;
		pdevices[i * 2 + 1] = deviceList[i].m_handle.gid;
	}
}

RVC_EXTERN_DLL bool __stdcall System_FindDevice(char* serialNumber, CHandle& deviceHandle)
{
	Device device = SystemFindDevice(serialNumber);
	deviceHandle = GetCHandle( device.m_handle);
	bool ret = device.IsValid();
	return device.IsValid();
}

RVC_EXTERN_DLL int __stdcall System_GetLastError()
{
	return GetLastError();
}

RVC_EXTERN_DLL char* __stdcall System_GetVersion()
{
	return (char*)GetVersion();
}

RVC_EXTERN_DLL void __stdcall Device_Destroy(CHandle devicehandle)
{
	return Device::Destroy(GetDevice(devicehandle));
}

RVC_EXTERN_DLL bool __stdcall Device_IsValid(CHandle devicehandle)
{
	return GetDevice(devicehandle).IsValid();
}

RVC_EXTERN_DLL void __stdcall Device_Print(CHandle devicehandle)
{
	return GetDevice(devicehandle).Print();
}

RVC_EXTERN_DLL bool __stdcall Device_GetDeviceInfo(CHandle devicehandle, RVC::DeviceInfo& pinfo)
{
	RVC::DeviceInfo tmp_info;
	bool valid = GetDevice(devicehandle).IsValid();
	auto ret = GetDevice(devicehandle).GetDeviceInfo(&tmp_info);
	pinfo = tmp_info;
	return ret;
}

RVC_EXTERN_DLL int __stdcall  Device_SetNetworkConfig(CHandle devicehandle, RVC::NetworkDevice d, RVC::NetworkType type, char* ip, char* netMask,
    char* gateway)
{
	return GetDevice(devicehandle).SetNetworkConfig(d,type,ip,netMask,gateway);
}

RVC_EXTERN_DLL int __stdcall  Device_GetNetworkConfig(CHandle devicehandle, RVC::NetworkDevice d, RVC::NetworkType& type, char* ip, char* netMask, char* gateway, NetworkDeviceStatus_& status)
{
	int tmp_status = 0;
	int ret = GetDevice(devicehandle).GetNetworkConfig(d, &type, ip, netMask, gateway, &tmp_status);
	status = (NetworkDeviceStatus_)tmp_status;
	return ret;
}

RVC_EXTERN_DLL CHandle __stdcall  X1_Create(CHandle deviceHandle, RVC::CameraID id)
{
	return  GetCHandle(X1::Create(GetDevice(deviceHandle), id).m_handle);
}

RVC_EXTERN_DLL void __stdcall  X1_Destroy(CHandle x1Handle)
{
	return X1::Destroy(GetX1(x1Handle));
}

RVC_EXTERN_DLL bool __stdcall  X1_IsValid(CHandle x1Handle)
{
	bool ret = GetX1(x1Handle).IsValid();
	return ret;
}

RVC_EXTERN_DLL bool __stdcall  X1_Open(CHandle x1Handle)
{
	bool ret = GetX1(x1Handle).Open();
	return ret;
}

RVC_EXTERN_DLL void __stdcall  X1_Close(CHandle x1Handle)
{
	return GetX1(x1Handle).Close();
}

RVC_EXTERN_DLL bool __stdcall  X1_IsOpen(CHandle x1Handle)
{
	return GetX1(x1Handle).IsOpen();
}

RVC_EXTERN_DLL bool __stdcall  X1_IsPhysicallyConnected(CHandle x1Handle)
{
	return GetX1(x1Handle).IsPhysicallyConnected();
}

RVC_EXTERN_DLL bool  __stdcall X1_Capture(CHandle x1Handle, RVC::X1::CaptureOptions opts)
{
	bool ret = GetX1(x1Handle).Capture(opts);
	return ret;
}

RVC_EXTERN_DLL bool  __stdcall X1_Capture_(CHandle x1Handle)
{
	bool ret = GetX1(x1Handle).Capture();
	return ret;
}

RVC_EXTERN_DLL bool __stdcall  X1_Capture2D(CHandle x1Handle, RVC::X1::CaptureOptions opts)
{
	bool ret = GetX1(x1Handle).Capture2D(opts);
	return ret;
}


RVC_EXTERN_DLL bool  __stdcall X1_Capture2D_(CHandle x1Handle)
{
	bool ret = GetX1(x1Handle).Capture2D();
	return ret;
}

RVC_EXTERN_DLL bool __stdcall  X1_SetBandwidth(CHandle x1Handle, float percent)
{
	return GetX1(x1Handle).SetBandwidth(percent);
}

RVC_EXTERN_DLL bool __stdcall  X1_GetBandwidth(CHandle x1Handle, float& percent)
{
	return GetX1(x1Handle).GetBandwidth(percent);
}

RVC_EXTERN_DLL bool __stdcall  X1_SetCustomTransformation(CHandle x1Handle, RVC::X1::CustomTransformOptions opts)
{
	return GetX1(x1Handle).SetCustomTransformation(opts);
}

RVC_EXTERN_DLL bool __stdcall  X1_GetCustomTransformation(CHandle x1Handle, RVC::X1::CustomTransformOptions& opts)
{
	return GetX1(x1Handle).GetCustomTransformation(opts);
}

RVC_EXTERN_DLL CHandle __stdcall  X1_GetImage(CHandle x1Handle)
{
	return  GetCHandle(GetX1(x1Handle).GetImage().m_handle);
}

RVC_EXTERN_DLL CHandle  __stdcall X1_GetDepthMap(CHandle x1Handle)
{
	return  GetCHandle(GetX1(x1Handle).GetDepthMap().m_handle);
}

RVC_EXTERN_DLL CHandle __stdcall  X1_GetPointMap(CHandle x1Handle)
{
	return  GetCHandle(GetX1(x1Handle).GetPointMap().m_handle);
}

RVC_EXTERN_DLL CHandle  __stdcall X1_GetConfidenceMap(CHandle x1Handle)
{
	return  GetCHandle(GetX1(x1Handle).GetConfidenceMap().m_handle);
}

RVC_EXTERN_DLL bool __stdcall  X1_GetExtrinsicMatrix(CHandle x1Handle, float* matrix)
{
	return GetX1(x1Handle).GetExtrinsicMatrix(matrix);
}

RVC_EXTERN_DLL bool __stdcall  X1_GetIntrinsicParameters(CHandle x1Handle, float* instrinsic_matrix, float* distortion)
{
	return GetX1(x1Handle).GetIntrinsicParameters(instrinsic_matrix, distortion);
}

RVC_EXTERN_DLL bool  __stdcall X1_GetCameraTemperature(CHandle x1Handle, RVC::CameraTempSelector seletor, float& temperature)
{
	return GetX1(x1Handle).GetCameraTemperature(seletor, temperature);
}

RVC_EXTERN_DLL bool  __stdcall X1_SetBalanceRatio(CHandle x1Handle, RVC::BalanceSelector selector, float value)
{
	return GetX1(x1Handle).SetBalanceRatio(selector, value);
}

RVC_EXTERN_DLL bool  __stdcall X1_GetBalanceRatio(CHandle x1Handle, RVC::BalanceSelector selector, float& value)
{
	return GetX1(x1Handle).GetBalanceRatio(selector,&value);
}

RVC_EXTERN_DLL bool  __stdcall X1_GetBalanceRange(CHandle x1Handle, RVC::BalanceSelector selector, float& min_value, float& max_value)
{
	return GetX1(x1Handle).GetBalanceRange(selector, &min_value,&max_value);
}

RVC_EXTERN_DLL bool  __stdcall X1_AutoWhiteBalance(CHandle x1Handle, int wb_times, RVC::X1::CaptureOptions opts, CROI roi)
{
	return GetX1(x1Handle).AutoWhiteBalance(wb_times, opts, GetRoi(roi));
}

RVC_EXTERN_DLL bool __stdcall  X1_GetExposureTimeRange(CHandle x1Handle, int& min_value, int& max_value)
{
	int tmp_min, tmp_max;
	auto ret = GetX1(x1Handle).GetExposureTimeRange(&tmp_min, &tmp_max);
	min_value = tmp_min;
	max_value = tmp_max;
	return ret;
}

RVC_EXTERN_DLL bool __stdcall  X1_GetGainRange(CHandle x1Handle, float& min_value, float& max_value)
{
	float tmp_min, tmp_max;
	auto ret = GetX1(x1Handle).GetGainRange(&tmp_min, &tmp_max);
	min_value = tmp_min;
	max_value = tmp_max;
	return ret;
}

RVC_EXTERN_DLL bool __stdcall  X1_GetGammaRange(CHandle x1Handle, float& min_value, float& max_value)
{
	float tmp_min, tmp_max;
	auto ret = GetX1(x1Handle).GetGammaRange(&tmp_min, &tmp_max);
	min_value = tmp_min;
	max_value = tmp_max;
	return ret;
}

RVC_EXTERN_DLL bool __stdcall X1_SaveCaptureOptionParameters(CHandle x1Handle, RVC::X1::CaptureOptions opts)
{
	return GetX1(x1Handle).SaveCaptureOptionParameters(opts);
}

RVC_EXTERN_DLL bool __stdcall  X1_LoadCaptureOptionParameters(CHandle x1Handle, RVC::X1::CaptureOptions& opts)
{
	bool ret = GetX1(x1Handle).LoadCaptureOptionParameters(opts);
	return ret;
}

RVC_EXTERN_DLL bool __stdcall  X1_GetAutoCaptureSetting(CHandle x1Handle, RVC::X1::CaptureOptions& opts, CROI roi)
{
	bool ret = GetX1(x1Handle).GetAutoCaptureSetting(opts, GetRoi(roi));
	return ret;
}

RVC_EXTERN_DLL bool __stdcall  X1_GetAutoHdrCaptureSetting(CHandle x1Handle, RVC::X1::CaptureOptions& opts, CROI roi)
{
	bool ret = GetX1(x1Handle).GetAutoHdrCaptureSetting(opts, GetRoi(roi));
	return ret;
}

RVC_EXTERN_DLL bool __stdcall  X1_GetAutoNoiseRemovalSetting(CHandle x1Handle, RVC::X1::CaptureOptions& opts)
{
	bool ret = GetX1(x1Handle).GetAutoNoiseRemovalSetting(opts);
	return ret;
}

RVC_EXTERN_DLL bool __stdcall  X1_LoadSettingFromFile(CHandle x1Handle, char* filename)
{
	return GetX1(x1Handle).LoadSettingFromFile(filename);
}

RVC_EXTERN_DLL bool __stdcall  X1_SaveSettingToFile(CHandle x1Handle, char* filename)
{
	return GetX1(x1Handle).SaveSettingToFile(filename);
}

RVC_EXTERN_DLL bool __stdcall  X1_CheckRoi(CHandle x1Handle, CROI roi)
{
	return GetX1(x1Handle).CheckRoi(GetRoi(roi));
}

RVC_EXTERN_DLL CROI __stdcall X1_AutoAdjustRoi(CHandle x1Handle, CROI roi)
{
	return GetCROI(GetX1(x1Handle).AutoAdjustRoi(GetRoi(roi)));
}

RVC_EXTERN_DLL bool __stdcall X1_GetRoiRange(CHandle x1Handle, RVC::ROIRange& range)
{
	return GetX1(x1Handle).GetRoiRange(range);
}

RVC_EXTERN_DLL CHandle __stdcall  X2_Create(CHandle deviceHandle)
{
	return  GetCHandle(X2::Create(GetDevice(deviceHandle)).m_handle);
}

RVC_EXTERN_DLL void __stdcall  X2_Destroy(CHandle x2Handle)
{
	return X2::Destroy(GetX2(x2Handle));
}

RVC_EXTERN_DLL bool __stdcall  X2_IsValid(CHandle x2Handle)
{
	return GetX2(x2Handle).IsValid();
}

RVC_EXTERN_DLL bool __stdcall  X2_Open(CHandle x2Handle)
{
	return GetX2(x2Handle).Open();
}

RVC_EXTERN_DLL void __stdcall  X2_Close(CHandle x2Handle)
{
	return GetX2(x2Handle).Close();
}

RVC_EXTERN_DLL bool __stdcall  X2_IsOpen(CHandle x2Handle)
{
	return GetX2(x2Handle).IsOpen();
}

RVC_EXTERN_DLL bool __stdcall  X2_IsPhysicallyConnected(CHandle x2Handle)
{
	return GetX2(x2Handle).IsPhysicallyConnected();
}

RVC_EXTERN_DLL bool  __stdcall X2_Capture(CHandle x2Handle, RVC::X2::CaptureOptions opts)
{
	bool ret = GetX2(x2Handle).Capture(opts);
	return ret;
}

RVC_EXTERN_DLL bool __stdcall  X2_Capture_(CHandle x2Handle)
{
	bool ret = GetX2(x2Handle).Capture();
	return ret;
}

RVC_EXTERN_DLL bool __stdcall  X2_Capture2D(CHandle x2Handle, RVC::CameraID cid, RVC::X2::CaptureOptions opts)
{
	bool ret = GetX2(x2Handle).Capture2D(cid, opts);
	return ret;
}

RVC_EXTERN_DLL bool __stdcall  X2_Capture2D_(CHandle x2Handle, RVC::CameraID cid)
{
	bool ret = GetX2(x2Handle).Capture2D(cid);
	return ret;
}

RVC_EXTERN_DLL bool __stdcall  X2_SetBandwidth(CHandle x2Handle, float percent)
{
	return GetX2(x2Handle).SetBandwidth(percent);
}

RVC_EXTERN_DLL bool __stdcall  X2_GetBandwidth(CHandle x2Handle, float& percent)
{
	return GetX2(x2Handle).GetBandwidth(percent);
}

RVC_EXTERN_DLL bool __stdcall  X2_SetCustomTransformation(CHandle x2Handle, RVC::X2::CustomTransformOptions opts)
{
	return GetX2(x2Handle).SetCustomTransformation(opts);
}

RVC_EXTERN_DLL bool __stdcall  X2_GetCustomTransformation(CHandle x2Handle, RVC::X2::CustomTransformOptions& opts)
{
	return GetX2(x2Handle).GetCustomTransformation(opts);
}

RVC_EXTERN_DLL CHandle __stdcall  X2_GetImage(CHandle x2Handle, RVC::CameraID cid)
{
	return  GetCHandle(GetX2(x2Handle).GetImage(cid).m_handle);
}

RVC_EXTERN_DLL CHandle  __stdcall X2_GetDepthMap(CHandle x2Handle)
{
	return  GetCHandle(GetX2(x2Handle).GetDepthMap().m_handle);
}

RVC_EXTERN_DLL CHandle __stdcall  X2_GetPointMap(CHandle x2Handle)
{
	return  GetCHandle(GetX2(x2Handle).GetPointMap().m_handle);
}

RVC_EXTERN_DLL CHandle  __stdcall X2_GetConfidenceMap(CHandle x2Handle)
{
	return  GetCHandle(GetX2(x2Handle).GetConfidenceMap().m_handle);
}

RVC_EXTERN_DLL bool __stdcall  X2_GetExtrinsicMatrix(CHandle x2Handle, RVC::CameraID cid, float* matrix)
{
	return GetX2(x2Handle).GetExtrinsicMatrix(cid,matrix);
}

RVC_EXTERN_DLL bool __stdcall  X2_GetIntrinsicParameters(CHandle x2Handle, RVC::CameraID cid, float* instrinsic_matrix, float* distortion)
{
	return GetX2(x2Handle).GetIntrinsicParameters(cid, instrinsic_matrix, distortion);
}

RVC_EXTERN_DLL bool  __stdcall X2_GetCameraTemperature(CHandle x2Handle, RVC::CameraID cid, RVC::CameraTempSelector seletor, float& temperature)
{
	return GetX2(x2Handle).GetCameraTemperature(cid, seletor, temperature);
}

RVC_EXTERN_DLL bool  __stdcall X2_AutoWhiteBalance(CHandle x2Handle, int wb_times, RVC::X2::CaptureOptions opts, CROI roi)
{
	return GetX2(x2Handle).AutoWhiteBalance(wb_times, opts, GetRoi(roi));
}

RVC_EXTERN_DLL bool __stdcall  X2_GetExposureTimeRange(CHandle x2Handle, int& min_value, int& max_value)
{
	int tmp_min, tmp_max;
	auto ret = GetX2(x2Handle).GetExposureTimeRange(&tmp_min, &tmp_max);
	min_value = tmp_min;
	max_value = tmp_max;
	return ret;
}

RVC_EXTERN_DLL bool __stdcall  X2_GetGainRange(CHandle x2Handle, float& min_value, float& max_value)
{
	float tmp_min, tmp_max;
	auto ret = GetX2(x2Handle).GetGainRange(&tmp_min, &tmp_max);
	min_value = tmp_min;
	max_value = tmp_max;
	return ret;
}

RVC_EXTERN_DLL bool __stdcall  X2_GetGammaRange(CHandle x2Handle, float& min_value, float& max_value)
{
	float tmp_min, tmp_max;
	auto ret = GetX2(x2Handle).GetGammaRange(&tmp_min, &tmp_max);
	min_value = tmp_min;
	max_value = tmp_max;
	return ret;
}

RVC_EXTERN_DLL bool __stdcall X2_SaveCaptureOptionParameters(CHandle x2Handle, RVC::X2::CaptureOptions opts)
{
	return GetX2(x2Handle).SaveCaptureOptionParameters(opts);
}

RVC_EXTERN_DLL bool __stdcall  X2_LoadCaptureOptionParameters(CHandle x2Handle, RVC::X2::CaptureOptions& opts)
{
	return GetX2(x2Handle).LoadCaptureOptionParameters(opts);
}

RVC_EXTERN_DLL bool __stdcall  X2_GetAutoCaptureSetting(CHandle x2Handle, RVC::X2::CaptureOptions& opts, CROI roi)
{
	return GetX2(x2Handle).GetAutoCaptureSetting(opts, GetRoi(roi));
}

RVC_EXTERN_DLL bool __stdcall  X2_GetAutoHdrCaptureSetting(CHandle x2Handle, RVC::X2::CaptureOptions& opts, CROI roi)
{
	return GetX2(x2Handle).GetAutoHdrCaptureSetting(opts, GetRoi(roi));
}

RVC_EXTERN_DLL bool __stdcall  X2_GetAutoNoiseRemovalSetting(CHandle x2Handle, RVC::X2::CaptureOptions& opts)
{
	return GetX2(x2Handle).GetAutoNoiseRemovalSetting(opts);
}

RVC_EXTERN_DLL bool __stdcall  X2_LoadSettingFromFile(CHandle x2Handle, char* filename)
{
	return GetX2(x2Handle).LoadSettingFromFile(filename);
}

RVC_EXTERN_DLL bool __stdcall  X2_SaveSettingToFile(CHandle x2Handle, char* filename)
{
	return GetX2(x2Handle).SaveSettingToFile(filename);
}


RVC_EXTERN_DLL CHandle __stdcall  Image_Create(RVC::ImageType::Enum it, CSize sz, unsigned char* data, bool own_data )
{
	return  GetCHandle(Image::Create(it, GetSize(sz), data, own_data).m_handle);
}

RVC_EXTERN_DLL void __stdcall  Image_Destroy(CHandle imageHandle, bool no_reuse )
{
	return Image::Destroy(GetImage(imageHandle),no_reuse);
}

RVC_EXTERN_DLL bool __stdcall  Image_IsValid(CHandle imageHandle)
{
	return GetImage(imageHandle).IsValid();
}

RVC_EXTERN_DLL CSize __stdcall  Image_GetSize(CHandle imageHandle)
{
	return GetCSize(GetImage(imageHandle).GetSize()) ;
}

RVC_EXTERN_DLL RVC::ImageType::Enum __stdcall  Image_GetType(CHandle imageHandle)
{
	return GetImage(imageHandle).GetType();
}

RVC_EXTERN_DLL unsigned char* __stdcall  Image_GetDataPtr(CHandle imageHandle)
{
	return GetImage(imageHandle).GetDataPtr();
}

RVC_EXTERN_DLL bool __stdcall  Image_SaveImage(CHandle imageHandle, char* addr)
{
	return GetImage(imageHandle).SaveImage(addr);
}

RVC_EXTERN_DLL CHandle __stdcall  DepthMap_Create(CSize sz, double* data, bool own_data)
{
	return  GetCHandle(DepthMap::Create(GetSize(sz), data, own_data).m_handle);
}

RVC_EXTERN_DLL void __stdcall  DepthMap_Destroy(CHandle depthHandle, bool no_reuse )
{
	return DepthMap::Destroy(GetDepthMap(depthHandle),no_reuse);
}

RVC_EXTERN_DLL bool __stdcall  DepthMap_IsValid(CHandle depthHandle)
{
	return GetDepthMap(depthHandle).IsValid();
}

RVC_EXTERN_DLL CSize __stdcall  DepthMap_GetSize(CHandle depthHandle)
{
	return GetCSize(GetDepthMap(depthHandle).GetSize());
}

RVC_EXTERN_DLL double* __stdcall  DepthMap_GetDataPtr(CHandle depthHandle)
{
	return GetDepthMap(depthHandle).GetDataPtr();
}


RVC_EXTERN_DLL bool __stdcall  DepthMap_SaveDepthMap(CHandle depthHandle, char* address, bool is_m )
{
	return GetDepthMap(depthHandle).SaveDepthMap(address, is_m);
}

RVC_EXTERN_DLL CHandle __stdcall  PointMap_Create(RVC::PointMapType::Enum type, CSize size, double* data, bool owndata )
{
	return  GetCHandle(PointMap::Create(type, GetSize(size), data, owndata).m_handle);
}

RVC_EXTERN_DLL void  __stdcall PointMap_Destroy(CHandle pointMapHandle, bool no_reuse )
{
	return PointMap::Destroy(GetPointMap(pointMapHandle), no_reuse);
}

RVC_EXTERN_DLL bool  __stdcall PointMap_IsValid(CHandle pointMapHandle)
{
	return GetPointMap(pointMapHandle).IsValid();
}

RVC_EXTERN_DLL CSize  __stdcall PointMap_GetSize(CHandle pointMapHandle)
{
	return GetCSize(GetPointMap(pointMapHandle).GetSize());
}

RVC_EXTERN_DLL  double* __stdcall PointMap_GetPointDataPtr(CHandle pointMapHandle)
{
	return GetPointMap(pointMapHandle).GetPointDataPtr();
}

RVC_EXTERN_DLL  double* __stdcall  PointMap_GetNormalDataPtr(CHandle pointMapHandle)
{
	return GetPointMap(pointMapHandle).GetNormalDataPtr();
}

RVC_EXTERN_DLL bool __stdcall  PointMap_GetPointMapSeperated(CHandle pointMapHandle, double* x, double* y, double* z, double scale )
{
	return GetPointMap(pointMapHandle).GetPointMapSeperated(x,y,z,scale);
}

RVC_EXTERN_DLL bool __stdcall  PointMap_Save(CHandle pointMapHandle, char* filename, RVC::PointMapUnit::Enum unit, bool isBinary, CHandle imageHandle)
{
	return GetPointMap(pointMapHandle).Save(filename,unit,isBinary,GetImage(imageHandle));
}

RVC_EXTERN_DLL CHandle __stdcall  ConfidenceMap_Create(CSize sz, double* data, bool own_data )
{
	return  GetCHandle(ConfidenceMap::Create(GetSize(sz), data, own_data).m_handle);
}

RVC_EXTERN_DLL void  __stdcall ConfidenceMap_Destroy(CHandle confidenceHandle, bool no_reuse )
{
	return ConfidenceMap::Destroy(GetConfidenceMap(confidenceHandle),no_reuse);
}

RVC_EXTERN_DLL bool __stdcall  ConfidenceMap_IsValid(CHandle confidenceHandle)
{
	return GetConfidenceMap(confidenceHandle).IsValid();
}

RVC_EXTERN_DLL CSize  __stdcall ConfidenceMap_GetSize(CHandle confidenceHandle)
{
	return GetCSize(GetConfidenceMap(confidenceHandle).GetSize());
}

RVC_EXTERN_DLL  double* __stdcall  ConfidenceMap_GetDataPtr(CHandle confidenceHandle)
{
	return GetConfidenceMap(confidenceHandle).GetDataPtr();
}

