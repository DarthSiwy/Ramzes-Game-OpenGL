#ifndef BORDER_RENDERER_H
#define BORDER_RENDERER_H

#include <glad/glad.h>
#include "shader_s.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Border {
    public:
        float border_vertices[48] = {
            // Positions                // Colors
             11.0f,  0.0f,  -1.0f,    0.0f,  0.0f,  0.0f,
             11.0f,  0.0f,  15.0f,    0.0f,  0.0f,  0.0f,

              -1.0f,  0.0f, 15.0f,    0.0f,  0.0f,  0.0f,
             11.0f,  0.0f,  15.0f,    0.0f,  0.0f,  0.0f,

             -1.0f,  0.0f,  -1.0f,    0.0f,  0.0f,  0.0f, 
             11.0f,  0.0f,  -1.0f,    0.0f,  0.0f,  0.0f,

              -1.0f,  0.0f,  -1.0f,   0.0f,  0.0f,  0.0f,
             -1.0f,  0.0f,  15.0f,    0.0f,  0.0f,  0.0f,            
        };     

        Border();
        void render(const Shader& shader, const glm::mat4& view, const glm::mat4& projection) const;
        ~Border();

    private:
        unsigned int vao, vbo;
};

#endif