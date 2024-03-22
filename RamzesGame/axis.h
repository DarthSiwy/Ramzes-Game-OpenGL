#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class AxisRenderer {
public:
    AxisRenderer();
    void render();
    ~AxisRenderer();

private:
    unsigned int axisVAO, axisVBO;

    Shader mainShader("shader_vertex", "shader_fragment");

    float axisVertices[36] = {
        0.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,   // X-axis
        5.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,

        0.0f, 0.0f, 0.0f,   0.0f, 1.0f, 0.0f,   // Y-axis
        0.0f, 5.0f, 0.0f,   0.0f, 1.0f, 0.0f,

        0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 1.0f,   // Z-axis
        0.0f, 0.0f, 5.0f,   0.0f, 0.0f, 1.0f
    };
};