#ifndef BOX_RENDERER_H
#define BOX_RENDERER_H

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

class Box {
public:
    float vertices[48] = {
        //     POSITION              COLOR           TEXTURE   
        -1.0f,  0.5f,  -1.0f,    1.0f, 1.0f, 0.0f,    0.0f, 1.0f,
        11.0f,  0.5f,  -1.0f,    1.0f, 1.0f, 0.0f,    1.0f, 1.0f,
         11.0f, 0.0f,  -1.0f,    1.0f, 1.0f, 0.0f,    1.0f, 0.0f,

         0.0f,  0.5f,  -1.0f,    1.0f, 1.0f, 0.0f,    0.0f, 1.0f,
        0.0f,  0.5f,  -1.0f,    1.0f, 1.0f, 0.0f,    1.0f, 1.0f,
         11.0f, 0.0f,  -1.0f,    1.0f, 1.0f, 0.0f,    1.0f, 0.0f,
         
    };

    



    Box();
    void render(const Shader& shader, const glm::mat4& view, const glm::mat4& projection, glm::mat4& model);
    ~Box();

private:
    unsigned int VAO, VBO;
};

#endif