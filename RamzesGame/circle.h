#ifndef CIRCLE_RENDERER_H
#define CIRCLE_RENDERER_H

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

class Circle {
public:
    Circle(float radius = 0.9f);
    void render(const Shader& shader, const glm::mat4& view, const glm::mat4& projection);
    ~Circle();
    void move(float posX, float posY, float posZ);
    void change_color(float r, float g, float b);
    int value = 0;
    float radius=0.9f;
    

private:
    unsigned int VAO, VBO;
    std::vector<float> vertices;
};

#endif
