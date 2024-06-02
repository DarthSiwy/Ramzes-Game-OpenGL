#ifndef CAMERA_MOVEMENT_H
#define CAMERA_MOVEMENT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "camera.h"
#include "globals.h"

void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

#endif // CAMERA_MOVEMENT_H
