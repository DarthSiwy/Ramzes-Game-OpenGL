#ifndef FLOOR_RENDERER_H
#define FLOOR_RENDERER_H

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

class Floor {
public:
    float vertices[48] = {
        //     POSITION              COLOR           TEXTURE   
         0.0f,  0.0f,   0.0f,    0.6f, 0.3f, 0.0f,    0.0f, 0.0f,    
        12.0f,  0.0f,   0.0f,    0.6f, 0.3f, 0.0f,    0.0f, 0.0f,
        12.0f,  0.0f,  16.0f,    0.6f, 0.3f, 0.0f,    0.0f, 0.0f,
         0.0f,  0.0f,   0.0f,    0.6f, 0.3f, 0.0f,    0.0f, 0.0f,
         0.0f,  0.0f,  16.0f,    0.6f, 0.3f, 0.0f,    0.0f, 0.0f,
        12.0f,  0.0f,  16.0f,    0.6f, 0.3f, 0.0f,    0.0f, 0.0f
    };

    Floor();
    void render(const Shader& shader, const glm::mat4& view, const glm::mat4& projection, glm::mat4& model);
    ~Floor();

private:
    unsigned int VAO, VBO;
};

#endif