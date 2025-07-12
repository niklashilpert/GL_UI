//
// Created by niklas on 10.07.25.
//

#include "DrawCall.h"

#include <iostream>

#include "../io/stb_image.h"

gl::DrawCall::DrawCall(const int dataSize, const unsigned int VBO, const unsigned int VAO, const Shader *shader, const int drawMode):
    dataSize(dataSize),
    VBO(VBO),
    VAO(VAO),
    shader(shader),
    drawMode(drawMode){}

gl::DrawCall::~DrawCall() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}


void gl::DrawCall::draw() const {
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBindVertexArray(this->VAO);
    shader->bind();
    glDrawArrays(this->drawMode, 0, this->dataSize);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glUseProgram(0);
}


unsigned int gl::createVBO(const std::vector<float> &data) {
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(data.size() * sizeof(float)), data.data(), GL_STATIC_DRAW);
    std::cout << "Created VBO with size " << data.size() * sizeof(float) << std::endl;
    return VBO;
}

unsigned int gl::createVAO(const std::vector<ShaderVariable> &vars) {
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned long vertexElementSize = 0;
    for (auto [size, _] : vars) {
        vertexElementSize += size;
    }

    unsigned int currentByte = 0;
    for (int i = 0; i < vars.size(); i++) {
        glVertexAttribPointer(
            i,
            vars[i].size,
            vars[i].type,
            GL_FALSE,
            static_cast<GLsizei>(vertexElementSize * sizeof(float)),
            reinterpret_cast<void *>(currentByte * sizeof(float))
        );
        glEnableVertexAttribArray(i);

        currentByte += vars[i].size;
    }

    return VAO;
}

gl::DrawCall *gl::createLineDrawCall(std::vector<Line> &lines) {
    std::vector<float> data;
    for (auto [startPosition, endPosition, color, thickness] : lines) {
        data.push_back(startPosition.x);
        data.push_back(startPosition.y);
        data.push_back(startPosition.z);
        data.push_back(endPosition.x);
        data.push_back(endPosition.y);
        data.push_back(endPosition.z);
        data.push_back(color.x);
        data.push_back(color.y);
        data.push_back(color.z);
        data.push_back(color.w);
        data.push_back(thickness);
    }

    const int size = static_cast<int>(data.size());
    const unsigned int VBO = createVBO(data);
    const unsigned int VAO = createVAO({
       ShaderVariable(3, GL_FLOAT), // Position 1
       ShaderVariable(3, GL_FLOAT), // Position 2
       ShaderVariable(4, GL_FLOAT), // Color
       ShaderVariable(1, GL_FLOAT), // Width
   });
    const Shader *shader = LINE_SHADER;

    return new DrawCall(size, VBO, VAO, shader, GL_POINTS);
}

gl::DrawCall *gl::createCircleDrawCall(std::vector<Circle> &circles) {
    std::vector<float> data;
    for (auto [position, color, radius] : circles) {
        data.push_back(position.x);
        data.push_back(position.y);
        data.push_back(position.z);
        data.push_back(color.r);
        data.push_back(color.g);
        data.push_back(color.b);
        data.push_back(color.a);
        data.push_back(radius);
    }

    const int size = static_cast<int>(data.size());
    const unsigned int VBO = createVBO(data);
    const unsigned int VAO = createVAO({
       ShaderVariable(3, GL_FLOAT), // Position
       ShaderVariable(4, GL_FLOAT), // Color
       ShaderVariable(1, GL_FLOAT), // Radius
   });
    const Shader *shader = CIRCLE_SHADER;

    return new DrawCall(size, VBO, VAO, shader, GL_POINTS);
}
