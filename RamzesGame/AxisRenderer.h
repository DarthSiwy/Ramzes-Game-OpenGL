#ifndef AXIS_RENDERER_H
#define AXIS_RENDERER_H

#include <glad/glad.h>
#include "shader_s.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class AxisRenderer {
public:
    AxisRenderer();
    void render(const Shader& shader, const glm::mat4& view, const glm::mat4& projection) const;
    ~AxisRenderer();

private:
    unsigned int vao, vbo;
};

#endif