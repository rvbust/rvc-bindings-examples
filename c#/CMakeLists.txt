cmake_minimum_required(VERSION 3.10)
project("RVC_CSharp" CSharp)

include(CSharpUtilities)

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(RVC_C)

add_library(RVC_CSharp SHARED 
    RVC_CSharp.cs
    RVC_CSharp_Tool.cs
)

set_property(TARGET RVC_CSharp PROPERTY VS_DOTNET_TARGET_FRAMEWORK_VERSION "v4.7.2")
set_property(TARGET RVC_CSharp PROPERTY WIN64_EXECUTABLE TRUE)
set(CMAKE_CSharp_FLAGS "${CMAKE_CXX_FLAGS} /langversion:latest /platform:x64")

target_link_libraries(RVC_CSharp RVC_C)
 
set_property(TARGET RVC_CSharp PROPERTY VS_DOTNET_REFERENCES
    "Microsoft.CSharp"
    "System"
    "System.Linq"
    "System.Threading.Tasks"
    "System.Windows.Forms"
    "System.Runtime.InteropServices"
    "System.IO"
    "System.Drawing"
)

option(OpenCV_Enable "whether use OpenCV  for Extension Function" ON)
option(Halcon_Enable "whether use Halcon for Extension Function. Assuming you have obtainedt lincenses." OFF)
option(VisionPro_Enable "whether use Halcon for Extension Function. Assuming you have obtainedt lincenses." OFF)


add_library(RVC_CSharp_Extension SHARED
    Halcon_Extension.cs
    Opencv_Extension.cs
    VisionPro_Extension.cs
)


if(OpenCV_Enable AND Halcon_Enable)
    set_property(TARGET RVC_CSharp_Extension PROPERTY VS_PACKAGE_REFERENCES "OpenCvSharp4.Windows_4.7.0.20230115;HalconDotNet_19.11.0")
elseif(OpenCV_Enable)
    set_property(TARGET RVC_CSharp_Extension PROPERTY VS_PACKAGE_REFERENCES "OpenCvSharp4.Windows_4.7.0.20230115")
elseif(Halcon_Enable)
    set_property(TARGET RVC_CSharp_Extension PROPERTY VS_PACKAGE_REFERENCES "HalconDotNet_19.11.0")
endif()


if(OpenCV_Enable)
    add_compile_definitions(OpenCV_Enable)
endif()

if(Halcon_Enable)
    add_compile_definitions(Halcon_Enable)
endif()

if(VisionPro_Enable)
    add_compile_definitions(VisionPro_Enable)
endif()


set_property(TARGET RVC_CSharp_Extension PROPERTY VS_DOTNET_TARGET_FRAMEWORK_VERSION "v4.7.2")
set_property(TARGET RVC_CSharp_Extension PROPERTY WIN64_EXECUTABLE TRUE)
set(CMAKE_CSharp_FLAGS "${CMAKE_CXX_FLAGS} /langversion:latest /platform:x64")

target_link_libraries(RVC_CSharp_Extension RVC_CSharp)

if(VisionPro_Enable )
    set_property(TARGET RVC_CSharp_Extension PROPERTY VS_DOTNET_REFERENCES
        "Microsoft.CSharp"
        "System"
        "System.Linq"
        "System.Threading.Tasks"
        "System.Windows.Forms"
        "System.Runtime.InteropServices"
        "System.IO"
        "System.Drawing"

        "Cognex.VisionPro.Core.dll"
        "Cognex.VisionPro.CorePlus.dll"
        "Cognex.VisionPro.dll"
        "Cognex.VisionPro.ImageFile.dll"
        "Cognex.VisionPro.Interop.Core.dll"
    
        "Cognex.VisionPro3D.Controls.dll"
        "Cognex.VisionPro3D.Core.dll"
        "Cognex.VisionPro3D.Display.Controls.dll"
        "Cognex.VisionPro3D.dll"
        "Cognex.VisionPro3D.Graphic.dll"
    )
else()
    set_property(TARGET RVC_CSharp_Extension PROPERTY VS_DOTNET_REFERENCES
            "Microsoft.CSharp"
            "System"
            "System.Linq"
            "System.Threading.Tasks"
            "System.Windows.Forms"
            "System.Runtime.InteropServices"
            "System.IO"
            "System.Drawing"
        )
