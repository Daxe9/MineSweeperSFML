#include <vector>
#include <iostream>
#include <random>
#include <utility>
#define DEBUG 1


#if DEBUG == 1
using std::cout;
using std::cin;
using std::endl;
#endif



typedef struct Single_Cell {
    // if the count is -1 then it's a bomb
    int count;
    bool visible;
} Cell;

class BoarderHandler {
public:
    std::vector<std::vector<Cell>> matrix;
    int width;
    int height;
    int direction[8][2] = {
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

    BoarderHandler(int board_width = 5, int board_height = 5) {
        width = board_width;
        height = board_height;
        setDiscrminant(width * height / 8);
        setNeededCellToExplore(width * height - getDiscrminant());
        matrix = createMatrix();
    }

    std::vector<std::pair<int, int>> countVisibleCells() {
        std::vector<std::pair<int, int>> visible_cells;
        for (size_t i = 0; i < matrix.size(); ++i) {
            for (size_t j = 0; j < matrix.at(i).size(); ++j) {
                if (matrix.at(i).at(j).visible) {
                    visible_cells.emplace_back(std::make_pair(i, j));
                }
            }
        }
        return visible_cells;
    }
    int countBomb(std::vector<std::vector<Cell>> &_matrix, int x, int y) {
        int counter = 0;

        for (auto &arr : direction) {
            try {
                if (_matrix.at(x + arr[0]).at(y + arr[1]).count == -1) {
                    counter++;
                } else {
                    throw std::exception();
                }
            } catch (std::exception &e) {
                continue;
            }
        }

        return counter;
    }

    void controlNeighbours(int x, int y) {
        matrix.at(x).at(y).visible = true;
        setNeededCellToExplore(getNeededCellToExplore() - 1);
        for (auto &arr : direction) {
            try {
                if (matrix.at(x).at(y).count == 0) {
                    if (matrix.at(x + arr[0]).at(y + arr[1]).count != -1 &&
                        !matrix.at(x + arr[0]).at(y + arr[1]).visible) {
                        matrix.at(x + arr[0]).at(y + arr[1]).visible = true;
                        controlNeighbours(x + arr[0], y + arr[1]);
                    } else {
                        throw std::exception();
                    }
                } else {
                    if (matrix.at(x + arr[0]).at(y + arr[1]).count == 0 &&
                        !matrix.at(x + arr[0]).at(y + arr[1]).visible) {
                        controlNeighbours(x + arr[0], y + arr[1]);
                    } else {
                        throw std::exception();
                    }
                }
            } catch (std::exception &e) {
                continue;
            }
        }

    }

    // getter discriminant
    int getDiscrminant() const  {
        return discrminant;
    }
    // setter discriminant
    void setDiscrminant(int new_discrminant) {
        discrminant = new_discrminant;
    }

    // getter neededCellToExplore
    int getNeededCellToExplore() const {
        return neededCellToExplore;
    }
    // setter neededCellToExplore
    void setNeededCellToExplore(int new_neededCellToExplore) {
        neededCellToExplore = new_neededCellToExplore;
    }

    void printMatrix(bool reveal) {
        for (size_t i = 0; i < matrix.size(); ++i) {
            for (size_t j = 0; j < matrix.at(i).size(); ++j) {
                if (!reveal) {
                    if (matrix.at(i).at(j).visible) {
                        if (matrix.at(i).at(j).count == -1) {
                            cout << "X";
                        } else {
                            cout << matrix.at(i).at(j).count;
                        }
                    } else {
                        cout << "O";
                    }
                } else {
                    if (matrix.at(i).at(j).count == -1) {
                        cout << "X";
                    } else {
                        cout << matrix.at(i).at(j).count;
                    }
                }
                cout << "\t";
            }
            cout << endl;
        }
        cout << endl;
    }
private:
    int discrminant;
    int neededCellToExplore;
private:
    // initialize how many bombs are in the board
    void bombInitializer(std::vector<std::vector<Cell>> &_matrix)  {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<int> randomWidth(0, (int) _matrix.size() - 1);
        std::uniform_int_distribution<int> randomHeight(0, (int) _matrix.at(0).size() - 1);
        int i = 0;
        int newWidth, newHeight;
        while (i < getDiscrminant()) {
            do {
                newWidth = randomWidth(mt);
                newHeight = randomHeight(mt);
            } while (_matrix.at(newWidth).at(newHeight).count != 0);
            _matrix.at(newWidth).at(newHeight).count = -1;
            ++i;
        }
    }

    std::vector<std::vector<Cell>> createMatrix() {
        std::vector<std::vector<Cell>> _matrix;
        // initialized the boarrd
        for (int i = 0; i < width; ++i) {
            std::vector<Cell> temp;
            for (int j = 0; j < height; ++j) {
                Cell newCell;
                newCell.count = 0;
                newCell.visible = false;
                temp.push_back(newCell);
            }
            _matrix.push_back(temp);
        }

        // randomize bombs
        bombInitializer(_matrix);

        for (size_t i = 0; i < _matrix.size(); ++i) {
            for (size_t j = 0; j < _matrix.at(i).size(); ++j) {
                if (_matrix.at(i).at(j).count != -1) {
                    _matrix.at(i).at(j).count = countBomb(_matrix, (int) i, (int) j);
                }
            }
        }
        return _matrix;
    }


};