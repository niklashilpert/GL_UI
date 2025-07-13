//
// Created by niklas on 10.07.25.
//

#ifndef RENDERCALL_H
#define RENDERCALL_H

#include <glad/glad.h>

#include "Shader.h"

namespace gl {
    struct ShaderVariable {
        int size;
        int type;
    };
    struct Line {
        glm::vec3 startPosition;
        glm::vec3 endPosition;
        glm::vec4 color;
        float thickness;
    };
    struct Circle {
        glm::vec3 position;
        glm::vec4 color;
        float outerRadius;
        float innerRadius;
        glm::vec2 angleBounds;
    };
    struct Rectangle {
        glm::vec2 corner1; // TOP LEFT
        glm::vec2 corner2; // TOP RIGHT
        float z;
    };

    /**
     * This class encompasses everything that is required to draw objects to the canvas.
     */
    class DrawCall {
    public:
        DrawCall(int dataSize, unsigned int VBO, unsigned int VAO, const Shader *shader, const int drawMode);
        explicit DrawCall(const DrawCall *drawCall);
        ~DrawCall();
        void bind() const;
        static void unbind();
        void draw() const;
        void setOffset(const glm::vec3 &offset);
    protected:
        int dataSize;
        unsigned int VBO;
        unsigned int VAO;
        const Shader *shader;
        int drawMode;
        glm::vec3 offset;
    private:
        const DrawCall *parent;
    };

    class MandelbrotDrawCall : public DrawCall {
    public:
        explicit MandelbrotDrawCall(const std::vector<Rectangle> &rectangles, glm::vec2 center, float zoom, int iterationCount);
        void bind() const;
    private:
        glm::vec2 center;
        float zoom;
        int iterationCount;
    };

    unsigned int createVBO(const std::vector<float> &data);
    unsigned int createVAO(const std::vector<ShaderVariable> &vars);

    DrawCall *createLineDrawCall(const std::vector<Line> &lines);
    DrawCall *createCircleDrawCall(const std::vector<Circle> &circles);
    DrawCall *createMandelbrotDrawCall(const std::vector<Rectangle> &rectangles);
}

#endif //RENDERCALL_H
