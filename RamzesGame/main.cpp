#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <ft2build.h>

#include "stb.cpp"
#include "shader_s.h"

#include "camera.h"
#include "axis.h"
#include "pyramid.h"
#include "border.h"
#include "functions.h"
#include "empty_space.h"
#include "keyboard.h"
#include "box.h"
#include "floor.h"
#include "circle.h"
#include "camera_movement.h"
#include "globals.h"
#include "player.h"

#include <map>
#include <cmath>
#include <string>
#include <vector>
#include <random>
#include <iostream>

#include FT_FREETYPE_H

void RenderText(Shader& shader, std::string text, float x, float y, float scale, glm::vec3 color);

// SETTINGS
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

// CAMERA
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float deltaTime = 0.0f;
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
float lastFrame = 0.0f;

// TEXT
struct Character {
    unsigned int TextureID; 
    glm::ivec2   Size;      
    glm::ivec2   Bearing;   
    unsigned int Advance;   
};
std::map<GLchar, Character> Characters;
unsigned int text_VAO, text_VBO;

// MAIN --------------------------------------------------------------------------------------
int main() {
    // GLFW 
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "RamzesGame", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // CLASS OBJECTS
    Shader shader_main("shader_vertex", "shader_fragment");
    Shader shader_1("shader_vertex_1", "shader_fragment_1");
    Shader shader_2("shader_vertex_2", "shader_fragment_2");
    Shader textShader("shader_vertex_text", "shader_fragment_text");

    // TEXT
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(SCR_WIDTH), 0.0f, static_cast<float>(SCR_HEIGHT));
    textShader.use();
    glUniformMatrix4fv(glGetUniformLocation(textShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    FT_Library ft;
    if (FT_Init_FreeType(&ft)) {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        return -1;
    }
    std::string font_name = ("resources/fonts/font_1.ttf");
    if (font_name.empty()) {
        std::cout << "ERROR::FREETYPE: Failed to load font_name" << std::endl;
        return -1;
    }
    FT_Face face;
    if (FT_New_Face(ft, font_name.c_str(), 0, &face)) {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        return -1;
    }
    else {
        FT_Set_Pixel_Sizes(face, 0, 48);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        for (unsigned char c = 0; c < 128; c++) {
            if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
                std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
                continue;
            }
            unsigned int texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
            );
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            Character character = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                static_cast<unsigned int>(face->glyph->advance.x)
            };
            Characters.insert(std::pair<char, Character>(c, character));
        }
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
    glGenVertexArrays(1, &text_VAO);
    glGenBuffers(1, &text_VBO);
    glBindVertexArray(text_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, text_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);  

    // CREATE OBJECTS
    Axis axis;
    Border border;
    Box box;
    Floor floor(0,0,12,16);
    Pyramid pyramids[47];
    Circle circles[8][6];
    Circle sand(50.0f);
    Empty_Space empty_space_on_board(8,6);
    Player players[2];

    // STARTING FUNCTIONS
    std::vector<std::vector<int>> board_pyramids;
    set_pyramids_default(pyramids);
    set_pyramids_vector(pyramids,  1, -1.02, 1);
    set_circles_default(circles);
    set_circles_vector(circles, 1, 0.01, 1);
    set_board_circles(circles);
    sand.move(6, -10, 8);
    sand.change_color(0.85f, 0.65f, 0.13f);
    
    // TEXTURES
    unsigned int texture1;
    unsigned char* data;
    int width, height, nrChannels;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    data = stbi_load("resources/textures/wall.jpg", &width, &height, &nrChannels, 4);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else std::cout << "Failed to load texture" << std::endl;
    stbi_image_free(data);  
    
    // CAMERA POSITION
    camera.Position.x = 14.0f;
    camera.Position.y = 10.0f;
    camera.Position.z = 20.0f;
    camera.Pitch += -40.0f;
    camera.Yaw += -40.0f;
    camera.updateCameraVectors();

    // keyboard
    int previousKeyState[10], currentKeyState[10];
    for (int i = 0; i < 10; i++) previousKeyState[i] = GLFW_RELEASE;

    // GAME VARIABLES
    int move_direction = 0;
    int animation = 0;
    int current_pyramid = 0;

  // RENDER LOOP      ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  // RENDER LOOP      ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    glfwSwapInterval(1);
    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        shader_main.use();
        glEnable(GL_DEPTH_TEST);
        glDisable(GL_BLEND);
        glClearColor(0.529f, 0.808f, 0.922f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // TIME 
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // MATRIX CREATE
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        
        // SHADER BIND
        shader_main.setMat4("projection", projection);
        shader_main.setMat4("view", view);
        shader_main.setMat4("model", model);
      
        // RENDER 
        axis.render(shader_main, view, projection);
        border.render(shader_main, view, projection);
        box.render(shader_1, view, projection, model);
        floor.render(shader_1, view, projection, model);
        sand.render(shader_main, view, projection);
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 6; j++) circles[i][j].render(shader_main, view, projection);
        }
        for (int i = 0; i < 47; i++)    pyramids[i].render(shader_2, view, projection, model, animation);   

        // TEXT PRINTING
        RenderText(textShader, "Player 1: " + std::to_string(players[0].points), 25.0f, 1000.0f, 0.5f, glm::vec3(0.9, 0.0f, 0.0f));
        RenderText(textShader, "Player 2: " + std::to_string(players[1].points), 25.0f, 970.0f, 0.5f, glm::vec3(0.0, 1.0f, 0.0f));

        // UPDATE KEYBOARD
        updateKeyboardState(window, currentKeyState);

        // MOVEMENTS
        if (animation == 0){
            if (currentKeyState[1] == GLFW_PRESS && previousKeyState[1] == GLFW_RELEASE) move_direction = 10;
            if (currentKeyState[2] == GLFW_PRESS && previousKeyState[2] == GLFW_RELEASE) move_direction = 30;
            if (currentKeyState[3] == GLFW_PRESS && previousKeyState[3] == GLFW_RELEASE) move_direction = 20;
            if (currentKeyState[4] == GLFW_PRESS && previousKeyState[4] == GLFW_RELEASE) move_direction = 40;
        }

        if (move_direction > 9) {
            move_direction /= 10;
            current_pyramid = empty_space_on_board.find_pyramid(move_direction, empty_space_on_board, pyramids);
            if (empty_space_on_board.can_go(move_direction, empty_space_on_board)) {              
                pyramids[current_pyramid].move_direction(move_direction, animation);       
                empty_space_on_board.swap_pos(current_pyramid, empty_space_on_board, pyramids);
            }
            move_direction = 0;
        }

        for (int i = 0; i < 10; i++) previousKeyState[i] = currentKeyState[i];       
        // SWAP BUFFERS
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// RENDER TEXT
void RenderText(Shader& shader, std::string text, float x, float y, float scale, glm::vec3 color) {
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    shader.use();
    glUniform3f(glGetUniformLocation(shader.ID, "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(text_VAO);
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++) {
        Character ch = Characters[*c];
        float xpos = x + ch.Bearing.x * scale;
        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;
        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }
        };
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        glBindBuffer(GL_ARRAY_BUFFER, text_VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); 
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        x += (ch.Advance >> 6) * scale; 
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}