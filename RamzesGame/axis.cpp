#include "axis.h"

AxisRenderer::AxisRenderer() {
    glGenVertexArrays(1, &axisVAO);
    glGenBuffers(1, &axisVBO);
    glBindVertexArray(axisVAO);
    glBindBuffer(GL_ARRAY_BUFFER, axisVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(axisVertices), axisVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);  
}

void AxisRenderer::render() {
    glBindVertexArray(axisVAO);
    glDrawArrays(GL_LINES, 0, 6);
}

AxisRenderer::~AxisRenderer() {
    glDeleteVertexArrays(1, &axisVAO);
    glDeleteBuffers(1, &axisVBO);
};