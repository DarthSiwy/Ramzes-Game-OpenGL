#pragma once
#include "pyramid.h"
#include "circle.h"

#include <map>
#include <cmath>
#include <string>
#include <vector>
#include <random>
#include <iostream>

void show_board_pyramids(std::vector<std::vector<int>>& board);
void make_board_pyramids(std::vector<std::vector<int>>& board);
void set_pyramids_default(Pyramid pyramids[]);
void set_pyramids_vector(Pyramid pyramids[], float x, float y, float z);
void set_circles_default(Circle circles[8][6]);
void set_board_circles(Circle circles[8][6]);
void set_circles_vector(Circle circles[8][6], float x, float y, float z);
glm::vec3 color_value(int drawn);