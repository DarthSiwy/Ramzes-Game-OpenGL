#include <vector>

#include "pyramid.h"


class Empty_Space {
public:
    int posX;
    int posY;
    int curret_posiotn_calue;
    Empty_Space(int x, int y);

    int can_go(int direction, const Empty_Space& empty_space);
    void swap_value(std::vector<std::vector<int>>& board, int direction, Empty_Space& empty_space);
    void swap_pos(int direction, const Empty_Space& empty_space, Pyramid pyramids[]);

    int find_value(std::vector<std::vector<int>>& board, int direction, const Empty_Space& empty_space);
    int find_pyramid(int direction, const Empty_Space& empty_space, Pyramid pyramids[]);
};