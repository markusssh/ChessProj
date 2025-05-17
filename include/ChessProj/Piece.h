//
// Created by markusssh on 03.05.2025.
//

#ifndef PIECE_H
#define PIECE_H
#include <cstdint>
#include <vector>

class Board;

struct Position {
    int row;
    int col;

    Position(const int r, const int c) : row(r), col(c) {}

    [[nodiscard]] bool isValid() const {
        return row >= 0 && row < 8 && col >= 0 && col < 8;
    }

    bool operator==(const Position &other) const {
        return row == other.row && col == other.col;
    }
};

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

    enum Color : std::uint8_t {
        WHITE,
        BLACK
    };

    virtual ~Piece() = default;
    [[nodiscard]] PieceType getPieceType() const { return pieceType; }
    [[nodiscard]] Color getColor() const { return pieceColor; }

    [[nodiscard]] virtual std::vector<Position> getPossibleMoves(
        const Board& board, const Position& currentPos) const = 0;


protected:
    explicit Piece(const PieceType type, const Color color) : pieceType(type), pieceColor(color) {}

private:
    PieceType pieceType;
    Color pieceColor;
};

class Pawn final : public Piece {
public:
    explicit Pawn(const Color color) : Piece(PAWN, color), hasMoved(false) {}

    [[nodiscard]] std::vector<Position> getPossibleMoves(
        const Board& board, const Position& currentPos) const override;

    void setMoved() { hasMoved = true; }
    [[nodiscard]] bool getHasMoved() const { return hasMoved; }

private:
    bool hasMoved;
};

class Rook final : public Piece {
public:
    explicit Rook(const Color color) : Piece(ROOK, color), hasMoved(false) {}

    [[nodiscard]] std::vector<Position> getPossibleMoves(
        const Board& board, const Position& currentPos) const override;

    void setMoved() { hasMoved = true; }
    [[nodiscard]] bool getHasMoved() const { return hasMoved; }

private:
    bool hasMoved;
};

class Knight final : public Piece {
public:
    explicit Knight(const Color color) : Piece(KNIGHT, color) {}

    [[nodiscard]] std::vector<Position> getPossibleMoves(
        const Board& board, const Position& currentPos) const override;
};

class Bishop final : public Piece {
public:
    explicit Bishop(const Color color) : Piece(BISHOP, color) {}

    [[nodiscard]] std::vector<Position> getPossibleMoves(
        const Board& board, const Position& currentPos) const override;
};

class Queen final : public Piece {
public:
    explicit Queen(const Color color) : Piece(QUEEN, color) {}

    [[nodiscard]] std::vector<Position> getPossibleMoves(
        const Board& board, const Position& currentPos) const override;
};

class King final : public Piece {
public:
    explicit King(const Color color) : Piece(KING, color), hasMoved(false), isInCheck(false) {}

    [[nodiscard]] std::vector<Position> getPossibleMoves(
        const Board& board, const Position& currentPos) const override;

    void setMoved() { hasMoved = true; }
    [[nodiscard]] bool getHasMoved() const { return hasMoved; }
    [[nodiscard]] bool getIsInCheck() const { return isInCheck; }

private:
    bool hasMoved;
    bool isInCheck;
};



#endif //PIECE_H
