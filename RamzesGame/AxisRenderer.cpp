#include "shader_s.h"
#include "AxisRenderer.h"

AxisRenderer::AxisRenderer() {
    // Vertices for the axis lines
    float axisVertices[] = {
        // Positions            // Colors
         0.0f,  0.0f,  0.0f,    1.0f,  0.0f,  0.0f, // X-axis
         1.0f,  0.0f,  0.0f,    1.0f,  0.0f,  0.0f,

         0.0f,  0.0f,  0.0f,    0.0f,  1.0f,  0.0f, // Y-axis
         0.0f,  1.0f,  0.0f,    0.0f,  1.0f,  0.0f,

         0.0f,  0.0f,  0.0f,    0.0f,  0.0f,  1.0f, // Z-axis
         0.0f,  0.0f,  1.0f,    0.0f,  0.0f,  1.0f
    };

    // Generate VAO and VBO
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    // Bind VAO and VBO
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Fill buffer with vertex data
    glBufferData(GL_ARRAY_BUFFER, sizeof(axisVertices), axisVertices, GL_STATIC_DRAW);

    // Set vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // Unbind VAO
    glBindVertexArray(0);
}

void AxisRenderer::render(const Shader& shader, const glm::mat4& view, const glm::mat4& projection) const {

    shader.use();
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);

    glBindVertexArray(vao);
    glDrawArrays(GL_LINES, 0, 6);
    glBindVertexArray(0);
}

AxisRenderer::~AxisRenderer() {
    // Cleanup
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}
