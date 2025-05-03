//
// Created by markusssh on 03.05.2025.
//

#ifndef PIECE_H
#define PIECE_H
#include <cstdint>


class Piece {
public:
    enum PieceType : std::uint8_t {
        PAWN,
        ROOK,
        KNIGHT,
        BISHOP,
        QUEEN,
        KING
    };

    virtual ~Piece() = default;
    [[nodiscard]] PieceType getPieceType() const { return pieceType; }


protected:
    explicit Piece(const PieceType type) : pieceType(type) {}

private:
    PieceType pieceType;
};

class Pawn final : public Piece {
public:
    Pawn() : Piece(PAWN) {}
};

class Rook final : public Piece {
public:
    Rook() : Piece(ROOK) {}
};

class Knight final : public Piece {
public:
    Knight() : Piece(KNIGHT) {}
};

class Bishop final : public Piece {
public:
    Bishop() : Piece(BISHOP) {}
};

class Queen final : public Piece {
public:
    Queen() : Piece(QUEEN) {}
};

class King final : public Piece {
public:
    King() : Piece(KING) {}
};



#endif //PIECE_H
