#include "shader_s.h"
#include "border.h"

Border::Border() {  
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(border_vertices), border_vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void Border::render(const Shader& shader, const glm::mat4& view, const glm::mat4& projection) const {
    shader.use();
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(border_vertices), border_vertices);
    glBindVertexArray(vao);

    glDrawArrays(GL_LINES, 0, 8);
    //glBindVertexArray(0);
}

Border::~Border() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}