endif()


add_executable(RVC_Example_CameraTest
    CameraTest.cs
)

set_property(TARGET RVC_Example_CameraTest PROPERTY VS_DOTNET_TARGET_FRAMEWORK_VERSION "v4.7.2")
set_property(TARGET RVC_Example_CameraTest PROPERTY WIN64_EXECUTABLE TRUE)
set(CMAKE_CSharp_FLAGS "${CMAKE_CXX_FLAGS} /langversion:latest /platform:x64")

target_link_libraries(RVC_Example_CameraTest RVC_CSharp RVC_CSharp_Extension)
 
set_property(TARGET RVC_Example_CameraTest PROPERTY VS_DOTNET_REFERENCES
    "Microsoft.CSharp"
    "System"
    "System.Linq"
    "System.Threading.Tasks"
    "System.Windows.Forms"
    "System.Runtime.InteropServices"
    "System.IO"
    "System.Drawing"
)


add_executable(RVC_Example_CaptureOptions_X1
    CaptureOptions_X1.cs
)
set_property(TARGET RVC_Example_CaptureOptions_X1 PROPERTY VS_DOTNET_TARGET_FRAMEWORK_VERSION "v4.7.2")
set_property(TARGET RVC_Example_CaptureOptions_X1 PROPERTY WIN64_EXECUTABLE TRUE)
set(CMAKE_CSharp_FLAGS "${CMAKE_CXX_FLAGS} /langversion:latest /platform:x64")
target_link_libraries(RVC_Example_CaptureOptions_X1 RVC_CSharp RVC_CSharp_Extension)
set_property(TARGET RVC_Example_CaptureOptions_X1 PROPERTY VS_DOTNET_REFERENCES
    "Microsoft.CSharp"
    "System"
    "System.Linq"
    "System.Threading.Tasks"
    "System.Windows.Forms"
    "System.Runtime.InteropServices"
    "System.IO"
    "System.Drawing"
    
    "Cognex.VisionPro.Core.dll"
    "Cognex.VisionPro.CorePlus.dll"
    "Cognex.VisionPro.dll"
    "Cognex.VisionPro.ImageFile.dll"
    "Cognex.VisionPro.Interop.Core.dll"
    
    "Cognex.VisionPro3D.Controls.dll"
    "Cognex.VisionPro3D.Core.dll"
    "Cognex.VisionPro3D.Display.Controls.dll"
    "Cognex.VisionPro3D.dll"
    "Cognex.VisionPro3D.Graphic.dll"
)


add_executable(RVC_Example_CaptureOptions_X2
    CaptureOptions_X2.cs
)
set_property(TARGET RVC_Example_CaptureOptions_X2 PROPERTY VS_DOTNET_TARGET_FRAMEWORK_VERSION "v4.7.2")
set_property(TARGET RVC_Example_CaptureOptions_X2 PROPERTY WIN64_EXECUTABLE TRUE)
set(CMAKE_CSharp_FLAGS "${CMAKE_CXX_FLAGS} /langversion:latest /platform:x64")
target_link_libraries(RVC_Example_CaptureOptions_X2 RVC_CSharp RVC_CSharp_Extension)
set_property(TARGET RVC_Example_CaptureOptions_X2 PROPERTY VS_DOTNET_REFERENCES
    "Microsoft.CSharp"
    "System"
    "System.Linq"
    "System.Threading.Tasks"
    "System.Windows.Forms"
    "System.Runtime.InteropServices"
    "System.IO"
    "System.Drawing"
    
    "Cognex.VisionPro.Core.dll"
    "Cognex.VisionPro.CorePlus.dll"
    "Cognex.VisionPro.dll"
    "Cognex.VisionPro.ImageFile.dll"
    "Cognex.VisionPro.Interop.Core.dll"
    
    "Cognex.VisionPro3D.Controls.dll"
    "Cognex.VisionPro3D.Core.dll"
    "Cognex.VisionPro3D.Display.Controls.dll"
    "Cognex.VisionPro3D.dll"
    "Cognex.VisionPro3D.Graphic.dll"
)

