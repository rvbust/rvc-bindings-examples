using System;
using System.Runtime.InteropServices;
using System.Text;
using System.Collections.Generic;

namespace RVC_CSharp
{
    #region Basic Enum

    /**
     * @brief NetworkDevieStatus, support *NetworkDeviceStatus_OK*, *NetworkDeviceStatus_Not_Reachable*,
     * *NetworkDeviceStatus_In_Use* and *NetworkDeviceStatus_Conflict*
     *
     */
    public enum NetworkDeviceStatus_
    {
        NetworkDeviceStatus_OK,
        NetworkDeviceStatus_Not_Reachable,
        NetworkDeviceStatus_In_Use,
        NetworkDeviceStatus_Conflict,
    };

    /// <summary>
    /// System list Device type
    /// All support type are *USB*, *GigE*, *ALL*
    /// </summary>
    public enum SystemListDeviceType
    {
        None = 0,
        USB = 1 << 0,
        GigE = 1 << 1,
        All = USB | GigE,
    };

    /// <summary>
    /// NetworkDevice
    /// support *NetworkDevice_LightMachine*, *NetworkDevice_LeftCamera* and *NetworkDevice_RightCamera*
    /// </summary>
    public enum NetworkDevice
    {
        NetworkDevice_LightMachine = 0,
        NetworkDevice_LeftCamera = 1,
        NetworkDevice_RightCamera = 2,
    };

    /// <summary>
    /// RVC supported Camera Network type
    /// Only valid when Camera PortType is *PortType_GIGE*
    /// All support type is *NetworkType_DHCP*, *NetworkType_STATIC*
    /// </summary>
    public enum NetworkType
    {
        NetworkType_DHCP = 0,
        NetworkType_STATIC = 1,
    };

    /// <summary>
    /// CaptureMode
    /// support *CaptureMode_Fast*, *CaptureMode_Normal*,*CaptureMode_Ultra*,*CaptureMode_Robust*,
    /// </summary>
    public enum CaptureMode
    {
        CaptureMode_Fast = 1 << 0,
        CaptureMode_Normal = 1 << 1,
        CaptureMode_Ultra = 1 << 2,
        CaptureMode_Robust = 1 << 3,
        CaptureMode_All = CaptureMode_Fast | CaptureMode_Normal | CaptureMode_Ultra | CaptureMode_Robust,
    };

    /// <summary>
    /// Projector color
    /// support *ProjectorColor_Red*, *ProjectorColor_Green*, *ProjectorColor_Blue*,*ProjectorColor_White* and *ProjectorColor_ALL*
    /// </summary>
    public enum ProjectorColor
    {
        ProjectorColor_None = 0,
        ProjectorColor_Red = 1,
        ProjectorColor_Green = 2,
        ProjectorColor_Blue = 4,
        ProjectorColor_White = 8,
        ProjectorColor_ALL = ProjectorColor_Red | ProjectorColor_Green | ProjectorColor_Blue | ProjectorColor_White,
    };

    /// <summary>
    /// CameraID
    /// support *CameraID_Left* , *CameraID_Right*, *CameraID_Both*
    /// </summary>
    public enum CameraID
    {
        CameraID_NONE = 0,
        CameraID_0 = 1 << 0,
        CameraID_1 = 1 << 1,
        CameraID_2 = 1 << 2,
        CameraID_3 = 1 << 3,
        CameraID_Left = CameraID_0,
        CameraID_Right = CameraID_1,
        CameraID_Both = CameraID_Left | CameraID_Right,
    };

    /// <summary>
    /// RVC supported Camera Port type
    /// All support type is *PortType_USB*, *PortType_GIGE*
    /// </summary>
    public enum PortType
    {
        PortType_NONE = 0,
        PortType_USB = 1,
        PortType_GIGE = 2,
    };

    /// <summary>
    /// 
    /// </summary>
    public enum SmoothnessLevel
    {
        SmoothnessLevel_Off,
        SmoothnessLevel_Weak,
        SmoothnessLevel_Normal,
        SmoothnessLevel_Strong
    };

    /// <summary>
    /// 
    /// </summary>
    public enum CameraTempSelector
    {
        CameraTempSelector_Camera,
        CameraTempSelector_CoreBoard,
        CameraTempSelector_FpgaCore,
        CameraTempSelector_Framegrabberboard,
        CameraTempSelector_Sensor,
        CameraTempSelector_SensorBoard,
    };

    /**
     * @brief White balance ratio selector, suport *BalanceSelector_Red*, *BalanceSelector_Green* and *BalanceSelector_Blue*
     *
     */
    public enum BalanceSelector
    {
        BalanceSelector_None = 0,
        BalanceSelector_Red,
        BalanceSelector_Green,
        BalanceSelector_Blue,
    };
    
    /**
     * @brief Image Type
     *
     *  All support type are *Mono8*, *RGB8*, *BGR8*
     */
    public enum ImageType
    {
        None = 0,
        Mono8 = 1,
        RGB8 = 2,
        BGR8 = 3,
    };


    /**
     * @brief RVC X PointMap Type
     * @brief PointMap Type Support type *PointsOnly* and *PointsNormals*
     * @param PointsOnly which only contains points
     * @param PointsNormals which contains points with normals
     */
    public enum PointMapType
    {
        None = 0,
        PointsOnly = 1,
        PointsNormals = 2,
    };

    /**
     * @brief RVC X PointMap Unit
     * @brief PointMap Type Support type *Meter* and *Millimeter*
     */
    public enum PointMapUnit
    {
        Meter = 0,
        Millimeter = 1,
    }

    #endregion

    #region Common Function

    public static class Common
    {
        /**
         * @brief Print given ImageType
         *
         * @param type ImageType
         * @return const char* Name of ImageType
         */
        public static string ToString(ImageType type) => RVC_CSharp_DLL.ImageType_ToString(type);

        /**
         * @brief Get pixel size of ImageType
         *
         * @param type ImageType
         * @return size_t Pixel size
         */
        public static int GetPixelSize(ImageType type) => RVC_CSharp_DLL.ImageType_GetPixelSize(type);

        /**
        * @brief print PointMap Type`s name
        *
        * @param e Pointmap Type
        * @return const char* Pointmap Type`s name
        */
        public static string ToString(PointMapType type) => RVC_CSharp_DLL.PointMapType_ToString(type);

    }

    #endregion

    #region Basic Struct

