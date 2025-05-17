//
// Created by markusssh on 03.05.2025.
//

#ifndef PIECEFACTORY_H
#define PIECEFACTORY_H
#include <memory>
#include "ChessProj/Piece.h"

class PieceFactory {
public:
    static std::unique_ptr<Piece> createPiece(const Piece::PieceType type, const Piece::Color color) {
        switch (type) {
            case Piece::PAWN:
                return std::make_unique<Pawn>(color);
            case Piece::ROOK:
                return std::make_unique<Rook>(color);
            case Piece::BISHOP:
                return std::make_unique<Bishop>(color);
            case Piece::KNIGHT:
                return std::make_unique<Knight>(color);
            case Piece::QUEEN:
                return std::make_unique<Queen>(color);
            case Piece::KING:
                return std::make_unique<King>(color);
            default: return nullptr;
        }
    }
};

#endif //PIECEFACTORY_H
