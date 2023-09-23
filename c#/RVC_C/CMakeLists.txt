cmake_minimum_required(VERSION 3.8)

project(RVC_C C CXX)

if(WIN32)
  set(RVC_SDK_DIR "Path/To/SDK/")
  set(RVC_INCLUDE_DIRS "${RVC_SDK_DIR}/include")
  set(RVC_LIB_DIR "${RVC_SDK_DIR}/lib")
  file(GLOB RVC_LIBS "${RVC_LIB_DIR}/*.lib" ABSOLUTE)
else(WIN32)
  message(FATAL_ERROR "RVC C# Interfaces currently only support Windows platform")
endif(WIN32)

add_library(RVC_C SHARED ${CMAKE_CURRENT_SOURCE_DIR}/RVC_C.cpp ${CMAKE_CURRENT_SOURCE_DIR}/RVC_C.h)
target_link_libraries(RVC_C PRIVATE ${RVC_LIBS})
target_include_directories(RVC_C PRIVATE ${RVC_INCLUDE_DIRS})