    /**
     * @brief RVC Handle
     *
     */
    [StructLayoutAttribute(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct Handle
    {
        /**
         * @brief Construct a new Handle object with sid and gid
         *
         * @param sid_
         * @param gid_
         */
        //public Handle(int sid_, int gid_)
        //{
        //    this.sid = sid_;
        //    this.gid = gid_;
        //}
        public int sid;
        public int gid;
    };

    /**
     * @brief Image/PointMap Size
     * In case of [union],the Size in CSharp is different from the Size in cpp.
     */
    [StructLayoutAttribute(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct Size
    {
        /**
         * @brief Construct a new Image/PointMap Size object with width/cols and height/rows
         *
         * @param w Image width/PointMap cols
         * @param h Image height/PointMap rows
         */
        public Size(int w, int h)
        {
            width = w;
            height = h;
        }

        /**
         * @brief width or cols
         *
         */
        public int width;
        /**
         * @brief height or rows
         *
         */
        public int height;
    };

    /**
     * @brief RVC X Image object
     *
     */
    [StructLayoutAttribute(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct Image
    {
        /**
         * @brief RVC Handle
         *
         */
        public Handle m_handle;

        /**
         * @brief Create Image object
         *
         * @param it image type
         * @param sz image size
         * @param data image data
         * @param own_data Image object
         * @return Image A Image object with given parameters
         */
        public static Image Create(ImageType type, Size sz, IntPtr data, bool own_data = true) =>
            new Image() {m_handle = RVC_CSharp_DLL.Image_Create(type, sz, data, own_data)};

        /**
         * @brief Destroy Image object
         *
         * @param img Image object will be destroyed
         * @param no_reuse True for reuse current space of PointMap
         */
        public static void Destroy(Image img, bool no_reuse = true) => RVC_CSharp_DLL.Image_Destroy(img.m_handle, no_reuse);

        /**
         * @brief Check Image obejct is Valid or not.
         *
         * @return true Valid
         * @return false Not valid
         */
        public bool IsValid() => RVC_CSharp_DLL.Image_IsValid(m_handle);

        /**
         * @brief Get the Image Size object
         *
         * @return Size A Image Size object
         */
        public Size GetSize() => RVC_CSharp_DLL.Image_GetSize(m_handle);

        /**
         * @brief Get the ImageType object
         *
         * @return ImageType Image type
         */
        public ImageType GetType() => RVC_CSharp_DLL.Image_GetType(m_handle);

        /**
         * @brief Get the Data Ptr of Image object
         *
         * @return unsigned* Data Ptr
         */
        public IntPtr GetDataPtr() => RVC_CSharp_DLL.Image_GetDataPtr(m_handle);

        /**
         * @brief Save Image to file
         *
         * @param address save address
         *
         * @return true Success
         * @return false Failed
         */
        public bool SaveImage(string addr) => RVC_CSharp_DLL.Image_SaveImage(m_handle, addr);

    };

    /**
     * @brief RVC X DepthMap
     *
     */
    [StructLayoutAttribute(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct  DepthMap
    {

        /**
         * @brief DepthMap Handle
         *
         */
        public Handle m_handle;

        /**
         * @brief Create DepthMap object
         *
         * @param sz depthmap size
         * @param data depthmap data
         * @param own_data depthmap data
         * @return DepthMap object with given parameters
         */
        public static DepthMap Create(Size sz, IntPtr data, bool own_data = true)
            => new DepthMap() {m_handle = RVC_CSharp_DLL.DepthMap_Create(sz, data, own_data)};

        /**
         * @brief Destroy DepthMap object
         *
         * @param depthmap DepthMap object will be destroyed
         * @param no_reuse True for reuse current space of PointMap
         */
        public static void Destroy(DepthMap depthmap, bool no_reuse = true) =>
            RVC_CSharp_DLL.DepthMap_Destroy(depthmap.m_handle, no_reuse);

        /**
         * @brief Check DepthMap obejct is Valid or not.
         *
         * @return true
         * @return false
         */
        public bool IsValid() => RVC_CSharp_DLL.DepthMap_IsValid(m_handle);

        /**
         * @brief Get the DepthMap Size object
         *
         * @return Size
         */
        public Size GetSize() => RVC_CSharp_DLL.DepthMap_GetSize(m_handle);

        /**
         * @brief Get the Data Ptr of DepthMap. Data unit is m, so it will be very small.
         * 
         * @return double* Data Ptr
         */
        public IntPtr GetDataPtr() => RVC_CSharp_DLL.DepthMap_GetDataPtr(m_handle);

        /**
         * @brief Save DepthMap to file
         *
         * @param address save address
         * @param is_m  save depthmap with m/mm
         *
         * @return true Success
         * @return false Failed
         */
        public bool SaveDepthMap(string address, bool is_m = false) => RVC_CSharp_DLL.DepthMap_SaveDepthMap(m_handle,address,is_m);
    };
    
    /**
     * @brief RVC X PointMap
     *
     */
    [StructLayoutAttribute(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct PointMap
    {
        /**
         * @brief RVC Handle
         *
         */
        public Handle m_handle;

        /**
         * @brief Create PointMap object
         *
         * @param pmt PointMapType
         * @param size PointMap Size
         * @param data PointMap data (m)
         * @param owndata True for malloc a new space for PointMap
         * @return PointMap A PointMap object
         */
        public static PointMap Create(PointMapType type, Size sz, IntPtr data, bool own_data = true)
            => new PointMap() {m_handle = RVC_CSharp_DLL.PointMap_Create(type, sz, data, own_data)};

        /**
         * @brief Destroy a PointMap object
         *
         * @param pm PointMap object will be destroyed
         * @param no_reuse True for reuse current space of PointMap
         */
        public static void Destroy(PointMap pm, bool no_reuse = true) => RVC_CSharp_DLL.PointMap_Destroy(pm.m_handle, no_reuse);

        /**
         * @brief Check PointMap is Valid or not
         *
         * @return true Valid
         * @return false Not valid
         */
        public bool IsValid() => RVC_CSharp_DLL.PointMap_IsValid(m_handle);

        /**
         * @brief Get the PointMap Size object
         *
         * @return Size PointMap Size
         */
        public Size GetSize() => RVC_CSharp_DLL.PointMap_GetSize(m_handle);

        /**
         * @brief Get the Point Data Ptr of PointMap object
         *
         * @return double* Point Data Ptr (m)
         */
        public IntPtr GetPointDataPtr() => RVC_CSharp_DLL.PointMap_GetPointDataPtr(m_handle);

        /**
         * @brief Get the Normal Data Ptr of PointMap object
         *
         * @return double* Normal Data Ptr
         */
        public IntPtr GetNormalDataPtr() => RVC_CSharp_DLL.PointMap_GetNormalDataPtr(m_handle);

        /**
         * @brief export PointMap's data to local file. Only support the *.ply* format.
         * @param fileName Name of file to be created.
         * @param unit The unit of exported data.
         * @param isBinary Whether to export to binary format.
         * @return bool.
        */
        public bool Save(string filename, PointMapUnit unit, bool isBinary, Image image = new Image()) =>
            RVC_CSharp_DLL.PointMap_Save(m_handle,  filename,  unit,  isBinary, image.m_handle);

        /**
         * @brief Get the Point Data Seperated
         *
         * @param x
         * @param y
         * @param z
         * @param scale  default set to 1
         * @return true
         * @return false
         */
        public bool GetPointMapSeperated(out double[] x, out double[] y, out double[] z, double scale = 1.0)
        {
            var size = this.GetSize();
            var count = size.width * size.height;
            x = new double[count];
            y = new double[count];
            z = new double[count];
            return GetPointMapSeperated(x, y, z, scale);
        }

        /**
         * @brief Get the Point Data Seperated
         *
         * @param x
         * @param y
         * @param z
         * @param scale  default set to 1
         * @return true
         * @return false
         */
        private bool GetPointMapSeperated(double[] x, double[] y, double[] z, double scale = 1.0) =>
            RVC_CSharp_DLL.PointMap_GetPointMapSeperated(m_handle, x, y, z, scale);
    };


    [StructLayoutAttribute(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct  ConfidenceMap
    {
        /**
         * @brief confidence map handle
         *
         */
        public Handle m_handle;

        /**
         * @brief create confidence map object, if object is no used, call Destroy to destroy it
         *
         * @param sz confidence map size
         * @param data confidence map data
         * @param own_data own data flag
         * @return ConfidenceMap object with given parameters
         * @sa ConfidenceMap::Destroy
         */
        public static ConfidenceMap Create(Size sz, IntPtr data, bool own_data = true) =>
            new ConfidenceMap() {m_handle = RVC_CSharp_DLL.ConfidenceMap_Create(sz, data, own_data)};

        /**
         * @brief Destroy confidence map object.
         *
         * @param confidencemap confidencemap to be destroy
         * @param no_reuse True for reuse current space of confidence map
         */
        public static void Destroy(ConfidenceMap confidencemap, bool no_reuse = true) =>
            RVC_CSharp_DLL.ConfidenceMap_Destroy(confidencemap.m_handle, no_reuse);

        /**
         * @brief Check obejct is Valid or not.
         *
         * @return true
         * @return false
         */
        public bool IsValid() => RVC_CSharp_DLL.ConfidenceMap_IsValid(m_handle);

        /**
         * @brief Get the Size object
         *
         * @return Size
         */
        public Size GetSize() => RVC_CSharp_DLL.ConfidenceMap_GetSize(m_handle);
        /**
         * @brief Get the Data Ptr object
         *
         * @return double*
         */
        public IntPtr GetDataPtr() => RVC_CSharp_DLL.ConfidenceMap_GetDataPtr(m_handle);
    };

    /**
     * @brief Image ROI
     *
     */
    [StructLayoutAttribute(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct ROI
    {
        /**
         * @brief Construct a new Image ROI object with x,y,w,h
         *
         * @param x start x of Image roi (col index of roi up left corner)
         * @param y start y of Image roi (row index of roi up left corner)
         * @param w image roi width
         * @param h image roi height
         */
        public ROI(int x, int y, int w, int h)
        {
            this.x = x;
            this.y = y;
            this.width = w;
            this.height = h;
        }
        /**
         * @brief start x of Image roi (col index of roi up left corner)
         *
         */
        public int x;
        /**
         * @brief start y of Image roi (row index of roi up left corner)
         *
         */
        public int y;
        /**
         * @brief Image roi width
         *
         */
        public int width;
        /**
         * @brief Image roi height
         *
         */
        public int height;
    };


    /**
     * @brief Device ROIRange
     *
     */
    [StructLayoutAttribute(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct ROIRange {
        /**
         * @brief step of x of Image roi (col index of roi up left corner)
         *
         */
        public int x_step;
        /**
         * @brief step of y of Image roi (row index of roi up left corner)
         *
         */
        public int y_step;
        /**
         * @brief step of width of Image roi
         *
         */
        public int width_step;
        /**
         * @brief step of height of Image roi
         *
         */
        public int height_step;
        /**
         * @brief Minimum value of width of Image roi
         *
         */
        public int width_min;
        /**
         * @brief Minimum value of height of Image roi
         *
         */
        public int height_min;
        /**
         * @brief Maximum value of width of Image roi
         *
         */
        public int width_max;
        /**
         * @brief Maximum value of height of Image roi
         *
         */
        public int height_max;
    };


    /// <summary>
    /// RVC X Device info
    /// @param name Device name
    /// @param sn Device serial number
    /// @param factroydate Device manufacture date
    /// @param port Port number
    /// @param type Support* PortType_USB* and * PortType_GIGE*
    /// @param cameraid Support* CameraID_Left*, * CameraID_Right* and * CameraID_Both*
    /// @param boardmodel main borad model type
    /// @param support_x2 support x2 or not
    /// @param support_color supported projector color
    /// @param firmware_version RVC Camera firmware version
    /// </summary>
    [StructLayoutAttribute(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct DeviceInfo
    {
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
        public string name;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
        public string sn;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
        public string factroydate;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
        public string port;
        public PortType type;
        public CameraID cameraid;
        public int boardmodel;
        [MarshalAs(UnmanagedType.I1)]
        public bool support_x2;
        public ProjectorColor support_color;
        public int workingdist_near_mm;
        public int workingdist_far_mm;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 128)]
        public string firmware_version;
        public CaptureMode support_capture_mode;
    };


    #endregion

    #region MainFunction

    /// <summary>
    /// RVC System
    /// </summary>
    [StructLayoutAttribute(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct System
    {
        /// <summary>
        /// SystemInit
        /// </summary>
        /// <returns>
        /// true Success
        /// false Failed
        /// </returns>
        public static bool Init() => RVC_CSharp_DLL.System_Init();

        /// <summary>
        /// Check system is inited or not
        /// </summary>
        /// <returns>
        /// true Inited
        /// false Not Inited
        /// </returns>
        public static bool IsInited() => RVC_CSharp_DLL.System_IsInit();

        /// <summary>
        /// SystemShutdown
        /// </summary>
        public static void Shutdown() => RVC_CSharp_DLL.System_ShutDown();

        /// <summary>
        /// List the fix number devices
        /// </summary>
        /// @param pdevices device listed
        /// @param len desire list devices number
        /// @param actual_size actually list devices number
        /// @param opt List DeviceType All/USB/GIGE optional
        /// <returns>Status code</returns>
        public static void ListDevices(Device[] pdevices, ref int actual_size, int maxLen = 10,
            SystemListDeviceType opt = SystemListDeviceType.All)
        {
            int[] handles = new int[maxLen * 2];
            RVC_CSharp_DLL.System_ListDevices(handles, maxLen, ref actual_size, opt);
            for (int i = 0; i < actual_size; i++)
            {
                pdevices[i].m_handle = new Handle()
                {
                    sid = handles[i * 2],
                    gid = handles[i * 2 + 1]
                };
            }
        }
        /// <summary>
        /// more easier way to find devices
        /// </summary>
        /// <param name="maxLen"></param>
        /// <param name="opt"></param>
        /// <returns></returns>
        public static List<Device> ListDevices(SystemListDeviceType opt = SystemListDeviceType.All, int maxLen = 100)
        {
            Device[] devices = new Device[maxLen];
            int actual_size = 0;
            ListDevices(devices, ref actual_size, maxLen, opt);
            List<Device> output = new List<Device>();
            for (int i = 0; i < actual_size; i++)
            {
                output.Add(devices[i]);
            }
            return output;
        }

        /// <summary>
        /// find target device by serialNumber
        /// </summary>
        /// @param serialNumber Device Struct serial number
        /// @return Device The serialNumber  corresponding Device Struct
        /// <returns>whether find target device</returns>
        public static bool FindDevice(string serialNumber, ref Device device)
        {
            Handle handle = new Handle();
            RVC_CSharp_DLL.System_FindDevice(serialNumber, ref handle);
            device.m_handle = handle;
            return device.IsValid();
        }


        /// <summary>
        /// find target device by serialNumber
        /// </summary>
        /// @param serialNumber Device Struct serial number
        /// @return Device The serialNumber  corresponding Device Struct
        /// <returns>whether find target device</returns>
        public static Device FindDeviceBySN(string serialNumber)
        {
            Device device = new Device();
            RVC_CSharp_DLL.System_FindDevice(serialNumber, ref device.m_handle);
            return device;
        }

        /// <summary>
        /// find target device by index
        /// </summary>
        /// @param index Device list index.
        /// @return Device The serialNumber corresponding Device Struct
        /// <returns>whether find target device</returns>
        public static Device FindDeviceByIndex(uint index)
        {
            Device device = new Device();
            var devices = ListDevices();
            if (index < devices.Count)
            {
                device = devices[(int)index];
            }
            return device;
        }

        /// <summary>
        /// find target device which is Can-Connected
        /// </summary>
        /// @param index Device list index.
        /// @return Device The serialNumber  corresponding Device Struct
        /// <returns>whether find target device</returns>
        public static Device FindDeviceCanConnected()
        {
            var devices = ListDevices();
            for (int i = 0; i < devices.Count; i++)
            {
                if (devices[i].CheckCanConnected())
                {
                    return devices[i];
                }
            }
            return new Device();
        }

        /**
         * @brief Get last error of RVC SDK
         *
         * @return int
         */
        public static int GetLastError() => RVC_CSharp_DLL.System_GetLastError();

        /**
         * @brief Get the Version of RVC SDK
         *
         * @return string of version
         */
        public static string GetVersion() => RVC_CSharp_DLL.System_GetVersion();

    }

    /// <summary>
    /// Device struct
    /// </summary>
    [StructLayoutAttribute(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct Device
    {
        /// <summary>
        /// RVC Handle
        /// </summary>
        public Handle m_handle;

        /// <summary>
        /// Destroy the device
        /// </summary>
        /// @param d Device to be destroyed
        public static void Destroy(Device d) => RVC_CSharp_DLL.Device_Destroy(d.m_handle);

        /**
         * @brief Check device is valid or not
         *
         * @return true Valid
         * @return false Not valid
         */
        public bool IsValid() => RVC_CSharp_DLL.Device_IsValid(m_handle);

        /**
         * @brief Print device info
         *
         */
        public void Print() => RVC_CSharp_DLL.Device_Print(m_handle);

        /**
         * @brief Get the DeviceInfo object
         *
         * @param pinfo Current Device information
         * @return true Success
         * @return false Failed
         */
        public bool GetDeviceInfo(ref DeviceInfo pinfo) => RVC_CSharp_DLL.Device_GetDeviceInfo(m_handle, ref pinfo);

        /**
         * @brief Set the Device network configuration
         *
         * @param d NetworkDevice
         * @param type NetworkType of Device DHCP/Static
         * @param ip New ip for Device, valid if NetworkType is *NetworkType_STATIC*
         * @param netMask New netmask for Device, valid if NetworkType is *NetworkType_STATIC*
         * @param gateway New gateway for Device, valid if NetworkType is *NetworkType_STATIC*
         * @return int status code
         */
        public int SetNetworkConfig(NetworkDevice d, NetworkType type, string ip, string netMask, string gateway) =>
            RVC_CSharp_DLL.Device_SetNetworkConfig(m_handle, d, type, ip, netMask, gateway);

        /**
         * @brief Get the device network configuration
         *
         * @param d NetworkDevice
         * @param type NetworkType of Device DHCP/Static
         * @param ip Current ip of Device
         * @param netMask Current netmask of Device
         * @param gateway Current gateway of Device
         * @param status Device`s status
         * @return int Status code
         */
        public int GetNetworkConfig(NetworkDevice d, ref NetworkType type, StringBuilder ip, StringBuilder netMask,
            StringBuilder gateway, ref NetworkDeviceStatus_ status) =>
            RVC_CSharp_DLL.Device_GetNetworkConfig(m_handle, d, ref type, ip, netMask, gateway, ref status);

        public bool CheckCanConnected()
        {
            DeviceInfo info = new DeviceInfo();
            GetDeviceInfo(ref info);

            bool canConnected = true;

            if (info.type == PortType.PortType_USB)
            {
                // Usb camera always can be connected 
                canConnected = true;
            }
            else if (info.type == PortType.PortType_GIGE)
            {
                // For the GIGE camera, we need to check the status of the LightMachine, the LeftCamera and the RightCamera.

                NetworkType networkType = NetworkType.NetworkType_DHCP;
                StringBuilder ip = new StringBuilder(256);
                StringBuilder netMask = new StringBuilder(256);
                StringBuilder gateway = new StringBuilder(256);
                NetworkDeviceStatus_ status = NetworkDeviceStatus_.NetworkDeviceStatus_OK;

                //LightMachine
                int ret1 = GetNetworkConfig(NetworkDevice.NetworkDevice_LightMachine, ref networkType, ip, netMask, gateway, ref status);
                if (ret1 == 0)
                {
                    // status means the state of assembly
                    canConnected = canConnected && status == NetworkDeviceStatus_.NetworkDeviceStatus_OK;
                }
                else
                {
                    //Failed
                    canConnected = false;
                }

                //LeftCamera
                if ((info.cameraid & CameraID.CameraID_Left) != 0)
                {
                    int ret2 = GetNetworkConfig(NetworkDevice.NetworkDevice_LeftCamera, ref networkType, ip, netMask, gateway, ref status);
                    if (ret2 == 0)
                    {
                        // status means the state of assembly
                        canConnected = canConnected && status == NetworkDeviceStatus_.NetworkDeviceStatus_OK;
                    }
                    else
                    {
                        //Failed
                        canConnected = false;
                    }
                }

                //RightCamera
                if ((info.cameraid & CameraID.CameraID_Right) != 0)
                {
                    int ret3 = GetNetworkConfig(NetworkDevice.NetworkDevice_RightCamera, ref networkType, ip, netMask, gateway, ref status);
                    if (ret3 == 0)
                    {
                        // status means the state of assembly
                        canConnected = canConnected && status == NetworkDeviceStatus_.NetworkDeviceStatus_OK;
                    }
                    else
                    {
                        //Failed
                        canConnected = false;
                    }
                }

            }
            return canConnected;
        }

    };

    [StructLayoutAttribute(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct X1
    {
        [StructLayoutAttribute(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
        public struct CaptureOptions
        {
            /// <summary>
            /// the default value of CaptureOptions
            /// </summary>
            /// <returns></returns>
            public static CaptureOptions Default()
            {
                CaptureOptions options = new CaptureOptions();
                options.calc_normal = false;
                options.calc_normal_radius = 5;
                options.transform_to_camera = false;
                options.filter_range = 0;
                options.noise_removal_distance = 0;
                options.noise_removal_point_number = 40;
                options.light_contrast_threshold = 3;
                options.phase_filter_range = 0;
                options.projector_brightness = 240;
                options.exposure_time_2d = 11;
                options.exposure_time_3d = 11;
                options.gain_2d = 0;
                options.gain_3d = 0;
                options.hdr_exposure_times = 0;
                options.hdr_exposuretime_content = new int[3];
                options.hdr_exposuretime_content[0] = 11;
                options.hdr_exposuretime_content[1] = 20;
                options.hdr_exposuretime_content[2] = 50;
                options.hdr_gain_3d = new float[3];
                options.hdr_gain_3d[0] = 0;
                options.hdr_gain_3d[1] = 0;
                options.hdr_gain_3d[2] = 0;
                options.hdr_scan_times = new int[3];
                options.hdr_scan_times[0] = 2;
                options.hdr_scan_times[1] = 2;
                options.hdr_scan_times[2] = 2;
                options.hdr_projector_brightness = new int[3];
                options.hdr_projector_brightness[0] = 240;
                options.hdr_projector_brightness[1] = 240;
                options.hdr_projector_brightness[2] = 240;
                options.gamma_2d = 1.0f;
                options.gamma_3d = 1.0f;
                options.use_projector_capturing_2d_image = true;
                options.smoothness = SmoothnessLevel.SmoothnessLevel_Off;
                options.downsample_distance = -1;
                options.capture_mode = CaptureMode.CaptureMode_Normal;
                options.confidence_threshold = 0;
                options.roi = new ROI(0, 0, 0, 0);
                options.truncate_z_min = -9999.0;
                options.truncate_z_max = 9999.0;
                options.bilateral_filter_kernal_size = 0;
                options.bilateral_filter_depth_sigma = 0;
                options.bilateral_filter_space_sigma = 0;
                options.scan_times = 2;
                return options;
            }

            /**
             * @brief flag Whether calculate 3D points normal vector
             *
             */
            [MarshalAs(UnmanagedType.I1)]
            public bool calc_normal;
            /**
             * @brief flag Whether transfrom 3D points from calibration board system to camera coordinate system
             *
             */
            [MarshalAs(UnmanagedType.I1)]
            public bool transform_to_camera;
            /**
             * Point cloud noise removal algorithm 1, contains one parameter: filter_range.
             * If this algorithm does not work well, set filter_range to 0 and try noise removal algorithm 2 below.
             * @brief Set the noise filter value. The larger the value, the greater the filtering degree.
             * The default value has been changed to 0 from 1 after v1.6.1.
             */
            [Obsolete] public int filter_range;
            /**
             *
             * Point cloud noise removal algorithm 2, contains two parameters: noise_removal_distance and
             * noise_removal_point_number. This algorithm performs noise reduction through a clustering algorithm. The point
             * cloud is classified into blocks according to the distance (noise_removal_distance). If the total number of
             * points in the block is less than a certain threshold (noise_removal_point_number), the points in the block
             * are considered as noise points and need to be removed.
             *
             * @brief Set the noise filter parameter 1. The smaller the value, the greater the filtering degree.
             * range: 0 ~ 10 (units: mm)
             */
            public double noise_removal_distance;
            /**
             * @brief Set the noise filter parameter 2. The larger the value, the greater the filtering degree.
             * range: 0 ~ 100
             */
            public int noise_removal_point_number;
            /**
             * @brief Light contrast trheshold, range in [0, 10]. The contrast of point less than this value will be treat
             * as invalid point and be removed.
             *
             */
            public int light_contrast_threshold;
            /**
             * @brief Set the phase filter value. The larger the value, the greater the filtering degree 0~40
             *
             */
            public int phase_filter_range;
            /**
             * @brief Set the exposure_time 2D value in milliseconds
             *
             */
            public int exposure_time_2d;
            /**
             * @brief Set the exposure_time 3D value in milliseconds
             *
             */
            public int exposure_time_3d;
            /**
             * @brief Set the projector brightness value
             *
             */
            public int projector_brightness;
            /**
             * @brief Set the 2D gain value
             *
             */
            public float gain_2d;
            /**
             * @brief Set the 3D gain value
             *
             */
            public float gain_3d;
            /**
             * @brief Set the hdr exposure times value. 0,2,3
             *
             */
            public int hdr_exposure_times;
            /**
             * @brief Set the hdr exposure time content. capture with white light, range [11, 100], others [3, 100]
             *
             */
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
            public int[] hdr_exposuretime_content;

            /**
             * @brief Set the hdr 3D gain content.
             *
             */
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
            public float[] hdr_gain_3d;

            /**
             * @brief Set the hdr scan times, only use in robust mode. range [2, 4],
             *
             */
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
            public int[] hdr_scan_times;
            /**
             * @brief Set the hdr projector brightness value
             *
             */
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
            public int[] hdr_projector_brightness;
            /**
             * @brief Neighborhood radius in pixel of calculating normal, > 0
             */
            public int calc_normal_radius;
            /**
             * @brief Set the 2D gamma value
             *
             */
            public float gamma_2d;
            /**
             * @brief Set the 3D gamma value
             *
             */
            public float gamma_3d;
            /**
             * @brief Set 2D image whether use projector
             *
             */
            [MarshalAs(UnmanagedType.I1)]
            public bool use_projector_capturing_2d_image;

            /**
             * @brief control point map smoothness
             *
             */
            public SmoothnessLevel smoothness;

            /**
             * @brief uniform downsample distance. if <= 0, do nothing.
             *
             */
            public double downsample_distance;

            /**
             * @brief control capture mode
             *
             */
            public CaptureMode capture_mode;

            /**
             * @brief confidence threshold, the point with confindence low then this value will be removed
             * range: [0, 1]
             *
             */
            public double confidence_threshold;

            /**
            * @brief set ROI function, only 3d points in the roi will be generated.
            * This function can improve 3d capturespeed.
            * The parameters of roi must comply with the rules of the equipment and can be checked by CheckRoi.
            * We recommend that you adjust roi automatically through C before AutoAdjustRoi.
            */
            public ROI roi;

            /**
             * @brief truncate point map and depth map under calib board coordinate by z direction minimum value (units: mm)
             * and truncate_z_min should less than truncate_z_max range: [-9999, 9999]
             *
             */
            public double truncate_z_min;

            /**
             * @brief truncate point map and depth map under calib board coordinate by z direction maximum value (units: mm)
             * and truncate_z_max should more than truncate_z_min range: [-9999, 9999]
             *
             */
            public double truncate_z_max;

            /**
             * @brief the kernal size of bilateral filter of depth map
             * range: [3, 31], 0 for not use bilateral filter
             *
             */
            public int bilateral_filter_kernal_size;

            /**
             * @brief the guassian sigma in depth of bilateral filter of depth map
             * range: [0, 100]
             *
             */
            public double bilateral_filter_depth_sigma;

            /**
             * @brief the guassian sigma in space of bilateral filter of depth map
             * range: [0, 100]
             *
             */
            public double bilateral_filter_space_sigma;

            /**
             * @brief scan times, only use in robust mode. range [2, 4],
             */
            public int scan_times;
        };

        /**
         * @brief Options when setting custom transformation
         *
         */
        [StructLayoutAttribute(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
        public struct CustomTransformOptions
        {
            /**
             * @brief base coordinate of custom transformation,default is *CoordinateSelect_Disabled*
             *
             * All support type is
             * *CoordinateSelect_Disabled*,*CoordinateSelect_Camera*,*CoordinateSelect_CaliBoard*
             */
            enum CoordinateSelect
            {
                CoordinateSelect_Disabled,
                CoordinateSelect_Camera,
                CoordinateSelect_CaliBoard,
            };

            public static CustomTransformOptions Default()
            {
                return new CustomTransformOptions()
                {
                    coordinate_select = CoordinateSelect.CoordinateSelect_Disabled,
                    transform = new double[16] { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 }
                };
            }

            /**
            * @brief base coordinate setting of custom transformation
            *
            */
            CoordinateSelect coordinate_select;

            /**
             * @brief custom transformation, translation unit: m
             * len = 16
             */
            double[] transform;
        };

        /**
         * @brief RVC Handle
         *
         */
        public Handle m_handle;

        /**
        * @brief Create a RVC X Camera and choose the CameraID which you desire before you use X1
        *
        * @param d One RVC X Camera
        * @param id Choose *CameraID_Left* or *CameraID_Right*
        * @return X1 RVC X object
        */
        public static X1 Create(Device d, CameraID id) => new X1() { m_handle = RVC_CSharp_DLL.X1_Create(d.m_handle, id) };

        /**
         * @brief Release all X1 resources after you use X1
         *
         * @param x RVC X object to be released
         *
         * @snippet X1Test.cpp Create RVC X1
         */
        public static void Destroy(X1 x) => RVC_CSharp_DLL.X1_Destroy(x.m_handle);

        public void Destroy() => RVC_CSharp_DLL.X1_Destroy(m_handle);

        /**
         * @brief Check X1 is valid or not before use X1
         *
         * @return true Available
         * @return false Not available
         *
         * @snippet X1Test.cpp Create RVC X1
         */
        public bool IsValid()
        {
            bool ret = RVC_CSharp_DLL.X1_IsValid(m_handle);
            return ret;
        }

        /**
         * @brief Open X1 before you use it
         *
         * @return true Success
         * @return false Failed
         *
         * @snippet X1Test.cpp Create RVC X1
         */
        public bool Open() => RVC_CSharp_DLL.X1_Open(m_handle);

        /**
         * @brief Close X1 after you Open it
         *
         * @snippet X1Test.cpp Create RVC X1
         */
        public void Close() => RVC_CSharp_DLL.X1_Close(m_handle);

        /**
         * @brief Check X1 is open or not
         *
         * @return true Is open
         * @return false Not open
         *
         * @snippet X1Test.cpp Create RVC X1
         */
        public bool IsOpen() => RVC_CSharp_DLL.X1_IsOpen(m_handle);

        /**
         * @brief Check X1 is physically connected or not
         *
         * @return true Is physically connected
         * @return false Not physically connected
         *
         * @snippet X1Test.cpp Create RVC X1
         */
        public bool IsPhysicallyConnected() => RVC_CSharp_DLL.X1_IsPhysicallyConnected(m_handle);

        /**
         * @brief Capture one point map and one image. This function will save capture options into camera.
         *
         * @param opts CaptureOptions
         * @return true Success
         * @return false Failed
         *
         * @snippet X1Test.cpp Capture with options
         */
        public bool Capture(CaptureOptions opts) => RVC_CSharp_DLL.X1_Capture(m_handle, opts);

        /**
         * @brief Capture one point map and one image. This function will load capture options from camera.
         *
         * @param opts CaptureOptions
         * @return true Success
         * @return false Failed
         *
         * @snippet X1Test.cpp Capture with options
         */
        public bool Capture() => RVC_CSharp_DLL.X1_Capture_(m_handle);

        /**
         * @brief Capture one image. This function will save capture options into camera. You can use GetImage() to obtain
         * 2D imgae
         *
         * @param opts CaptureOptions
         * @return true Success
         * @return false Failed
         */
        public bool Capture2D(CaptureOptions opts) => RVC_CSharp_DLL.X1_Capture2D(m_handle, opts);

        /**
         * @brief Capture one image. This function will load capture options from camera. You can use GetImage() to obtain
         * 2D imgae
         *
         * @param opts CaptureOptions
         * @return true Success
         * @return false Failed
         */
        public bool Capture2D() => RVC_CSharp_DLL.X1_Capture2D_(m_handle);

        /**
         * @brief Set the camera band width ratio
         *
         * @param percent Band width ratio
         * @return true Success
         * @return false Failed
         */
        public bool SetBandwidth(float percent) => RVC_CSharp_DLL.X1_SetBandwidth(m_handle, percent);

        /**
         * @brief Get the camera band width ratio
         *
         * @param percent Band width ratio
         * @return true Success
         * @return false Failed
         */
        public bool GetBandwidth(ref float percent) => RVC_CSharp_DLL.X1_GetBandwidth(m_handle, ref percent);

        /**
         * @brief Set the Transformation of output point cloud
         *
         * @param opts  Custom Transform Options
         * @return true
         * @return false
         */
        public bool SetCustomTransformation(CustomTransformOptions opts) => RVC_CSharp_DLL.X1_SetCustomTransformation(m_handle, opts);

        /**
         * @brief Get the Custom Transformation object
         *
         * @param opts
         * @return true
         * @return false
         */
        public bool GetCustomTransformation(ref CustomTransformOptions opts) => RVC_CSharp_DLL.X1_GetCustomTransformation(m_handle, ref opts);

        /**
         * @brief Get the Image object
         *
         * @return Image
         */
        public Image GetImage() => new Image() { m_handle = RVC_CSharp_DLL.X1_GetImage(m_handle) };

        /**
         * @brief Get the DepthMap object
         *
         * @return DepthMap A DepthMap
         */
        public DepthMap GetDepthMap() => new DepthMap() { m_handle = RVC_CSharp_DLL.X1_GetDepthMap(m_handle) };

        /**
         * @brief Get the Point Map object
         *
         * @return PointMap
         */
        public PointMap GetPointMap() => new PointMap() { m_handle = RVC_CSharp_DLL.X1_GetPointMap(m_handle) };

        /**
         * @brief Get the Confidence Map object
         *
         * @return ConfidenceMap
         */
        public ConfidenceMap GetConfidenceMap() => new ConfidenceMap() { m_handle = RVC_CSharp_DLL.X1_GetConfidenceMap(m_handle) };

        /**
         * @brief Get the extrinsic matrix
         *
         * @param matrix  extrinsic matrix,len = 16
         * @return true Success
         * @return false Failed
         */
        public bool GetExtrinsicMatrix(float[] matrix) => RVC_CSharp_DLL.X1_GetExtrinsicMatrix(m_handle, matrix);

        /**
         * @brief Get the intrinsic matrix
         *
         * @param instrinsic_matrix camera instrinsic matrix,len = 9
         * @param distortion ,len = 5
         * @return true Success
         * @return false Failed
         */
        public bool GetIntrinsicParameters(float[] instrinsic_matrix, float[] distortion) =>
            RVC_CSharp_DLL.X1_GetIntrinsicParameters(m_handle, instrinsic_matrix, distortion);

        /**
         * @brief  GetCameraTemperature
         * @note   TODO:
         * @param  seletor:
         * @param  &temperature:
         * @retval
         */
        public bool GetCameraTemperature(CameraTempSelector seletor, ref float temperature) =>
            RVC_CSharp_DLL.X1_GetCameraTemperature(m_handle, seletor, ref temperature);

        /**
         * @brief Set the white balance ratio value
         *
         * @param selector support BalanceSelector_Red, BalanceSelector_Green and BalanceSelector_Blue
         * @param value  balance ratio value
         * @return true Success
         * @return false Failed
         */
        public bool SetBalanceRatio(BalanceSelector selector, float value) => RVC_CSharp_DLL.X1_SetBalanceRatio(m_handle, selector, value);

        /**
         * @brief Get the white balance ratio value
         *
         * @param selector support BalanceSelector_Red, BalanceSelector_Green and BalanceSelector_Blue
         * @param value balance ratio value
         * @return true Success
         * @return false Failed
         */
        public bool GetBalanceRatio(BalanceSelector selector, ref float value) =>
            RVC_CSharp_DLL.X1_GetBalanceRatio(m_handle, selector, ref value);

        /**
         * @brief Get the white balance ratio value range
         *
         * @param selector support BalanceSelector_Red, BalanceSelector_Green and BalanceSelector_Blue
         * @param min_value selector's minimum value
         * @param max_value selector's maximum value
         * @return true Success
         * @return false Failed
         */
        public bool GetBalanceRange(BalanceSelector selector, ref float min_value, ref float max_value) =>
            RVC_CSharp_DLL.X1_GetBalanceRange(m_handle, selector, ref min_value, ref max_value);

        /**
         * @brief Only Color Camera can use this function. This function can get suitable white balance paramters
         *
         * @param wb_times how many images used for calculate the white balance paramters,defalut = 10
         * @param opts capture options. exposure_time_2d, gain_2d, gamma_2d will be used. use_projector_capturing_2d_image
         * == true, brightness will be used too.
         * @param roi auto white balance will be operated here
         * @return true
         * @return false
         */
        public bool AutoWhiteBalance(int wb_times, CaptureOptions opts, ROI roi) =>
            RVC_CSharp_DLL.X1_AutoWhiteBalance(m_handle, wb_times, opts, roi);

        /**
         * @brief Get the Exposure Time Range
         *
         * @param min_value exposure time minimum value
         * @param max_value exposure time maxinum value
         * @return true Success
         * @return false Failed
         */
        public bool GetExposureTimeRange(ref int min_value, ref int max_value) =>
            RVC_CSharp_DLL.X1_GetExposureTimeRange(m_handle, ref min_value, ref max_value);

        /**
         * @brief Get the Gain Range
         *
         * @param min_value gain minimum value
         * @param max_value gain minimum value
         * @return true Success
         * @return false Failed
         */
        public bool GetGainRange(ref float min_value, ref float max_value) =>
            RVC_CSharp_DLL.X1_GetGainRange(m_handle, ref min_value, ref max_value);

        /**
         * @brief Get the Gamma Range
         *
         * @param min_value gamma minimum value
         * @param max_value gamma minimum value
         * @return true Success
         * @return false Failed
         */
        public bool GetGammaRange(ref float min_value, ref float max_value) =>
            RVC_CSharp_DLL.X1_GetGammaRange(m_handle, ref min_value, ref max_value);

        /**
         * @brief Save capture option parameters
         *
         * @param opts CaptureOptions
         * @return true Success
         * @return false Failed
         */
        public bool SaveCaptureOptionParameters(CaptureOptions opts) => RVC_CSharp_DLL.X1_SaveCaptureOptionParameters(m_handle, opts);

        /**
         * @brief Get capture option parameters
         *
         * @param opts CaptureOptions
         * @return true Success
         * @return false Failed
         */
        public bool LoadCaptureOptionParameters(ref CaptureOptions opts) =>
            RVC_CSharp_DLL.X1_LoadCaptureOptionParameters(m_handle, ref opts);

        /**
         * @brief Get auto capture setting. Exposure_time_2d, exposure_time_3d, projector_brightness, light_contrast_threshold will be adjusted automatically.
         * automatically
         *
         * @param opts
         * @return CaptureOptions
         */
        public bool GetAutoCaptureSetting(ref CaptureOptions opts, ROI roi) =>
            RVC_CSharp_DLL.X1_GetAutoCaptureSetting(m_handle, ref opts, roi);

        /**
         * @brief adjust 3D capturing parameters
         *
         * @param opts [in,out] capture options. if  hdr_exposure_times > 1, hdr_exposure_times and hdr_exposuretime_content
         * will be adjusted. If hdr_exposure_times equals to 1, exposure_time_3d will be adjusted.
         * @param roi [in] if width or height equal to 0, all image will be used.
         * @return true
         * @return false
         */
        public bool GetAutoHdrCaptureSetting(ref CaptureOptions opts, ROI roi) =>
            RVC_CSharp_DLL.X1_GetAutoHdrCaptureSetting(m_handle, ref opts, roi);

        /**
         * @brief Get automatic noise removal results
         */
        public bool GetAutoNoiseRemovalSetting(ref CaptureOptions opts) =>
            RVC_CSharp_DLL.X1_GetAutoNoiseRemovalSetting(m_handle, ref opts);

        /**
        * @brief Load camera setting from local file .
        * @param filename [in]
        * @return true the content of file is correctly .
        * @return false the content of file is not correctly .
        */
        public bool LoadSettingFromFile(string filename) => RVC_CSharp_DLL.X1_LoadSettingFromFile(m_handle, filename);

        /**
         * @brief Save camera setting to local file.
         * @param filename [in]
         * @return true Successfully written to the file.
         * @return false Failed write to file.
         */
        public bool SaveSettingToFile(string filename) => RVC_CSharp_DLL.X1_SaveSettingToFile(m_handle, filename);

        /**
         * @brief Check whether the parameters of ROI meet the requirements.
         * @param roi [in] .
         * @return true
         * @return false
         */
        public bool CheckRoi(ROI roi) => RVC_CSharp_DLL.X1_CheckRoi(m_handle, roi);

        /**
         * @brief Automatically correct the parameters of ROI. You need to correct ROI before Capture/Captrue2D.
         * @param roi [in] If you want to get a maximum ROI, you can pass in the default value.
         * @return ROI Corrected ROI.
         */
        public ROI AutoAdjustRoi(ROI roi ) => RVC_CSharp_DLL.X1_AutoAdjustRoi(m_handle, roi);

        /**
         * @brief Get the range of ROI.
         */
        public bool GetRoiRange(ref ROIRange range) => RVC_CSharp_DLL.X1_GetRoiRange(m_handle, ref range);

    }

    [StructLayoutAttribute(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct X2
    {

        /**
         * @brief Capture options
         *
         */
        [StructLayoutAttribute(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
        public struct CaptureOptions
        {
            /**
             * @brief Construct a new Capture Options object
             *
             */
            public static CaptureOptions Default()
            {
                CaptureOptions options = new CaptureOptions();
                options.transform_to_camera = CameraID.CameraID_NONE;
                options.projector_brightness = 240;
                options.calc_normal = false;
                options.calc_normal_radius = 5;
                options.noise_removal_distance = 0;
                options.noise_removal_point_number = 40;
                options.light_contrast_threshold = 3;
                options.edge_noise_reduction_threshold = 2;
                options.exposure_time_2d = 11;
                options.exposure_time_3d = 11;
                options.gain_2d = 0.0f;
                options.gain_3d = 0.0f;
                options.hdr_exposure_times = 0;
                options.hdr_exposuretime_content = new int[3];
                options.hdr_exposuretime_content[0] = 11;
                options.hdr_exposuretime_content[1] = 20;
                options.hdr_exposuretime_content[2] = 50;
                options.hdr_gain_3d = new float[3];
                options.hdr_gain_3d[0] = 0;
                options.hdr_gain_3d[1] = 0;
                options.hdr_gain_3d[2] = 0;
                options.hdr_projector_brightness = new int[3];
                options.hdr_projector_brightness[0] = 240;
                options.hdr_projector_brightness[1] = 240;
                options.hdr_projector_brightness[2] = 240;
                options.gamma_2d = 1.0f;
                options.gamma_3d = 1.0f;
                options.projector_color = ProjectorColor.ProjectorColor_Blue;
                options.use_projector_capturing_2d_image = true;
                options.smoothness = SmoothnessLevel.SmoothnessLevel_Off;
                options.downsample_distance = -1;
                options.capture_mode = CaptureMode.CaptureMode_Normal;
                options.confidence_threshold = 0;
                return options;
            }

            /**
             * @brief CameraID_Left transfrom 3D points from calibration board system to left camera coordinate system
             * CameraID_Right transfrom 3D points from calibration board system to right camera coordinate system
             * other is do not transfrom
             */
            public CameraID transform_to_camera;
            /**
             * @brief Set the projector brightness value
             *
             */
            public int projector_brightness;
            /**
             * @brief flag Whether calculate 3D points normal vector
             *
             */
            [MarshalAs(UnmanagedType.I1)]
            public bool calc_normal;

            /**
             * @brief Neighborhood radius in pixel of calculating normal, > 0
             */
            public int calc_normal_radius;

            /**
             * @brief Light contrast trheshold, range in [0, 10]. The contrast of point less than this value will be treat
             * as invalid point and be removed.
             *
             */
            public int light_contrast_threshold;
            /**
             * @brief edge control after point matching, range in [0, 10], default = 2. The big the value, the more edge
             * noise to be removed.
             *
             */
            public int edge_noise_reduction_threshold;
            /**
             * @brief Set the exposure_time 2D value in milliseconds
             *
             */
            public int exposure_time_2d;
            /**
             * @brief Set the exposure_time 3D value in milliseconds
             *
             */
            public int exposure_time_3d;
            /**
             * @brief Set the 2D gain value in milliseconds
             *
             */
            public float gain_2d;
            /**
             * @brief Set the 3D gain value in milliseconds
             *
             */
            public float gain_3d;
            /**
             * @brief Set the hdr exposure times value. 0,2,3
             *
             */
            public int hdr_exposure_times;
            /**
             * @brief Set the hdr exposure time content. capture with white light, range [11, 100], others [3, 100]
             *
             */
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
            public int[] hdr_exposuretime_content;
            /**
             * @brief Set the hdr 3D gain content.
             *
             */
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
            public float[] hdr_gain_3d;
            /**
             * @brief Set the hdr projector brightness value
             *
             */
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
            public int[] hdr_projector_brightness;
            /**
             * @brief Set the 2D gamma value in milliseconds
             *
             */
            public float gamma_2d;
            /**
             * @brief Set the 3D gamma value in milliseconds
             *
             */
            public float gamma_3d;
            /**
             * @brief  projector color
             */
            public ProjectorColor projector_color;
            /**
             * @brief Set 2D image whether use projector
             *
             */
            [MarshalAs(UnmanagedType.I1)]
            public bool use_projector_capturing_2d_image;

            /**
             * @brief control point map smoothness
             *
             */
            public SmoothnessLevel smoothness;

            /**
             *
             * Point cloud noise removal algorithm, which contains two parameters: noise_removal_distance and
             * noise_removal_point_number. This algorithm performs noise reduction through a clustering algorithm. The point
             * cloud is classified into blocks according to the distance (noise_removal_distance). If the total number of
             * points in the block is less than a certain threshold (noise_removal_point_number), the points in the block
             * are considered as noise points and need to be removed.
             *
             * @brief Set the noise filter parameter 1. The smaller the value, the greater the filtering degree.
             * range: 0 ~ 10 (units: mm)
             */
            public double noise_removal_distance;
            /**
             * @brief Set the noise filter parameter 2. The larger the value, the greater the filtering degree.
             * range: 0 ~ 100
             */
            public int noise_removal_point_number;

            /**
             * @brief uniform downsample distance. if <= 0, do nothing.
             *
             */
            public double downsample_distance;

            /**
             * @brief control capture mode
             *
             */
            public CaptureMode capture_mode;

            /**
             * @brief confidence threshold, the point with confindence low then this value will be removed
             * range: [0, 1]
             *
             */
            public double confidence_threshold;
        };

        /**
         * @brief Options when setting custom transformation
         *
         */
        [StructLayoutAttribute(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
        public struct CustomTransformOptions
        {

            /**
             * @brief base coordinate of custom transformation,default is *CoordinateSelect_Disabled*
             *
             * All support type is
             * *CoordinateSelect_Disabled*,*CoordinateSelect_CameraLeft*,*CoordinateSelect_CameraRight*,*CoordinateSelect_CaliBoard*
             */
            enum CoordinateSelect
            {
                CoordinateSelect_Disabled,
                CoordinateSelect_CameraLeft,
                CoordinateSelect_CameraRight,
                CoordinateSelect_CaliBoard,
            };

            public static CustomTransformOptions Default() => new CustomTransformOptions()
            {
                coordinate_select = CoordinateSelect.CoordinateSelect_Disabled,
                transform = new double[] { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 }
            };

            /**
             * @brief base coordinate setting of custom transformation
             *
             */
            CoordinateSelect coordinate_select;

            /**
             * @brief custom transformation, translation unit: m
             *
             */
            double[] transform;
        };

        /**
         * @brief RVC Handle
         *
         */
        public Handle m_handle;

        /**
         * @brief Create a RVC X Camera before you use x2
         *
         * @param d One RVC X Camera
         * @return X2 RVC X object
         */
        public static X2 Create(Device device) => new X2() { m_handle = RVC_CSharp_DLL.X2_Create(device.m_handle) };

        /**
         * @brief Release all X2 resources after you use X2
         *
         * @param x RVC X2 object to be released
         */
        public static void Destroy(X2 x2) => RVC_CSharp_DLL.X2_Destroy(x2.m_handle);
        public  void Destroy() => RVC_CSharp_DLL.X2_Destroy(m_handle);

        /**
         * @brief Check X2 is valid or not before use X2
         *
         * @return true Available
         * @return false Not available
         */
        public bool IsValid() => RVC_CSharp_DLL.X2_IsValid(m_handle);

        /**
         * @brief Open X2 before you use it
         *
         * @return true Success
         * @return false Failed
         */
        public bool Open() => RVC_CSharp_DLL.X2_Open(m_handle);

        /**
         * @brief Close X2 after you Open it
         */
        public void Close() => RVC_CSharp_DLL.X2_Close(m_handle);

        /**
         * @brief Check X2 is open or not
         *
         * @return true Is open
         * @return false Not open
         */
        public bool IsOpen() => RVC_CSharp_DLL.X2_IsOpen(m_handle);

        /**
         * @brief Check X2 is physically connected or not
         *
         * @return true Is physically connected
         * @return false Not physically connected
         */
        public bool IsPhysicallyConnected() => RVC_CSharp_DLL.X2_IsPhysicallyConnected(m_handle);

        /**
         * @brief Capture one point map and one image.This function will save capture options into camera.
         *
         * @param opts CaptureOptions
         * @return true Success
         * @return false Failed
         */
        public bool Capture(CaptureOptions opts) => RVC_CSharp_DLL.X2_Capture(m_handle, opts);

        /**
         * @brief Capture one point map and one image.This function will load capture options from camera.
         *
         * @param opts CaptureOptions
         * @return true Success
         * @return false Failed
         */
        public bool Capture() => RVC_CSharp_DLL.X2_Capture_(m_handle);

        /**
         * @brief
         *
         * @param cid Capture one image. This function will save capture options into camera. You can use GetImage() to
         * obtain 2D imgae
         * @param opts CaptureOptions
         * @return true Success
         * @return false Failed
         */
        public bool Capture2D(CameraID cid, CaptureOptions opts) => RVC_CSharp_DLL.X2_Capture2D(m_handle, cid, opts);

        /**
         * @brief
         *
         * @param cid Capture one image. This function will save capture options into camera. You can use GetImage() to
         * obtain 2D imgae
         * @param opts CaptureOptions
         * @return true Success
         * @return false Failed
         */
        public bool Capture2D(CameraID cid) => RVC_CSharp_DLL.X2_Capture2D_(m_handle, cid);

        /**
         * @brief Set the camera band width ratio
         *
         * @param percent Band width ratio
         * @return true Success
         * @return false Failed
         */
        public bool SetBandwidth(float percent) => RVC_CSharp_DLL.X2_SetBandwidth(m_handle, percent);

        /**
         * @brief Get the camera band width ratio
         *
         * @param percent Band width ratio
         * @return true Success
         * @return false Failed
         */
        public bool GetBandwidth(ref float percent) => RVC_CSharp_DLL.X2_GetBandwidth(m_handle, ref percent);

        /**
         * @brief Set the Transformation of output point cloud
         *
         * @param opts  Custom Transform Options
         * @return true
         * @return false
         */
        public bool SetCustomTransformation(CustomTransformOptions opts) => RVC_CSharp_DLL.X2_SetCustomTransformation(m_handle, opts);

        /**
         * @brief Get the Custom Transformation object
         *
         * @param opts
         * @return true
         * @return false
         */
        public bool GetCustomTransformation(ref CustomTransformOptions opts) => RVC_CSharp_DLL.X2_GetCustomTransformation(m_handle, ref opts);

        /**
         * @brief Get the Point Map object
         *
         * @return PointMap
         */
        public PointMap GetPointMap() => new PointMap() { m_handle = RVC_CSharp_DLL.X2_GetPointMap(m_handle) };

        /**
         * @brief Get the Image object
         *
         * @return Image
         */
        public Image GetImage(CameraID cid) => new Image(){m_handle = RVC_CSharp_DLL.X2_GetImage(m_handle, cid) } ;

        /**
         * @brief Get the DepthMap object
         *
         * @return DepthMap A DepthMap
         */
        public DepthMap GetDepthMap() => new DepthMap() {m_handle = RVC_CSharp_DLL.X2_GetDepthMap(m_handle)};

        /**
         * @brief Get the Confidence Map object
         *
         * @return ConfidenceMap
         */
        public ConfidenceMap GetConfidenceMap() => new ConfidenceMap() { m_handle = RVC_CSharp_DLL.X2_GetConfidenceMap(m_handle) };

        /**
         * @brief Get extrinsic matrix
         *
         * @param cid [in] option of {CameraID_Left, CameraID_Right}
         * @param matrix [out] the extrinsic matrix,len = 16
         * @return true for success
         */
        public bool GetExtrinsicMatrix(CameraID cid, float[] matrix) => RVC_CSharp_DLL.X2_GetExtrinsicMatrix(m_handle, cid, matrix);

        /**
         * @brief Get intrinsic parameters
         *
         * @param cid [in] option of {CameraID_Left, CameraID_Right}
         * @param instrinsicMatrix [out] intrinsic parameters of selected camera,len = 9
         * @param distortion [out] distortion parameter of selected camera,len = 5
         * @return true for success.
         */
        public bool GetIntrinsicParameters(CameraID cid, float[] instrinsicMatrix, float[] distortion) =>
            RVC_CSharp_DLL.X2_GetIntrinsicParameters(m_handle, cid, instrinsicMatrix, distortion);

        /**
         * @brief  GetCameraTemperature
         * @note   TODO:
         * @param  cid:
         * @param  seletor:
         * @param  &temperature:
         * @retval
         */
        public bool GetCameraTemperature(CameraID cid, CameraTempSelector seletor, ref float temperature) =>
            RVC_CSharp_DLL.X2_GetCameraTemperature(m_handle, cid, seletor, ref temperature);

        /**
         * @brief Only Color Camera can use this function. This function can get suitable white balance paramters
         *
         * @param wb_times how many images used for calculate the white balance paramters, default = 10
         * @param opts capture options. exposure_time_2d, gain_2d, gamma_2d will be used. use_projector_capturing_2d_image
         * == true, brightness will be used too.
         * @param roi auto white balance will be operated here
         * @return true
         * @return false
         */
        public bool AutoWhiteBalance(int wb_times, CaptureOptions opts, ROI roi) =>
            RVC_CSharp_DLL.X2_AutoWhiteBalance(m_handle, wb_times, opts, roi);

        /**
         * @brief Get the Exposure Time Range
         *
         * @param min_value exposure time minimum value
         * @param max_value exposure time maxinum value
         * @return true Success
         * @return false Failed
         */
        public bool GetExposureTimeRange(ref int min_value, ref int max_value) =>
            RVC_CSharp_DLL.X2_GetExposureTimeRange(m_handle, ref min_value, ref max_value);

        /**
         * @brief Get the Gain Range
         *
         * @param min_value gain minimum value
         * @param max_value gain minimum value
         * @return true Success
         * @return false Failed
         */
        public bool GetGainRange(ref float min_value, ref float max_value) =>
            RVC_CSharp_DLL.X2_GetGainRange(m_handle, ref min_value, ref max_value);

        /**
         * @brief Get the Gamma Range
         *
         * @param min_value gamma minimum value
         * @param max_value gamma minimum value
         * @return true Success
         * @return false Failed
         */
        public bool GetGammaRange(ref float min_value, ref float max_value) =>
            RVC_CSharp_DLL.X2_GetGammaRange(m_handle, ref min_value, ref max_value);

        /**
         * @brief Save capture option parameters
         *
         * @param opts CaptureOptions
         * @return true Success
         * @return false Failed
         */
        public bool SaveCaptureOptionParameters(CaptureOptions opts) =>
            RVC_CSharp_DLL.X2_SaveCaptureOptionParameters(m_handle, opts);

        /**
         * @brief Get capture option parameters
         *
         * @param opts CaptureOptions
         * @return true Success
         * @return false Failed
         */
        public bool LoadCaptureOptionParameters(ref CaptureOptions opts) =>
            RVC_CSharp_DLL.X2_LoadCaptureOptionParameters(m_handle, ref opts);

        /**
         * @brief Get auto capture setting. Exposure_time_2d, exposure_time_3d, projector_brightness, light_contrast_threshold will be adjusted automatically.
         * automatically
         *
         * @param opts
         * @return CaptureOptions
         */
        public bool GetAutoCaptureSetting(ref CaptureOptions opts, ROI roi) =>
            RVC_CSharp_DLL.X2_GetAutoCaptureSetting(m_handle, ref opts, roi);

        /**
         * @brief adjust 3D capturing parameters
         *
         * @param opts [in,out] capture options. if  hdr_exposure_times > 1, hdr_exposure_times and hdr_exposuretime_content
         * will be adjusted. If hdr_exposure_times equals to 1, exposure_time_3d will be adjusted.
         * @param roi [in] if width or height equal to 0, all image will be used.
         * @return true
         * @return false
         */
        public bool GetAutoHdrCaptureSetting(ref CaptureOptions opts, ROI roi) =>
            RVC_CSharp_DLL.X2_GetAutoHdrCaptureSetting(m_handle, ref opts, roi);

        /**
         * @brief Get automatic noise removal results
         */
        public bool GetAutoNoiseRemovalSetting(ref CaptureOptions opts) =>
            RVC_CSharp_DLL.X2_GetAutoNoiseRemovalSetting(m_handle, ref opts);

        /**
        * @brief Load camera setting from local file .
        * @param filename [in]
        * @return true the content of file is correctly .
        * @return false the content of file is not correctly .
        */
        public bool LoadSettingFromFile(string filename) =>
            RVC_CSharp_DLL.X2_LoadSettingFromFile(m_handle, filename);

        /**
         * @brief Save camera setting to local file.
         * @param filename [in]
         * @return true Successfully written to the file.
         * @return false Failed write to file.
         */
        public bool SaveSettingToFile(string filename) =>
            RVC_CSharp_DLL.X2_SaveSettingToFile(m_handle, filename);
    };

    #endregion

    #region DLL

    public class RVC_CSharp_DLL
    {
        #region Other

        [DllImport("RVC_C.dll")]
        public extern static string ImageType_ToString(ImageType type);

        [DllImport("RVC_C.dll")]
        public extern static int ImageType_GetPixelSize(ImageType type);

        [DllImport("RVC_C.dll")]
        public extern static string PointMapType_ToString(PointMapType type);

        #endregion

        #region System

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool System_Init();

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool System_IsInit();

        [DllImport("RVC_C.dll")]
        public extern static void System_ShutDown();

        [DllImport("RVC_C.dll")]
        public extern static void System_ListDevices(int[] pdevices, int len, ref int actual_size,
            SystemListDeviceType opt = SystemListDeviceType.All);

        [DllImport("RVC_C.dll")]
        public extern static void System_FindDevice(string serialNumber, ref Handle deviceHandle);

        [DllImport("RVC_C.dll")]
        public extern static int System_GetLastError();

        [DllImport("RVC_C.dll")]
        public extern static string System_GetVersion();

        #endregion

        #region Device

        [DllImport("RVC_C.dll")]
        public extern static void Device_Destroy(Handle devicehandle);

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool Device_IsValid(Handle devicehandle);

        [DllImport("RVC_C.dll")]
        public extern static void Device_Print(Handle devicehandle);

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool Device_GetDeviceInfo(Handle devicehandle, ref DeviceInfo pinfo);

        [DllImport("RVC_C.dll")]
        public extern static int Device_SetNetworkConfig(Handle devicehandle, NetworkDevice d, NetworkType type, string ip, string netMask,
            string gateway);

        [DllImport("RVC_C.dll")]
        public extern static int Device_GetNetworkConfig(Handle devicehandle, NetworkDevice d, ref NetworkType type, StringBuilder ip, StringBuilder netMask, StringBuilder gateway, ref NetworkDeviceStatus_ status);

        #endregion

        #region X1

        [DllImport("RVC_C.dll")]
        public extern static Handle X1_Create(Handle deviceHandle, CameraID id);

        [DllImport("RVC_C.dll")]
        public extern static void X1_Destroy(Handle x1Handle);

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool X1_IsValid(Handle x1Handle);

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool X1_Open(Handle x1Handle);

        [DllImport("RVC_C.dll")]
        public extern static void X1_Close(Handle x1Handle);

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool X1_IsOpen(Handle x1Handle);

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool X1_IsPhysicallyConnected(Handle x1Handle);

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool X1_Capture(Handle x1Handle, X1.CaptureOptions opts);
        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool X1_Capture_(Handle x1Handle);

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool X1_Capture2D(Handle x1Handle, X1.CaptureOptions opts);
        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool X1_Capture2D_(Handle x1Handle);

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool X1_SetBandwidth(Handle x1Handle, float percent);

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool X1_GetBandwidth(Handle x1Handle, ref float percent);

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool X1_SetCustomTransformation(Handle x1Handle, X1.CustomTransformOptions opts);

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool X1_GetCustomTransformation(Handle x1Handle, ref X1.CustomTransformOptions opts);

        [DllImport("RVC_C.dll")]
        public extern static Handle X1_GetImage(Handle x1Handle);

        [DllImport("RVC_C.dll")]
        public extern static Handle X1_GetDepthMap(Handle x1Handle);

        [DllImport("RVC_C.dll")]
        public extern static Handle X1_GetPointMap(Handle x1Handle);

        [DllImport("RVC_C.dll")]
        public extern static Handle X1_GetConfidenceMap(Handle x1Handle);

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool X1_GetExtrinsicMatrix(Handle x1Handle, float[] matrix);

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool X1_GetIntrinsicParameters(Handle x1Handle, float[] instrinsic_matrix, float[] distortion);

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool X1_GetCameraTemperature(Handle x1Handle, CameraTempSelector seletor, ref float temperature);

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool X1_SetBalanceRatio(Handle x1Handle, BalanceSelector selector, float value);

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool X1_GetBalanceRatio(Handle x1Handle, BalanceSelector selector, ref float value);

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool X1_GetBalanceRange(Handle x1Handle, BalanceSelector selector, ref float min_value, ref float max_value);

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool X1_AutoWhiteBalance(Handle x1Handle, int wb_times, X1.CaptureOptions opts, ROI roi);

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool X1_GetExposureTimeRange(Handle x1Handle, ref int min_value, ref int max_value);

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool X1_GetGainRange(Handle x1Handle, ref float min_value, ref float max_value);

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool X1_GetGammaRange(Handle x1Handle, ref float min_value, ref float max_value);

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool X1_SaveCaptureOptionParameters(Handle x1Handle, X1.CaptureOptions opts);

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool X1_LoadCaptureOptionParameters(Handle x1Handle, ref X1.CaptureOptions opts);

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool X1_GetAutoCaptureSetting(Handle x1Handle, ref X1.CaptureOptions opts, ROI roi);

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool X1_GetAutoHdrCaptureSetting(Handle x1Handle, ref X1.CaptureOptions opts, ROI roi);

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool X1_GetAutoNoiseRemovalSetting(Handle x1Handle, ref X1.CaptureOptions opts);

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool X1_LoadSettingFromFile(Handle x1Handle, string filename);

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool X1_SaveSettingToFile(Handle x1Handle, string filename);

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool   X1_CheckRoi(Handle x1Handle, ROI roi);

        [DllImport("RVC_C.dll")]
        public extern static ROI X1_AutoAdjustRoi(Handle x1Handle, ROI roi);

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool X1_GetRoiRange(Handle x1Handle, ref ROIRange range);
        #endregion

        #region X2

        [DllImport("RVC_C.dll")]
        public extern static Handle X2_Create(Handle deviceHandle);

        [DllImport("RVC_C.dll")]
        public extern static void X2_Destroy(Handle x2Handle);

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool X2_IsValid(Handle x2Handle);

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool X2_Open(Handle x2Handle);

        [DllImport("RVC_C.dll")]
        public extern static void X2_Close(Handle x2Handle);

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool X2_IsOpen(Handle x2Handle);

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool X2_IsPhysicallyConnected(Handle x2Handle);

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool X2_Capture(Handle x2Handle, X2.CaptureOptions opts);

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool X2_Capture_(Handle x2Handle);

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool X2_Capture2D(Handle x2Handle, CameraID cid, X2.CaptureOptions opts);

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool X2_Capture2D_(Handle x2Handle, CameraID cid);

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool X2_SetBandwidth(Handle x2Handle, float percent);

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool X2_GetBandwidth(Handle x2Handle, ref float percent);

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool X2_SetCustomTransformation(Handle x2Handle, X2.CustomTransformOptions opts);

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool X2_GetCustomTransformation(Handle x2Handle, ref X2.CustomTransformOptions opts);

        [DllImport("RVC_C.dll")]
        public extern static Handle X2_GetPointMap(Handle x2Handle);

        [DllImport("RVC_C.dll")]
        public extern static Handle X2_GetImage(Handle x2Handle, CameraID cid);

        [DllImport("RVC_C.dll")]
        public extern static Handle X2_GetDepthMap(Handle x2Handle);

        [DllImport("RVC_C.dll")]
        public extern static Handle X2_GetConfidenceMap(Handle x2Handle);

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool X2_GetExtrinsicMatrix(Handle x2Handle, CameraID cid, float[] matrix);

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool X2_GetIntrinsicParameters(Handle x2Handle, CameraID cid, float[] instrinsicMatrix, float[] distortion);

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool X2_GetCameraTemperature(Handle x2Handle, CameraID cid, CameraTempSelector seletor, ref float temperature);

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool X2_AutoWhiteBalance(Handle x2Handle, int wb_times, X2.CaptureOptions opts, ROI roi);

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool X2_GetExposureTimeRange(Handle x2Handle, ref int min_value, ref int max_value);

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool X2_GetGainRange(Handle x2Handle, ref float min_value, ref float max_value);

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool X2_GetGammaRange(Handle x2Handle, ref float min_value, ref float max_value);

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool X2_SaveCaptureOptionParameters(Handle x2Handle, X2.CaptureOptions opts);

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool X2_LoadCaptureOptionParameters(Handle x2Handle, ref X2.CaptureOptions opts);

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool X2_GetAutoCaptureSetting(Handle x2Handle, ref X2.CaptureOptions opts, ROI roi);

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool X2_GetAutoHdrCaptureSetting(Handle x2Handle, ref X2.CaptureOptions opts, ROI roi);

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool X2_GetAutoNoiseRemovalSetting(Handle x2Handle, ref X2.CaptureOptions opts);

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool X2_LoadSettingFromFile(Handle x2Handle, string filename);

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool X2_SaveSettingToFile(Handle x2Handle, string filename);

        #endregion

        #region Image

        [DllImport("RVC_C.dll")]
        public extern static Handle Image_Create(ImageType it, Size sz, IntPtr data, bool own_data = true);

        [DllImport("RVC_C.dll")]
        public extern static void Image_Destroy(Handle imageHandle, bool no_reuse = true);

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool Image_IsValid(Handle imageHandle);

        [DllImport("RVC_C.dll")]
        public extern static Size Image_GetSize(Handle imageHandle);

        [DllImport("RVC_C.dll")]
        public extern static ImageType Image_GetType(Handle imageHandle);

        [DllImport("RVC_C.dll")]
        public extern static IntPtr Image_GetDataPtr(Handle imageHandle);

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool Image_SaveImage(Handle imageHandle, string addr);

        #endregion

        #region DepthMap

        [DllImport("RVC_C.dll")]
        public extern static Handle DepthMap_Create(Size sz, IntPtr data, bool own_data = true);

        [DllImport("RVC_C.dll")]
        public extern static void DepthMap_Destroy(Handle depthHandle, bool no_reuse = true);

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool DepthMap_IsValid(Handle depthHandle);

        [DllImport("RVC_C.dll")]
        public extern static Size DepthMap_GetSize(Handle depthHandle);

        [DllImport("RVC_C.dll")]
        public extern static IntPtr DepthMap_GetDataPtr(Handle depthHandle);

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool DepthMap_SaveDepthMap(Handle depthHandle, string address, bool is_m = true);

        #endregion

        #region PointMap

        [DllImport("RVC_C.dll")]
        public extern static Handle PointMap_Create(PointMapType type, Size size, IntPtr data, bool owndata = true);

        [DllImport("RVC_C.dll")]
        public extern static void PointMap_Destroy(Handle pointMapHandle, bool no_reuse = true);

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool PointMap_IsValid(Handle pointMapHandle);

        [DllImport("RVC_C.dll")]
        public extern static Size PointMap_GetSize(Handle pointMapHandle);

        [DllImport("RVC_C.dll")]
        public extern static IntPtr PointMap_GetPointDataPtr(Handle pointMapHandle);

        [DllImport("RVC_C.dll")]
        public extern static IntPtr PointMap_GetNormalDataPtr(Handle pointMapHandle);

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool PointMap_GetPointMapSeperated(Handle pointMapHandle, double[] x, double[] y, double[] z, double scale = 1.0);

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool PointMap_Save(Handle pointMapHandle, string filename, PointMapUnit unit, bool isBinary, Handle imageHandle);

        #endregion

        #region ConfidenceMap

        [DllImport("RVC_C.dll")]
        public extern static Handle ConfidenceMap_Create(Size sz, IntPtr data, bool own_data = true);

        [DllImport("RVC_C.dll")]
        public extern static void ConfidenceMap_Destroy(Handle confidenceHandle, bool no_reuse = true);

        [DllImport("RVC_C.dll")]
        [return: MarshalAs(UnmanagedType.I1)]
        public extern static bool ConfidenceMap_IsValid(Handle confidenceHandle);

        [DllImport("RVC_C.dll")]
        public extern static Size ConfidenceMap_GetSize(Handle confidenceHandle);

        [DllImport("RVC_C.dll")]
        public extern static IntPtr ConfidenceMap_GetDataPtr(Handle confidenceHandle);

        #endregion
    }

    #endregion

}
