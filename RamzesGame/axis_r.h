#ifndef AXIS_RENDERER_H
#define AXIS_RENDERER_H

#include <glad/glad.h>
#include "shader_s.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Axis {
    public:
        float position[18] = {       
             0.0f,  0.0f,  0.0f,  // X-axis
             1.0f,  0.0f,  0.0f, 

             0.0f,  0.0f,  0.0f,  // Y-axis
             0.0f,  1.0f,  0.0f, 

             0.0f,  0.0f,  0.0f,  // Z-axis
             0.0f,  0.0f,  1.0f, 
        };

        float color[18] = {
            1.0f,  0.0f,  0.0f, // X-axis
            1.0f,  0.0f,  0.0f,

            0.0f,  1.0f,  0.0f, // Y-axis
            0.0f,  1.0f,  0.0f,

            0.0f,  0.0f,  1.0f, // Z-axis
            0.0f,  0.0f,  1.0f
        };

        //float axis_vertices[36];

        float axis_vertices[36] = {
            // Positions            // Colors
             0.0f,  0.0f,  0.0f,    1.0f,  0.0f,  0.0f, // X-axis
             1.0f,  0.0f,  0.0f,    1.0f,  0.0f,  0.0f,

             0.0f,  0.0f,  0.0f,    0.0f,  1.0f,  0.0f, // Y-axis
             0.0f,  1.0f,  0.0f,    0.0f,  1.0f,  0.0f,

             0.0f,  0.0f,  0.0f,    0.0f,  0.0f,  1.0f, // Z-axis
             0.0f,  0.0f,  1.0f,    0.0f,  0.0f,  1.0f
        };     

        Axis();
        void render(const Shader& shader, const glm::mat4& view, const glm::mat4& projection) const;
        void make_it();

        ~Axis();

    private:
        unsigned int vao, vbo;
};

#endif