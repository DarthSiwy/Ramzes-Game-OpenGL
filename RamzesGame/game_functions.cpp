// game_functions.cpp
#include "game_functions.h"

void swap_value(std::vector<std::vector<int>>& board, int direction, Player& player) {
    int value = 0;
    if (direction == 1) {
        value = board[player.posX - 1][player.posY];
        board[player.posX - 1][player.posY] = 77;
        board[player.posX][player.posY] = value;
        player.posX += -1;
    }
    if (direction == 2) {
        value = board[player.posX][player.posY + 1];
        board[player.posX][player.posY + 1] = 77;
        board[player.posX][player.posY] = value;
        player.posY += 1;
    }
    if (direction == 3) {
        value = board[player.posX + 1][player.posY];
        board[player.posX + 1][player.posY] = 77;
        board[player.posX][player.posY] = value;
        player.posX += 1;
    }
    if (direction == 4) {
        value = board[player.posX][player.posY - 1];
        board[player.posX][player.posY - 1] = 77;
        board[player.posX][player.posY] = value;
        player.posY -= 1;
    }
}