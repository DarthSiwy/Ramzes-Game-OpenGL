#include "axis.h"
#include <glm/glm.hpp> 

#include <algorithm>
#include <iostream>

// CREATE AXIS
void make_axis(float axisVertices[]) {
    float axisVertices_[] = {
        //   POSITION             COLOR 
        0.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,   // X-axis
        5.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,

        0.0f, 0.0f, 0.0f,   0.0f, 1.0f, 0.0f,   // Y-axis
        0.0f, 5.0f, 0.0f,   0.0f, 1.0f, 0.0f,

        0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 1.0f,   // Z-axis
        0.0f, 0.0f, 5.0f,   0.0f, 0.0f, 1.0f
    };
    for (int i = 0; i < 36; i++) axisVertices[i] = axisVertices_[i];
}