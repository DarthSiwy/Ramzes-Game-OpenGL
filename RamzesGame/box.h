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
    float vertices[480] = {
        //     POSITION              COLOR           TEXTURE   
        0.0f,   0.0f,  0.0f,    1.0f, 0.5f, 0.0f,    0.0f, 0.0f,     // BACK IN
        12.0f,  0.0f,  0.0f,    1.0f, 0.5f, 0.0f,    0.0f, 0.0f,
        12.0f,  0.5f,  0.0f,    1.0f, 0.5f, 0.0f,    0.0f, 0.0f,
        0.0f,  0.0f,  0.0f,     1.0f, 0.5f, 0.0f,    0.0f, 0.0f,
        0.0f,  0.5f,  0.0f,     1.0f, 0.5f, 0.0f,    0.0f, 0.0f,
        12.0f,  0.5f,  0.0f,    1.0f, 0.5f, 0.0f,    0.0f, 0.0f,

        0.0f,  0.0f,  16.0f,    1.0f, 0.5f, 0.0f,    0.0f, 0.0f,     // FRONT IN
        12.0f,  0.0f,  16.0f,   1.0f, 0.5f, 0.0f,    0.0f, 0.0f,
        12.0f,  0.5f,  16.0f,   1.0f, 0.5f, 0.0f,    0.0f, 0.0f,
        0.0f,  0.0f,  16.0f,    1.0f, 0.5f, 0.0f,    0.0f, 0.0f,
        0.0f,  0.5f,  16.0f,    1.0f, 0.5f, 0.0f,    0.0f, 0.0f,
        12.0f,  0.5f,  16.0f,   1.0f, 0.5f, 0.0f,    0.0f, 0.0f,

        0.0f,  0.0f,  0.0f,     1.0f, 0.5f, 0.0f,    0.0f, 0.0f,      // RIGHT IN
        0.0f,  0.0f,  16.0f,    1.0f, 0.5f, 0.0f,    0.0f, 0.0f,
        0.0f,  0.5f,  16.0f,    1.0f, 0.5f, 0.0f,    0.0f, 0.0f,
        0.0f,  0.0f,  0.0f,     1.0f, 0.5f, 0.0f,    0.0f, 0.0f,
        0.0f,  0.5f,  0.0f,     1.0f, 0.5f, 0.0f,    0.0f, 0.0f,
        0.0f,  0.5f,  16.0f,    1.0f, 0.5f, 0.0f,    0.0f, 0.0f,

        12.0f,  0.0f,  0.0f,    1.0f, 0.5f, 0.0f,    0.0f, 0.0f,     // LEFT IN
        12.0f,  0.0f,  16.0f,   1.0f, 0.5f, 0.0f,    0.0f, 0.0f,
        12.0f,  0.5f,  16.0f,   1.0f, 0.5f, 0.0f,    0.0f, 0.0f,
        12.0f,  0.0f,  0.0f,    1.0f, 0.5f, 0.0f,    0.0f, 0.0f,
        12.0f,  0.5f,  0.0f,    1.0f, 0.5f, 0.0f,    0.0f, 0.0f,
        12.0f,  0.5f,  16.0f,   1.0f, 0.5f, 0.0f,    0.0f, 0.0f,
        
        -0.5f,  0.5f,  -0.5f,   1.0f, 0.7f, 0.0f,    0.0f, 0.0f,   // BACK HOR
        -0.5f,  0.5f,  0.0f,    1.0f, 0.7f, 0.0f,    0.0f, 0.0f,
        12.5f,  0.5f,  -0.5f,   1.0f, 0.7f, 0.0f,    0.0f, 0.0f,
        -0.5f,  0.5f,  0.0f,    1.0f, 0.7f, 0.0f,    0.0f, 0.0f,
        12.5f,  0.5f,  0.0f,    1.0f, 0.7f, 0.0f,    0.0f, 0.0f,
        12.5f,  0.5f,  -0.5f,   1.0f, 0.7f, 0.0f,    0.0f, 0.0f,

        -0.5f,  0.5f,  16.0f,   1.0f, 0.7f, 0.0f,    0.0f, 0.0f,   // FRONT HOR
        -0.5f,  0.5f,  16.5f,   1.0f, 0.7f, 0.0f,    0.0f, 0.0f,
        12.5f,  0.5f,  16.0f,   1.0f, 0.7f, 0.0f,    0.0f, 0.0f,
        -0.5f,  0.5f,  16.5f,   1.0f, 0.7f, 0.0f,    0.0f, 0.0f,
        12.5f,  0.5f,  16.5f,   1.0f, 0.7f, 0.0f,    0.0f, 0.0f,
        12.5f,  0.5f,  16.0f,   1.0f, 0.7f, 0.0f,    0.0f, 0.0f,
        
        -0.5f,  0.5f,  0.0f,    1.0f, 0.7f, 0.0f,    0.0f, 0.0f,   // LEFT HOR
        0.0f,  0.5f,  0.0f,    1.0f, 0.7f, 0.0f,    0.0f, 0.0f,
        0.0f,  0.5f,  16.5f,    1.0f, 0.7f, 0.0f,    0.0f, 0.0f,
        0.0f,  0.5f,  16.0f,    1.0f, 0.7f, 0.0f,    0.0f, 0.0f,
        -0.5f,  0.5f,  16.0f,    1.0f, 0.7f, 0.0f,    0.0f, 0.0f,
        -0.5f,  0.5f,  0.0f,    1.0f, 0.7f, 0.0f,    0.0f, 0.0f,

         12.0f,  0.5f,  0.0f,    1.0f, 0.7f, 0.0f,    0.0f, 0.0f,   // RIGHT HOR
        12.5f,  0.5f,  0.0f,    1.0f, 0.7f, 0.0f,    0.0f, 0.0f,
        12.5f,  0.5f,  16.5f,    1.0f, 0.7f, 0.0f,    0.0f, 0.0f,
        12.5f,  0.5f,  16.0f,    1.0f, 0.7f, 0.0f,    0.0f, 0.0f,
        12.0f,  0.5f,  16.0f,    1.0f, 0.7f, 0.0f,    0.0f, 0.0f,
        12.0f,  0.5f,  0.0f,    1.0f, 0.7f, 0.0f,    0.0f, 0.0f,
        
        







        0.0f,  0.5f,  0.0f,    1.0f, 0.7f, 0.0f,    0.0f, 0.0f,



    };

    



    Box();
    void render(const Shader& shader, const glm::mat4& view, const glm::mat4& projection, glm::mat4& model);
    ~Box();

private:
    unsigned int VAO, VBO;
};

#endif