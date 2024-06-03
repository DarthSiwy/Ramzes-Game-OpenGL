#include "empty_space.h"

#include <vector>

Empty_Space::Empty_Space(int x, int y) : posX(x), posY(y) {
    // constructor implementation
}

int Empty_Space::can_go(int direction, const Empty_Space& empty_space) {
    int result = 0;
    if (direction == 1) {
        if (posX - 1 != -1) result = 1;
    }
    if (direction == 2) {
        if (posY  +1 != 6) result = 1;
    }
    if (direction == 3) {
        if (posX + 1 != 8) result = 1;
    }
    if (direction == 4) {
        if (posY - 1 != -1) result = 1;
    }
    return result;
}

int Empty_Space::find_pyramid(int direction, const Empty_Space& empty_space, Pyramid pyramids[]) {
    int searched_x = empty_space.posX;
    int searched_y = empty_space.posY;
    int result = 2;
    if (direction == 1) searched_x -= 1;
    if (direction == 2) searched_y += 1;
    if (direction == 3) searched_x += 1;
    if (direction == 4) searched_y -= 1;

    for (int i = 0; i < 48; i++) {
        if (pyramids[i].posX == searched_x and pyramids[i].posY == searched_y) result = i;
    }

    return result;
}

void Empty_Space::swap_pos(int current_pyramid, const Empty_Space& empty_space, Pyramid pyramids[]) {
    int temp_x = pyramids[current_pyramid].posX;
    int temp_y = pyramids[current_pyramid].posY;

    pyramids[current_pyramid].posX = posX;
    pyramids[current_pyramid].posY = posY;

    posX = temp_x;
    posY = temp_y;
}





// UNUSED
int Empty_Space::find_value(std::vector<std::vector<int>>& board, int direction, const Empty_Space& empty_space) {
    int result = 0;
    if (direction == 1) result = board[posX - 1][empty_space.posY];
    if (direction == 2) result = board[posX][empty_space.posY + 1];
    if (direction == 3) result = board[posX + 1][empty_space.posY];
    if (direction == 4) result = board[posX][empty_space.posY - 1];
    return result;
}

void Empty_Space::swap_value(std::vector<std::vector<int>>& board, int direction, Empty_Space& empty_space) {
    int value = 0;
    if (direction == 1) {
        value = board[empty_space.posX - 1][empty_space.posY];
        board[empty_space.posX - 1][empty_space.posY] = 77;
        board[empty_space.posX][empty_space.posY] = value;
        empty_space.posX += -1;
    }
    if (direction == 2) {
        value = board[empty_space.posX][empty_space.posY + 1];
        board[empty_space.posX][empty_space.posY + 1] = 77;
        board[empty_space.posX][empty_space.posY] = value;
        empty_space.posY += 1;
    }
    if (direction == 3) {
        value = board[empty_space.posX + 1][empty_space.posY];
        board[empty_space.posX + 1][empty_space.posY] = 77;
        board[empty_space.posX][empty_space.posY] = value;
        empty_space.posX += 1;
    }
    if (direction == 4) {
        value = board[empty_space.posX][empty_space.posY - 1];
        board[empty_space.posX][empty_space.posY - 1] = 77;
        board[empty_space.posX][empty_space.posY] = value;
        empty_space.posY -= 1;
    }
}