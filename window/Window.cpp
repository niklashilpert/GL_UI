//
// Created by niklas on 30.01.25.
//

#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <glad/glad.h>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <utility>
#include <vector>
#include <GLFW/glfw3.h>

#include "Window.h"
#include "../io/stb_image_write.h"


/* ###### STATIC ###### */

int Window::instance_count = 0;

void Window::updateEvents() {
    glfwPollEvents();
}

void Window::eventThreadLoop() const {
    while (this->keepEventThreadRunning) {
        glfwPollEvents();
    }
}

/* ###### MEMBERS ###### */

Window::Window(
    const int width,
    const int height,
    const std::string &title
): title(title),
    width(width),
    height(height) {
    if (instance_count == 0) {
        if (!glfwInit()) {
            throw std::runtime_error("Failed to initialize GLFW3");
        }
    }

    instance_count++;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(1, 1, title.c_str(), nullptr, nullptr);
    if (!window) {
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwSetErrorCallback(errorCallback);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow *window, const int w, const int h) {
        if (auto *window_pointer = static_cast<Window*>(glfwGetWindowUserPointer(window))) {
            window_pointer->framebufferSizeCallback(window, w, h);
        }
    });
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        throw std::runtime_error("Failed to initialize GLAD");
    }

    glfwSetWindowSize(window, width, height);

    //this->eventThread = std::thread(&Window::eventThreadLoop, this);

}

Window::~Window() {
    close();
    glfwDestroyWindow(window);

    keepEventThreadRunning = false;

    instance_count--;
    if (instance_count == 0) {
        glfwTerminate();
    }
}


void Window::close() const {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}


bool Window::should_close() const {
    return glfwWindowShouldClose(window);
}

bool Window::is_key_pressed(const int key) const {
    return glfwGetKey(window, key) != GLFW_RELEASE;
}

void Window::updateBuffers() const {
    glfwSwapBuffers(window);
}


void Window::setWidth(const int width) {
    this->width = width;
}
void Window::setHeight(const int height) {
    this->height = height;
}
void Window::setTitle(const std::string &title) {
    this->title = title;
}
int Window::getWidth() const {
    return this->width;
}
int Window::getHeight() const {
    return this->height;
}
float Window::getAspectRatio() const {
    return static_cast<float>(width) / static_cast<float>(height);
}

void Window::writeToFile(const std::string &filename) const {
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    constexpr GLsizei nrChannels = 3;
    GLsizei stride = nrChannels * width;
    stride += (stride % 4) ? (4 - stride % 4) : 0;
    const GLsizei bufferSize = stride * height;
    std::vector<char> buffer(bufferSize);
    glPixelStorei(GL_PACK_ALIGNMENT, 4);
    glReadBuffer(GL_FRONT);
    glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, buffer.data());
    stbi_flip_vertically_on_write(true);
    stbi_write_png(filename.c_str(), width, height, nrChannels, buffer.data(), stride);
}

std::string Window::getTitle() const {
    return this->title;
}



void Window::errorCallback(int error, const char *description) {
    throw std::runtime_error("GLFW error: " + std::string(description));
}

void Window::framebufferSizeCallback(GLFWwindow *window, const int width, const int height) {
    glViewport(0, 0, width, height);
    this->width = width;
    this->height = height;
    std::cout << "Framebuffer size: " << width << " x " << height << std::endl;
}


void Window::keyCallback(GLFWwindow *window, const int key, int scancode, const int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    } else if (key == GLFW_KEY_P && action == GLFW_PRESS) {
        const auto *w = static_cast<Window *>(glfwGetWindowUserPointer(window));
        w->writeToFile("/home/niklas/Desktop/Test.bmp");
    }
}

