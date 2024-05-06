#pragma once
#include "pyramid.h"
#include "circle.h"

#include <map>
#include <cmath>
#include <string>
#include <vector>
#include <random>
#include <iostream>

void show_board(std::vector<std::vector<int>>& board);
void make_board(std::vector<std::vector<int>>& board);
void set_pyramids_default(Pyramid pyramids[]);
void set_pyramids_vector(Pyramid pyramids[], float x, float y, float z);
void set_circles_default(Circle circles[]);
void set_circles_vector(Circle circles[], float x, float y, float z);
