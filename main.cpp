#define STB_IMAGE_IMPLEMENTATION

#include <cmath>
#include <iostream>
#include <string>
#include <unistd.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "io/stb_image.h"

#include <thread>

#include "gl/DrawCall.h"
#include "gl/UniformBufferObject.h"
#include "window/Window.h"


int main() {
    const Window window(800, 800, "OpenGL - Test");

    gl::initShaders();
    const auto viewportSizeUBO = gl::ScreenSizeUBO();

    /*std::vector lines = {
        gl::Line(
            glm::vec3(100, 100, 0),
            glm::vec3(1300, 100, 0),
            glm::vec4(1, .5, 1, 1),
            100
        )
    };

    std::vector circles = {
        gl::Circle(
        glm::vec3(100, 100, 0),
        glm::vec4(1, .5, 1, 1),
        50,
        0,
        glm::vec2(0, 1)
        ),
        gl::Circle(
        glm::vec3(1300, 100, 0),
        glm::vec4(1, .5, 1, 1),
        50,
        0,
        glm::vec2(0, 1)
        ),
        gl::Circle(
            glm::vec3(700, 700, 0),
        glm::vec4(1, 1, 1, 1),
        300,
        250,
        glm::vec2(0, 1)
        )
    };*/

    std::vector mandelbrot = {
        gl::Rectangle(
            glm::vec3(0, 0, 0),
            glm::vec3(1400, 1400, 0))
    };

    //const auto *lineCall   = gl::createLineDrawCall(lines);
    //const auto *circleCall = gl::createCircleDrawCall(circles);
    const auto *mandelbrotCall = new gl::MandelbrotDrawCall(mandelbrot, glm::vec2(-.5, 0), 1, 50);


    while (!window.should_close()) {

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        viewportSizeUBO.setSize(window.getWidth(), window.getHeight());

        //lineCall->draw();
        //circleCall->draw();
        mandelbrotCall->bind();
        mandelbrotCall->draw();

        window.updateBuffers();
        Window::updateEvents();
    }

    //delete circleCall;
    //delete lineCall;
    delete mandelbrotCall;
    gl::deinitShaders();
}
