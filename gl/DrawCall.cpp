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
    drawMode(drawMode),
    offset(glm::vec3(0, 0, 0)),
    parent(nullptr) {}

gl::DrawCall::DrawCall(const DrawCall *drawCall):
    dataSize(drawCall->dataSize),
    VBO(drawCall->VBO),
    VAO(drawCall->VAO),
    shader(drawCall->shader),
    drawMode(drawCall->drawMode),
    offset(glm::vec3(0, 0, 0)),
    parent(drawCall) {}


gl::DrawCall::~DrawCall() {
    if (parent) {
        delete parent;
        parent = nullptr;
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void gl::DrawCall::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBindVertexArray(this->VAO);
    shader->bind();
    shader->setFloat3("uOffset", offset.x, offset.y, offset.z);
}

void gl::DrawCall::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glUseProgram(0);
}


void gl::DrawCall::draw() const {
    bind();
    glDrawArrays(this->drawMode, 0, this->dataSize);
    unbind();
}


gl::MandelbrotDrawCall::MandelbrotDrawCall(const std::vector<Rectangle> &rectangles, glm::vec2 center, float zoom, int iterationCount):
    DrawCall(createMandelbrotDrawCall(rectangles)), center(center), zoom(zoom), iterationCount(iterationCount) {}

void gl::MandelbrotDrawCall::bind() const {
    DrawCall::bind();
    shader->setFloat2("uCenter", this->center.x, this->center.y);
    shader->setFloat("uZoom", this->zoom);
    shader->setInt("uIterationCount", this->iterationCount);
}



unsigned int gl::createVBO(const std::vector<float> &data) {
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(data.size() * sizeof(float)), data.data(), GL_STATIC_DRAW);
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

gl::DrawCall *gl::createLineDrawCall(const std::vector<Line> &lines) {
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

gl::DrawCall *gl::createCircleDrawCall(const std::vector<Circle> &circles) {
    std::vector<float> data;
    for (auto [position, color, outerRadius, innerRadius, angleBounds] : circles) {
        data.push_back(position.x);
        data.push_back(position.y);
        data.push_back(position.z);
        data.push_back(color.r);
        data.push_back(color.g);
        data.push_back(color.b);
        data.push_back(color.a);
        data.push_back(outerRadius);
        data.push_back(innerRadius);
        data.push_back(angleBounds.x);
        data.push_back(angleBounds.y);
    }

    const int size = static_cast<int>(data.size());
    const unsigned int VBO = createVBO(data);
    const unsigned int VAO = createVAO({
        ShaderVariable(3, GL_FLOAT), // Position
        ShaderVariable(4, GL_FLOAT), // Color
        ShaderVariable(1, GL_FLOAT), // Outer Radius
        ShaderVariable(1, GL_FLOAT), // Inner Radius
        ShaderVariable(2, GL_FLOAT), // Angle Bounds

   });
    const Shader *shader = CIRCLE_SHADER;

    return new DrawCall(size, VBO, VAO, shader, GL_POINTS);
}

gl::DrawCall *gl::createMandelbrotDrawCall(const std::vector<Rectangle> &rectangles) {
    std::vector<float> data;
    for (auto [corner1, corner2, z] : rectangles) {
        float topLeft_x = corner1.x < corner2.x ? corner1.x : corner2.x;
        float topLeft_y = corner1.y < corner2.y ? corner1.y : corner2.y;
        float bottomRight_x = corner1.x > corner2.x ? corner1.x : corner2.x;
        float bottomRight_y = corner1.y > corner2.y ? corner1.y : corner2.y;

        data.push_back(topLeft_x);
        data.push_back(topLeft_y);
        data.push_back(z);

        data.push_back(topLeft_x);
        data.push_back(bottomRight_y);
        data.push_back(z);

        data.push_back(bottomRight_x);
        data.push_back(bottomRight_y);
        data.push_back(z);

        data.push_back(topLeft_x);
        data.push_back(topLeft_y);
        data.push_back(z);

        data.push_back(bottomRight_x);
        data.push_back(bottomRight_y);
        data.push_back(z);

        data.push_back(bottomRight_x);
        data.push_back(topLeft_y);
        data.push_back(z);
    }

    const int size = static_cast<int>(data.size());
    const unsigned int VBO = createVBO(data);
    const unsigned int VAO = createVAO({
        ShaderVariable(3, GL_FLOAT), // Position
   });
    const Shader *shader = MANDELBROT_SHADER;

    return new DrawCall(size, VBO, VAO, shader, GL_TRIANGLES);
}
