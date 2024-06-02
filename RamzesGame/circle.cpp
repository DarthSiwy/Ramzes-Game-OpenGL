#include "shader_s.h"
#include "circle.h"

#include <map>
#include <cmath>
#include <string>
#include <vector>
#include <random>
#include <iostream>

Circle::Circle(float radius) : radius(radius) {
    int numSegments = 100;
    vertices.push_back(0.0f); // x
    vertices.push_back(0.0f); // y
    vertices.push_back(0.0f); // z
    // CENTER
    vertices.push_back(0.0f); // r
    vertices.push_back(0.0f); // g
    vertices.push_back(0.0f); // b

    for (int i = 0; i <= numSegments; ++i) {
        float theta = 2.0f * 3.1415926f * i / numSegments;
        float x = radius * cos(theta);
        float z = radius * sin(theta);
        vertices.push_back(x);
        vertices.push_back(0.0f);
        vertices.push_back(z);
        vertices.push_back(0.0f); // r
        vertices.push_back(0.0f); // g
        vertices.push_back(0.0f); // b
    }

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Circle::render(const Shader& shader, const glm::mat4& view, const glm::mat4& projection) {
    shader.use();
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size() / 6);  // Adjusted to 6 floats per vertex
}

void Circle::move(float posX, float posY, float posZ) {
    for (int i = 0; i < vertices.size(); i += 6) {
        vertices[i] += posX;       // x
        vertices[i + 1] += posY;   // y
        vertices[i + 2] += posZ;   // z
    }

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(float), vertices.data());
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Circle::change_color(float r, float g, float b) {
    for (int i = 0; i < vertices.size(); i += 6) {
        vertices[i + 3] = r;  // r
        vertices[i + 4] = g;  // g
        vertices[i + 5] = b;  // b
    }

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(float), vertices.data());
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Circle::~Circle() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}
