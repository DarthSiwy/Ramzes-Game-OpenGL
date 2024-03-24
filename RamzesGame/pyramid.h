#ifndef PYRAMID_RENDERER_H
#define PYRAMID_RENDERER_H

#include <glad/glad.h>
#include "shader_s.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Pyramid {
public:
    float vertices[288] = {
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

private:
    unsigned int VAO, VBO;
};

#endif