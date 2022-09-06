//#include "lib.h"
#include "board_handler.h"

int main() {
//    App::run();
    BoarderHandler boarderHandler(5, 5);
    boarderHandler.printMatrix(true);
    return 0;
}
