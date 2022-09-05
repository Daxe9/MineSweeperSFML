#include <vector>

class Matrix {
private:
    int directions[8][2] = {
            // top left corner
            {-1, -1},
            // top middle
            {-1, 0},
            // top right corner
            {-1, 1},
            // middle left
            {0,  -1},
            // middle right
            {0,  1},
            // bottom left corner
            {1,  -1},
            // bottom middle
            {1,  0},
            // bottom right corner
            {1,  1}};

public:

};

typedef struct Cell {
    int count;
    bool visible;
} Single_Cell;

std::vector<std::vector<Single_Cell>> createMatrix(int width, int height) {
    std::vector<std::vector<Single_Cell>> matrix;
    for (unsigned int i = 0; i < width; ++i) {
        std::vector<Single_Cell> temp;
        for (unsigned int j = 0; j < height; ++j) {
            Single_Cell cell;
            cell.visible = false;
            cell.count = 0;
            temp.push_back(cell);
        }
        matrix.push_back(temp);
    }
    return matrix;
}