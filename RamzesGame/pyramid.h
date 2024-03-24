#ifndef PYRAMID_RENDERER_H
#define PYRAMID_RENDERER_H

#include <glad/glad.h>
#include "shader_s.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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

    Pyramid();
    void render(const Shader& shader, const glm::mat4& view, const glm::mat4& projection) const;
    ~Pyramid();

    void move_pyramid(float pos_x, float pos_y, float pos_z);

private:
    unsigned int VAO, VBO;
};

#endif