add_executable(RVC_Example_MultiCamera
    MultiCamera.cs
)
set_property(TARGET RVC_Example_MultiCamera PROPERTY VS_DOTNET_TARGET_FRAMEWORK_VERSION "v4.7.2")
set_property(TARGET RVC_Example_MultiCamera PROPERTY WIN64_EXECUTABLE TRUE)
set(CMAKE_CSharp_FLAGS "${CMAKE_CXX_FLAGS} /langversion:latest /platform:x64")
target_link_libraries(RVC_Example_MultiCamera RVC_CSharp RVC_CSharp_Extension)
set_property(TARGET RVC_Example_MultiCamera PROPERTY VS_DOTNET_REFERENCES
    "Microsoft.CSharp"
    "System"
    "System.Linq"
    "System.Threading.Tasks"
    "System.Windows.Forms"
    "System.Runtime.InteropServices"
    "System.IO"
    "System.Drawing"
)



add_executable(RVC_Example_QuickCapture_X1
    QuickCapture_X1.cs
)
set_property(TARGET RVC_Example_QuickCapture_X1 PROPERTY VS_DOTNET_TARGET_FRAMEWORK_VERSION "v4.7.2")
set_property(TARGET RVC_Example_QuickCapture_X1 PROPERTY WIN64_EXECUTABLE TRUE)
set(CMAKE_CSharp_FLAGS "${CMAKE_CXX_FLAGS} /langversion:latest /platform:x64")
target_link_libraries(RVC_Example_QuickCapture_X1 RVC_CSharp RVC_CSharp_Extension)
set_property(TARGET RVC_Example_QuickCapture_X1 PROPERTY VS_DOTNET_REFERENCES
    "Microsoft.CSharp"
    "System"
    "System.Linq"
    "System.Threading.Tasks"
    "System.Windows.Forms"
    "System.Runtime.InteropServices"
    "System.IO"
    "System.Drawing"
    
    "Cognex.VisionPro.Core.dll"
    "Cognex.VisionPro.CorePlus.dll"
    "Cognex.VisionPro.dll"
    "Cognex.VisionPro.ImageFile.dll"
    "Cognex.VisionPro.Interop.Core.dll"
    
    "Cognex.VisionPro3D.Controls.dll"
    "Cognex.VisionPro3D.Core.dll"
    "Cognex.VisionPro3D.Display.Controls.dll"
    "Cognex.VisionPro3D.dll"
    "Cognex.VisionPro3D.Graphic.dll"
)


add_executable(RVC_Example_QuickCapture_X2
    QuickCapture_X2.cs
)
set_property(TARGET RVC_Example_QuickCapture_X2 PROPERTY VS_DOTNET_TARGET_FRAMEWORK_VERSION "v4.7.2")
set_property(TARGET RVC_Example_QuickCapture_X2 PROPERTY WIN64_EXECUTABLE TRUE)
set(CMAKE_CSharp_FLAGS "${CMAKE_CXX_FLAGS} /langversion:latest /platform:x64")
target_link_libraries(RVC_Example_QuickCapture_X2 RVC_CSharp RVC_CSharp_Extension)
set_property(TARGET RVC_Example_QuickCapture_X2 PROPERTY VS_DOTNET_REFERENCES
    "Microsoft.CSharp"
    "System"
    "System.Linq"
    "System.Threading.Tasks"
    "System.Windows.Forms"
    "System.Runtime.InteropServices"
    "System.IO"
    "System.Drawing"
    
    "Cognex.VisionPro.Core.dll"
    "Cognex.VisionPro.CorePlus.dll"
    "Cognex.VisionPro.dll"
    "Cognex.VisionPro.ImageFile.dll"
    "Cognex.VisionPro.Interop.Core.dll"
    
    "Cognex.VisionPro3D.Controls.dll"
    "Cognex.VisionPro3D.Core.dll"
    "Cognex.VisionPro3D.Display.Controls.dll"
    "Cognex.VisionPro3D.dll"
    "Cognex.VisionPro3D.Graphic.dll"
)
