#include "empty_space.h"

#include <vector>

Empty_Space::Empty_Space(int x, int y) : posX(x), posY(y) {
    // constructor implementation
}

int Empty_Space::find_value(std::vector<std::vector<int>>& board, int direction, const Empty_Space& empty_space) {
    int result = 0;
    if (direction == 1) result = board[empty_space.posX - 1][empty_space.posY];
    if (direction == 2) result = board[empty_space.posX][empty_space.posY + 1];
    if (direction == 3) result = board[empty_space.posX + 1][empty_space.posY];
    if (direction == 4) result = board[empty_space.posX][empty_space.posY - 1];
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