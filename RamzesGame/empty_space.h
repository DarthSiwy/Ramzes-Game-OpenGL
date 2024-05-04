#include <vector>


class Empty_Space {
public:
    int posX;
    int posY;
    Empty_Space(int x, int y);

    int find_value(std::vector<std::vector<int>>& board, int direction, const Empty_Space& empty_space);
    void swap_value(std::vector<std::vector<int>>& board, int direction, Empty_Space& empty_space);
};