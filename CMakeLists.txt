cmake_minimum_required(VERSION 3.6)

project(april-engine)

set(CMAKE_CXX_STANDARD 14)

# set default minimum deployment target
if(XCODE)
    if(NOT DEFINED CMAKE_XCODE_ATTRIBUTE_IPHONEOS_DEPLOYMENT_TARGET)
        SET (CMAKE_XCODE_ATTRIBUTE_IPHONEOS_DEPLOYMENT_TARGET 8.0)
    endif()
endif()


# april root path
set(APRIL_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_MODULE_PATH ${APRIL_ROOT_PATH}/cmake/Modules/)

include(AprilBuildSet)

#添加子目录
add_subdirectory(${APRIL_ROOT_PATH}/april ${ENGINE_BINARY_PATH}/april/core)

