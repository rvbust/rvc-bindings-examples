cmake_minimum_required(VERSION 3.10)

project(RVCExampleCPP C CXX)

set(CMAKE_CXX_STANDARD 11)

option(USE_PCL "Enable samples which depend on Point Cloud Library (PCL)" OFF)
option(USE_Open3D "Enable samples which depend on Open3D" OFF)
option(USE_OpenCV "Enable samples which depend on OpenCV" OFF)

set(SAMPLES 
    CaptureUSB
    CaptureGigE
    GetValidPointMap
    GetImageCorresponcePoint
    SaveColorPointMap
    GetDepthImage
    GetCameraParameter
    AdjustCaptureParameter
    CaptureInContinueMode
    CaptureAndConvertToPCLType
    CaptureByX2
    GetNormalMap
    X1HDR
    X2HDR
    SaveLoadCaptureOptions
    X1SetTransformation
    X2SetTransformation
    TruncatePointCloud
    X1AutoSetParam
    X2AutoSetParam
    GetPointMapSeperated
    #CaptureWriteOpen3D
    GetSmoothPointMap
    GetDownsamplePointMap
    GetCaliBoardPoseX1
    GetCaliBoardPoseX2
    X1Capture2D
    X2Capture2D
    AdjustCaptureMode
    ConvertDepthMapToPointMap
    X1AutoHdrSetParam
    X2AutoHdrSetParam
    LaserCameraCapture
    GetConfidenceMap
    GetNoiseRemovalPointMap
    GetAutoNoiseRemovalSetting
    SetROI
    SaveLoadCameraSetting
    GetBilateralFilteredPointMap
    GetZFilteredPointMap
    QuickCaptureX1
    QuickCaptureX2
    CaptureOptionsX1
    CaptureOptionsX2
)

set(PCL_DEPENDING CaptureAndConvertToPCLType)
set(OpenCV_DEPENDING GetCaliBoardPoseX1 GetCaliBoardPoseX2 ConvertDepthMapToPointMap)

if (RVC_BUILD_SDK)
    set(RVC_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/Include")
    set(RVC_LIBS RVC)
else()
    find_package(CUDA 9.0 QUIET)
    if(CUDA_FOUND)
        enable_language(CUDA)
    endif(CUDA_FOUND)
    if(WIN32)
        set(RVC_ROOT "../..")
        set(RVC_INCLUDE_DIRS "${RVC_ROOT}/include")
        set(RVC_LIB_DIR "${RVC_ROOT}/lib")
        file(GLOB RVC_LIBS "${RVC_LIB_DIR}/*.lib" ABSOLUTE)
    else(WIN32)
        set(RVC_ROOT "/opt/RVC")
        set(RVC_INCLUDE_DIRS "${RVC_ROOT}/include")
        set(RVC_LIB_DIR "${RVC_ROOT}/lib")
        file(GLOB RVC_LIBS "${RVC_LIB_DIR}/libRVC.so" ABSOLUTE)
        file(GLOB RVC_DEPS_LIBS "${RVC_LIB_DIR}/externals/*.so" ABSOLUTE)
    endif(WIN32)
    list(LENGTH RVC_LIBS RVC_LIBS_LEN)
endif()
    
message(STATUS "Using RVC library in ${RVC_LIBS}.")

include_directories(${RVC_INCLUDE_DIRS})

macro(disable_samples DEPENDENCY_NAME)
    message(STATUS "${DEPENDENCY_NAME} samples have been disabled:")
    foreach(SAMPLE ${SAMPLES})
        get_filename_component(SAMPLE_NAME ${SAMPLE} NAME)
        set(DEPENDENCY_LIST "${DEPENDENCY_NAME}_DEPENDING")
        if(${SAMPLE_NAME} IN_LIST ${DEPENDENCY_LIST})
            message(STATUS "  - ${SAMPLE}")
            list(REMOVE_ITEM SAMPLES ${SAMPLE})
        endif()
    endforeach()
endmacro()

if(USE_PCL)
    set(PCL_ROOT "$ENV{HOME}/Rvbust/Install/PCL")
    set(PCL_DIR "${PCL_ROOT}/share/pcl-1.9")
    find_package(PCL COMPONENTS common)
    if(NOT PCL_FOUND)
        message(FATAL_ERROR "Point Cloud Library (PCL) not found. Please point PCL_DIR to the directory of your PCL installation (containing the file PCLConfig.cmake), or disable the PCL samples with -DUSE_PCL=OFF.")
    endif()
else()
    disable_samples("PCL")
endif()

if(USE_OpenCV)
    find_package(OpenCV)
    if(NOT OpenCV_FOUND)
        message(FATAL_ERROR "OpenCV not found. Please point OpenCV_DIR to the directory of your OpenCV installation (containing the file OpenCVConfig.cmake) with -DOpenCV_DIR=path/to/opencv/installation, or disable the OpenCV samples with -DUSE_OpenCV=OFF.")
    endif()
else()
    disable_samples("OpenCV")
endif()


add_library(Save_IO ${CMAKE_CURRENT_SOURCE_DIR}/IO/SavePointMap.cpp ${CMAKE_CURRENT_SOURCE_DIR}/IO/FileIO.cpp)
add_library(Utils ${CMAKE_CURRENT_SOURCE_DIR}/Utils/PointCloudUtils.cpp)

if(OpenCV_FOUND)
    add_library(CaliBoardUtils ${CMAKE_CURRENT_SOURCE_DIR}/Utils/CaliBoardUtils.cpp)
    target_link_libraries(CaliBoardUtils PUBLIC ${OpenCV_LIBS} ${RVC_LIBS})
    target_include_directories(CaliBoardUtils PUBLIC ${OpenCV_I} ${RVC_INCLUDE_DIRS})
endif(OpenCV_FOUND)

if(WIN32)
else()
target_link_libraries(Save_IO stdc++fs) #filesystem
endif()

message(STATUS "All samples: ${SAMPLES}")

foreach(SAMPLE_NAME ${SAMPLES})
    #get_filename_component(SAMPLE_NAME ${SAMPLE} NAME)

    add_executable(${SAMPLE_NAME} ${SAMPLE_NAME}.cpp)

    target_link_libraries(${SAMPLE_NAME} ${RVC_LIBS} ${RVC_DEPS_LIBS} Save_IO Utils)
    target_include_directories(${SAMPLE_NAME} SYSTEM PRIVATE ${RVC_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR})

    if(${SAMPLE_NAME} IN_LIST PCL_DEPENDING)
        target_link_libraries(${SAMPLE_NAME} ${PCL_LIBRARIES})
        target_include_directories(${SAMPLE_NAME} SYSTEM PRIVATE ${PCL_INCLUDE_DIRS})
    endif()

    if(${SAMPLE_NAME} IN_LIST Open3D_DEPENDING)
        target_link_libraries(${SAMPLE_NAME} ${Open3D_LIBRARIES})
        target_include_directories(${SAMPLE_NAME} SYSTEM PRIVATE ${Open3D_INCLUDE_DIRS})
    endif()

    if(${SAMPLE_NAME} IN_LIST OpenCV_DEPENDING)
        target_link_libraries(${SAMPLE_NAME} CaliBoardUtils)
    endif()
endforeach()

