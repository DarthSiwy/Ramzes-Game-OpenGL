#include "shader_s.h"
#include "pyramid.h"

Pyramid::Pyramid() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);  
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
}

void Pyramid::render(const Shader& shader, const glm::mat4& view, const glm::mat4& projection) const {
    shader.use();
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBindVertexArray(VAO);

    glDrawArrays(GL_TRIANGLES, 0, 36);
    //glBindVertexArray(0);
}

void Pyramid::move_pyramid(float pos_x, float pos_y, float pos_z) {
    for (int j = 0; j < 144; j += 8) {
        vertices[j + 0] += pos_x;
        vertices[j + 1] += pos_y;
        vertices[j + 2] += pos_z;
    }
}

Pyramid::~Pyramid() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}


