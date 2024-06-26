#include "shader_s.h"
#include "pyramid.h"

#include <map>
#include <cmath>
#include <string>
#include <vector>
#include <random>
#include <iostream>

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

void Pyramid::render(const Shader& shader, const glm::mat4& view, const glm::mat4& projection,  glm::mat4& model, int& animation) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    shader.use();
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);
    
    model = glm::mat4(1.0f);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBindVertexArray(VAO);

    // ANIMATION
    if (isTransitioning == 1) {
        translation_animation = translation_direction * transitionProgress;
        model = glm::translate(model, translation_animation);
    }

    // UPDATE TRANSITION PROGRESS
    if (isTransitioning == 1) {
        transitionProgress += 0.01f * transition_speed;
        // END OF TRANSITION
        if (transitionProgress >= 1.0f) {
            transitionProgress = 0.0f;
            move_pyramid();
            translation_animation = glm::vec3(0.0f, 0.0f, 0.0f);
            translation_direction = glm::vec3(0.0f, 0.0f, 0.0f);
            isTransitioning = 0;
            direction == 0;
            animation = 0;
        }
    }

    glm::vec4 color(1.0f, 1.0f, 1.0f, 0.5f); // White color with 50% transparency
    shader.setVec4("color", color);

    shader.setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    glDisable(GL_BLEND);
}

void Pyramid::move(float pos_x, float pos_y, float pos_z) {
    for (int j = 0; j < 144; j += 8) {
        vertices[j + 0] += pos_x;
        vertices[j + 1] += pos_y;
        vertices[j + 2] += pos_z;
    }
}

void Pyramid::move_direction(int direction_given, int& animation) {
    isTransitioning = 1;
    animation = 1;
    int direction = direction_given;
    if (direction == 3) translation_direction = glm::vec3( 0.0f,  0.0f, -2.0f);
    if (direction == 4) translation_direction = glm::vec3( 2.0f,  0.0f,  0.0f);
    if (direction == 1) translation_direction = glm::vec3( 0.0f,  0.0f,  2.0f);
    if (direction == 2) translation_direction = glm::vec3( -2.0f, 0.0f,  0.0f);
}

void Pyramid::move_pyramid() {
    for (int i = 0; i < 144; i += 8) {
        glm::vec3 position(vertices[i], vertices[i + 1], vertices[i + 2]);
        glm::vec3 translatedPosition = position + translation_direction;
        vertices[i] = translatedPosition.x;
        vertices[i + 1] = translatedPosition.y;
        vertices[i + 2] = translatedPosition.z;
    }
}


Pyramid::~Pyramid() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}


