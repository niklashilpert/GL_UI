//
// Created by niklas on 12.07.25.
//

#include "UniformBufferObject.h"

#include <glad/glad.h>
#include <glm/vec2.hpp>
#include <glm/gtc/type_ptr.inl>

unsigned int gl::createUBO(const unsigned int size, const unsigned int binding) {
    unsigned int UBO;
    glGenBuffers(1, &UBO);
    glBindBuffer(GL_UNIFORM_BUFFER, UBO);
    glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    glBindBufferBase(GL_UNIFORM_BUFFER, binding, UBO);
    // alt: glBindBufferRange

    return UBO;
}

gl::ScreenSizeUBO::ScreenSizeUBO(): UBO(createUBO(sizeof(glm::vec2), 0)) {}

gl::ScreenSizeUBO::~ScreenSizeUBO() {
    glDeleteBuffers(1, &UBO);
}

void gl::ScreenSizeUBO::setSize(const int width, const int height) const {
    auto viewportSize = glm::vec2(width, height);
    glBindBuffer(GL_UNIFORM_BUFFER, UBO);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::vec2), glm::value_ptr(viewportSize));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}



