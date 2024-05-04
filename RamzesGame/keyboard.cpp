#include "keyboard.h"

#include <GLFW/glfw3.h>

void updateKeyboardState(GLFWwindow* window, int* currentKeyState) {
    currentKeyState[1] = glfwGetKey(window, GLFW_KEY_UP);
    currentKeyState[2] = glfwGetKey(window, GLFW_KEY_DOWN);
    currentKeyState[3] = glfwGetKey(window, GLFW_KEY_RIGHT);
    currentKeyState[4] = glfwGetKey(window, GLFW_KEY_LEFT);
}
