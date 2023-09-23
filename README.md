# RVC bindings and examples 

This repository contains source codes used for creating python, C# bindgins and example codes of using RVC in C++, Python, C#, etc. 

RVC SDK is a C++ API for RVC 3D cameras. The SDK is supported on Windows 9,10,11, Debian 9+ and Ubuntu 18.04+. 

When creating bindings or running the examples, we assume you have RVC SDK installed properly. You can download it from our website: https://rvbust.com/download.html

The directories: 
  - c++/: contains the example codes using RVC C++ SDK. 
  - python/: 
    - PyRVC/: Used to generate python bindings based on Pybind 
    - Others are examples using Python API  
  - c#/: 
    - RVC_C/: First export an C DLL based on the C++ API, which will be used in C# by using DllImport, checkout RVC_CSharp.cs 
    - Others are some examples or entension to use with OpenCV, Halcon, VisionPro etc.  

We are planning to release more sources codes from RVC projects. Now we are in a fast fixing and improving process, please don't hesitate to give us feedbacks with issues. 
