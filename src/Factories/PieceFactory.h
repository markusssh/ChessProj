//
// Created by markusssh on 03.05.2025.
//

#ifndef PIECEFACTORY_H
#define PIECEFACTORY_H
#include <memory>
#include "ChessProj/Piece.h"

class PieceFactory {
public:
    static std::unique_ptr<Piece> createPiece(const Piece::PieceType type) {
        switch (type) {
            case Piece::PAWN:
                return std::make_unique<Pawn>();
            case Piece::ROOK:
                return std::make_unique<Rook>();
            case Piece::BISHOP:
                return std::make_unique<Bishop>();
            case Piece::KNIGHT:
                return std::make_unique<Knight>();
            case Piece::QUEEN:
                return std::make_unique<Queen>();
            case Piece::KING:
                return std::make_unique<King>();
            default: return nullptr;
        }
    }
};

#endif //PIECEFACTORY_H
