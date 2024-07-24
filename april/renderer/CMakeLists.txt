set(APRIL_RENDERER_HEADER
    #renderer/Renderer.h
    #renderer/RenderCommand.h
    #renderer/TrianglesCommand.h
    #renderer/CustomCommand.h
    
    #renderer/Texture2D.h
    #renderer/TextureAtlas.h 
    #renderer/TextureUtils.h

    #backend
    renderer/backend/Backend.h
    renderer/backend/Buffer.h
    renderer/backend/CommandBuffer.h
    renderer/backend/DepthStencilState.h
    renderer/backend/Device.h
    renderer/backend/Program.h
    renderer/backend/ProgramCache.h
    renderer/backend/Macros.h
    renderer/backend/RenderPassDescriptor.h
    renderer/backend/RenderPipeline.h
    renderer/backend/RenderPipelineDescriptor.h
    renderer/backend/ShaderModule.h
    renderer/backend/Texture.h
    renderer/backend/Types.h
    renderer/backend/VertexLayout.h
    renderer/backend/ProgramState.h
    renderer/backend/ShaderCache.h
    renderer/backend/DeviceInfo.h

    renderer/aprilShaders.h
    )

set(APRIL_RENDERER_SRC
    #renderer/Renderer.cpp
    #renderer/RenderCommand.cpp
    #renderer/TrianglesCommand.cpp
    #renderer/CustomCommand.cpp
   
    #renderer/Texture2D.cpp
    #renderer/TextureAtlas.cpp 
    #renderer/TextureUtils.cpp
   
    #backend
    renderer/backend/CommandBuffer.cpp
    renderer/backend/DepthStencilState.cpp
    renderer/backend/Device.cpp
    renderer/backend/ShaderModule.cpp
    renderer/backend/Texture.cpp
    renderer/backend/Types.cpp
    renderer/backend/VertexLayout.cpp
    renderer/backend/ProgramCache.cpp
    renderer/backend/Program.cpp
    renderer/backend/ProgramState.cpp
    renderer/backend/ShaderCache.cpp
    renderer/backend/RenderPassDescriptor.cpp

    renderer/aprilShaders.cpp
)


#if(ANDROID OR WINDOWS OR LINUX OR Mac)  

list(APPEND APRIL_RENDERER_HEADER
    renderer/backend/opengl/BufferGL.h
    renderer/backend/opengl/CommandBufferGL.h
    renderer/backend/opengl/DepthStencilStateGL.h
    renderer/backend/opengl/DeviceGL.h
    renderer/backend/opengl/ProgramGL.h
    renderer/backend/opengl/RenderPipelineGL.h
    renderer/backend/opengl/ShaderModuleGL.h
    renderer/backend/opengl/TextureGL.h
    renderer/backend/opengl/UtilsGL.h
    renderer/backend/opengl/DeviceInfoGL.h
)

list(APPEND APRIL_RENDERER_SRC
    renderer/backend/opengl/BufferGL.cpp
    renderer/backend/opengl/CommandBufferGL.cpp
    renderer/backend/opengl/DepthStencilStateGL.cpp
    renderer/backend/opengl/DeviceGL.cpp
    renderer/backend/opengl/ProgramGL.cpp
    renderer/backend/opengl/RenderPipelineGL.cpp
    renderer/backend/opengl/ShaderModuleGL.cpp
    renderer/backend/opengl/TextureGL.cpp
    renderer/backend/opengl/UtilsGL.cpp
    renderer/backend/opengl/DeviceInfoGL.cpp
)
#endif()

