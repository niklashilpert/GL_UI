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
        float radius;
    };

    /**
     * This class encompasses everything that is required to draw objects to the canvas.
     */
    class DrawCall {
    public:
        DrawCall(int dataSize, unsigned int VBO, unsigned int VAO, const Shader *shader, const int drawMode);
        ~DrawCall();
        void draw() const;
        int dataSize;
        unsigned int VBO;
        unsigned int VAO;
        const Shader *shader;
        int drawMode;

    private:

    };

    unsigned int createVBO(const std::vector<float> &data);
    unsigned int createVAO(const std::vector<ShaderVariable> &vars);

    DrawCall *createLineDrawCall(std::vector<Line> &lines);
    DrawCall *createCircleDrawCall(std::vector<Circle> &circles);
}

#endif //RENDERCALL_H
