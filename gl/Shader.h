//
// Created by niklas on 31.01.25.
//

#ifndef SHADER_H
#define SHADER_H
#include <string>
#include <vector>
#include <glm/glm.hpp>

namespace gl {
    const std::string TEXTURE_VERTEX_SHADER_FILE = "resources/shaders/texture/default_texture.vert";
    const std::string TEXTURE_FRAGMENT_SHADER_FILE = "resources/shaders/texture/default_texture.frag";

    const std::string LINE_VERTEX_SHADER_FILE = "resources/shaders/line/shader.vert";
    const std::string LINE_GEOMETRY_SHADER_FILE = "resources/shaders/line/shader.geom";
    const std::string LINE_FRAGMENT_SHADER_FILE = "resources/shaders/line/shader.frag";

    const std::string CIRCLE_VERTEX_SHADER_FILE = "resources/shaders/circle/shader.vert";
    const std::string CIRCLE_GEOMETRY_SHADER_FILE = "resources/shaders/circle/shader.geom";
    const std::string CIRCLE_FRAGMENT_SHADER_FILE = "resources/shaders/circle/shader.frag";

    const std::string MANDELBROT_VERTEX_SHADER_FILE = "resources/shaders/mandelbrot/shader.vert";
    const std::string MANDELBROT_FRAGMENT_SHADER_FILE = "resources/shaders/mandelbrot/shader.frag";

    class Shader {
    public:
        explicit Shader(const std::vector<std::string> &paths);
        ~Shader();
        void bind() const;

        void setFloat2(const std::string& name, float value1, float value2) const;
        void setFloat3(const std::string& name, float value1, float value2, float value3) const;
        void setBool(const std::string& name, bool value) const;
        void setInt(const std::string& name, int value) const;
        void setFloat(const std::string& name, float value) const;
        void setMat4(const std::string& name, const glm::mat4& value) const;
    private:
        unsigned int id;

    };

    void initShaders();
    void deinitShaders();

    inline const Shader *TEXtURE_SHADER;
    inline const Shader *LINE_SHADER;
    inline const Shader *CIRCLE_SHADER;
    inline const Shader *MANDELBROT_SHADER;

}


#endif //SHADER_H
