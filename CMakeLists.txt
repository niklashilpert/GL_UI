cmake_minimum_required(VERSION 3.30)
project(GL_UI)

set(CMAKE_CXX_STANDARD 20)

set(OpenGlLinkers -lGL -lglfw)

file (COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/resources/)


add_executable(GL_UI
        main.cpp
        glad/glad.c
        io/stb_image.h
        io/io.cpp
        io/io.h
        window/Window.cpp
        window/Window.h
        gl/Shader.cpp
        gl/Shader.h
        gl/Texture.h
        gl/Texture.cpp
        gl/TextureInstance.cpp
        gl/TextureInstance.h
        gl/DrawCall.cpp
        gl/DrawCall.h
        io/stb_image.h
        io/stb_image_write.h

)

target_link_libraries(GL_UI ${OpenGlLinkers})

