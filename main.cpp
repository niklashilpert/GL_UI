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

    std::vector lines = {
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
        50
        ),
        gl::Circle(
        glm::vec3(1300, 100, 0),
        glm::vec4(1, .5, 1, 1),
        50
        ),
        gl::Circle(
            glm::vec3(700, 700, 0),
        glm::vec4(1, 1, 1, 1),
        100
        )
    };

    for (int i = 0; i < 100; i++) {
        lines.push_back(gl::Line(
            glm::vec3(
                700 + sinf(M_PI * 2.0f * i / 100) * 300,
                700 + cosf(M_PI * 2.0f * i / 100) * 300,
                0
                ),
            glm::vec3(
                700 + sinf(M_PI * 2.0f * (i+1) / 100) * 300,
                700 + cosf(M_PI * 2.0f * (i+1) / 100) * 300,
                0
                ),
            glm::vec4(1, 1, 1, 1),
            100.0f
        ));

        circles.push_back(gl::Circle(
        glm::vec3(
            700 + sinf(2.0f * M_PI * i / 100) * 300,
            700 + cosf(2.0f * M_PI * i / 100) * 300,
            0),
            glm::vec4(1, 1, 1, 1),
            50
        ));
    }

    const auto *lineCall   = gl::createLineDrawCall(lines);
    const auto *circleCall = gl::createCircleDrawCall(circles);



    while (!window.should_close()) {

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        viewportSizeUBO.setSize(window.getWidth(), window.getHeight());

        lineCall->draw();
        circleCall->draw();

        const double startTime = glfwGetTime();

        window.updateBuffers();
        Window::updateEvents();

        const double endTime = glfwGetTime();
        //std::cout << round((endTime - startTime) * 1000000) / 1000 << " ms" << std::endl;

    }

    delete circleCall;
    delete lineCall;
    gl::deinitShaders();
}
