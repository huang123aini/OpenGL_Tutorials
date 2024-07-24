set(APRIL_VERSION 1.0)

set(APRIL_CORE_LIB april)
project(april3d_libs)

include(base/CMakeLists.txt)
include(platform/CMakeLists.txt)
include(math/CMakeLists.txt)
include(renderer/CMakeLists.txt)



set(APRIL_HEADER
    ${APRIL_BASE_HEADER}
    ${APRIL_PLATFORM_HEADER}
    ${APRIL_MATH_HEADER}
    ${APRIL_RENDERER_HEADER}
)

set(APRIL_SRC 
    ${APRIL_PLATFORM_SRC}
    ${APRIL_RENDERER_SRC}
    ${APRIL_MATH_SRC}
    ${APRIL_BASE_SRC}
)

list(APPEND APRIL_SRC ${APRIL_HEADER})


################临时的环境配置方案#############################
# 包含头文件
set(GLFW_H /usr/local/Cellar/glfw/3.4/include)
set(GLEW_H /usr/local/Cellar/glew/2.2.0_1/include)
set(GLM_H /Users/huangshiping/Documents/GitHub/OpenGL_Tutorials/third-party/glm)

include_directories(${GLFW_H} ${GLEW_H} ${GLM_H})
#添加链接
set(GLFW_LINK /usr/local/Cellar/glfw/3.4/lib/libglfw.3.4.dylib)
set(GLEW_LINK /usr/local/Cellar/glew/2.2.0_1/lib/libGLEW.2.2.0.dylib)
link_libraries(${GLFW_LINK} ${GLEW_LINK})
###############################################


add_library(april3d ${APRIL_SRC})



target_include_directories(april3d
    PUBLIC ${APRIL_ROOT_PATH}
    PUBLIC ${APRIL_ROOT_PATH}/april
    #PUBLIC ${APRIL_ROOT_PATH}/extensions
    PUBLIC ${APRIL_ROOT_PATH}/april/platform
    #PUBLIC ${COCOS2DX_ROOT_PATH}/cocos/editor-support
    INTERFACE ${COCOS2DX_ROOT_PATH}/april/base
    #INTERFACE ${COCOS2DX_ROOT_PATH}/cocos/audio/include
    #INTERFACE ${COCOS2DX_ROOT_PATH}/cocos/platform/${PLATFORM_FOLDER}
)