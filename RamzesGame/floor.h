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
    float x1, z1, x2, z2;
    Floor(int x, int y, int z, int w);
    float vertices[48] = {
        //     POSITION              COLOR           TEXTURE   
           x1,  0.0,      z1,    0.6f, 0.3f, 0.2f,    0.0f, 0.0f,    
           x2,  0.0f,     z1,    0.6f, 0.3f, 0.2f,    0.0f, 0.0f,
           x2,  0.0f,     z2,    0.6f, 0.3f, 0.2f,    0.0f, 0.0f,
           x1,  0.0f,     z1,    0.6f, 0.3f, 0.2f,    0.0f, 0.0f,
           x1,  0.0f,     z2,    0.6f, 0.3f, 0.2f,    0.0f, 0.0f,
           x2,  0.0f,     z2,    0.6f, 0.3f, 0.2f,    0.0f, 0.0f
    };

    Floor();
    void render(const Shader& shader, const glm::mat4& view, const glm::mat4& projection, glm::mat4& model);
    ~Floor();

private:
    unsigned int VAO, VBO;
};

#endif