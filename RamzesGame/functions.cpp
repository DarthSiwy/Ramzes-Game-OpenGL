#include "functions.h"
#include "pyramid.h"
#include "circle.h"

#include <map>
#include <cmath>
#include <string>
#include <vector>
#include <random>
#include <iostream>


void show_board_pyramids(std::vector<std::vector<int>>& board) {
    system("cls");
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 8; j++) {
            int value = board[i][j];
            if (value < 0) std::cout << "\x1B[31m"; 
            else if (value > 50) std::cout << "\x1B[32m";            
            std::cout << value << "\033[0m\t";
        }
        std::cout << "\n\n";
    }
    std::cout << "current position: \n\n";
}

void make_board_pyramids(std::vector<std::vector<int>>& board) {
    board = {
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1,  0,  1,  2,  3,  4,  5, -1},
        {-1,  6,  7,  8,  9, 10, 11, -1},
        {-1, 12, 13, 14, 15, 16, 17, -1},
        {-1, 18, 19, 20, 21, 22, 23, -1},
        {-1, 24, 25, 26, 27, 28, 29, -1},
        {-1, 30, 31, 32, 33, 34, 35, -1},
        {-1, 36, 37, 38, 39, 40, 41, -1},
        {-1, 42, 43, 44, 45, 46, 77, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1}
    };
}

void set_pyramids_default(Pyramid pyramids[]) {
    int x = 0, z = 0, step = 2; 
    int index = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 6; j++) {
            pyramids[index].posX = i+1;
            pyramids[index].posY = j+1;
            pyramids[index].move(x, 0.0f, z);
            x += step;
            index++;
            if (index == 47) j = 6;
        }
        z += step;
        x = 0;
    }
}

void set_circles_default(Circle circles[8][6]){
int x = 0, z = 0, step = 2;
for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 6; j++) {
        circles[i][j].move(x, 0, z);
        x += step;
    }
    z += step;
    x = 0;
}
}

void set_circles_vector(Circle circles[8][6], float x, float y, float z) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 6; j++) {
            circles[i][j].move(x, y, z);
        }
    }
}

void set_pyramids_vector(Pyramid pyramids[], float x, float y, float z) {
    for (int i = 0; i < 47; i++) {
        pyramids[i].move(x, y, z);
    }
}



