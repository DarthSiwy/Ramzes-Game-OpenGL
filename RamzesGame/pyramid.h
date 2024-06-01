#ifndef PYRAMID_RENDERER_H
#define PYRAMID_RENDERER_H

#include <glad/glad.h>
#include "shader_s.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <map>
#include <cmath>
#include <string>
#include <vector>
#include <random>
#include <iostream>

class Pyramid {
public:
    float vertices[144] = {
        //     POSITION              COLOR           TEXTURE   
        -1.0f, 0.0f, -1.0f,    1.0f, 1.0f, 0.0f,    0.0f, 1.0f,
         1.0f, 0.0f, -1.0f,    1.0f, 1.0f, 0.0f,    1.0f, 1.0f,
         1.0f, 0.0f,  1.0f,    1.0f, 1.0f, 0.0f,    1.0f, 0.0f,
         1.0f, 0.0f,  1.0f,    1.0f, 1.0f, 0.0f,    1.0f, 0.0f,
        -1.0f, 0.0f,  1.0f,    1.0f, 1.0f, 0.0f,    0.0f, 0.0f,
        -1.0f, 0.0f, -1.0f,    1.0f, 1.0f, 0.0f,    0.0f, 1.0f,

        -1.0f, 0.0f, 1.0f,     1.0f, 0.0f, 0.0f,    0.0f, 1.0f,
         1.0f, 0.0f, 1.0f,     1.0f, 0.0f, 0.0f,    1.0f, 1.0f,
         0.0f, 2.0f, 0.0f,     1.0f, 0.0f, 0.0f,    1.0f, 0.0f,

        -1.0f, 0.0f, -1.0f,    1.0f, 0.5f, 0.0f,    0.0f, 1.0f,
         1.0f, 0.0f, -1.0f,    1.0f, 0.5f, 0.0f,    1.0f, 1.0f,
         0.0f, 2.0f,  0.0f,    1.0f, 0.5f, 0.0f,    1.0f, 0.0f,

        -1.0f, 0.0f,  1.0f,    0.0f, 1.0f, 0.0f,    0.0f, 1.0f,
        -1.0f, 0.0f, -1.0f,    0.0f, 1.0f, 0.0f,    1.0f, 1.0f,
         0.0f, 2.0f,  0.0f,    0.0f, 1.0f, 0.0f,    1.0f, 0.0f,

         1.0f, 0.0f,  1.0f,    0.0f, 0.0f, 1.0f,    0.0f, 1.0f,
         1.0f, 0.0f, -1.0f,    0.0f, 0.0f, 1.0f,    1.0f, 1.0f,
         0.0f, 2.0f,  0.0f,    0.0f, 0.0f, 1.0f,    1.0f, 0.0f
    };

    float step = 2.0f;
    int isTransitioning = 0;
    float transitionProgress = 0.0f;
    float transition_speed = 10.0f;
    int direction = 0; 
    glm::vec3 translation_direction = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 translation_animation = glm::vec3(0.0f, 0.0f, 0.0f);
    int posX;
    int posY;

    Pyramid();
    void render(const Shader& shader, const glm::mat4& view, const glm::mat4& projection,  glm::mat4& model, int& animation);
    ~Pyramid();

    void move(float pos_x, float pos_y, float pos_z);
    void move_direction(int direction_given, int &animation);
    void move_pyramid();

private:
    unsigned int VAO, VBO;
};

#endif