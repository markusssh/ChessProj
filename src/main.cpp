#include <iostream>

#include "ChessProj/Board.h"

int main() {
    auto board = Board();
    board.initializeStandardBoard();
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board.getPieceAt({i, j})) {
                std::cout << "*";
            }
            else {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
    return 0;
}
