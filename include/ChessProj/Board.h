//
// Created by markusssh on 03.05.2025.
//

#ifndef BOARD_H
#define BOARD_H
#include <array>
#include <memory>

#include "Piece.h"

class Board {
public:
    static constexpr int BOARD_SIZE = 8;

    Board();
    ~Board() = default;

    void initializeStandardBoard();

    [[nodiscard]] const Piece* getPieceAt(const Position& pos) const;
    [[nodiscard]] Piece* getPieceAt(const Position& pos);
    [[nodiscard]] bool isPositionEmpty(const Position& pos) const;

    [[nodiscard]] bool isOpponentPiece(const Position& pos, Piece::Color playerColor) const;

    void movePiece(const Position& from, const Position& to);
    [[nodiscard]] bool isValidMove(const Position& from, const Position& to) const;
    [[nodiscard]] std::vector<Position> getValidMovesForPieceAt(const Position& pos) const;

    [[nodiscard]] bool isInCheck(Piece::Color kingColor) const;
    [[nodiscard]] Position getKingPosition(Piece::Color kingColor) const;

private:
    std::array<std::array<std::unique_ptr<Piece>, BOARD_SIZE>, BOARD_SIZE> board;
    [[nodiscard]] static bool isValidPosition(const Position& pos) ;
};



#endif //BOARD_H
