cmake_minimum_required(VERSION 3.5)

project(OpenGL_First)

set(CMAKE_CXX_STANDARD 14)


# brew install glfw/glew 安装glfw&glew三方库 并引入头文件

# 包含头文件
set(GLFW_H /usr/local/Cellar/glfw/3.4/include)
set(GLEW_H /usr/local/Cellar/glew/2.2.0_1/include)
include_directories(${GLFW_H} ${GLEW_H})

#添加链接
set(GLFW_LINK /usr/local/Cellar/glfw/3.4/lib/libglfw.3.4.dylib)
set(GLEW_LINK /usr/local/Cellar/glew/2.2.0_1/lib/libGLEW.2.2.0.dylib)
link_libraries(${GLFW_LINK} ${GLEW_LINK})


# 添加可执行代码
add_executable(OpenGL_First main.cpp)

# 链接系统的 OpenGL 框架
if (APPLE)
    target_link_libraries(OpenGL_First "-framework OpenGL")
endif()