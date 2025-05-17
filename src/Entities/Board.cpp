//
// Created by markusssh on 03.05.2025.
//

#include <algorithm>
#include <ChessProj/Board.h>

#include "../Factories/PieceFactory.h"

Board::Board() {
    for (auto &row: board) {
        for (auto &cell: row) {
            cell = nullptr;
        }
    }
}

void Board::initializeStandardBoard() {
    // Initialize pawns
    for (int col = 0; col < 8; ++col) {
        board[1][col] = PieceFactory::createPiece(Piece::PAWN, Piece::BLACK);
        board[6][col] = PieceFactory::createPiece(Piece::PAWN, Piece::WHITE);
    }

    // Initialize rooks
    board[0][0] = PieceFactory::createPiece(Piece::ROOK, Piece::BLACK);
    board[0][7] = PieceFactory::createPiece(Piece::ROOK, Piece::BLACK);
    board[7][0] = PieceFactory::createPiece(Piece::ROOK, Piece::WHITE);
    board[7][7] = PieceFactory::createPiece(Piece::ROOK, Piece::WHITE);

    // Initialize knights
    board[0][1] = PieceFactory::createPiece(Piece::KNIGHT, Piece::BLACK);
    board[0][6] = PieceFactory::createPiece(Piece::KNIGHT, Piece::BLACK);
    board[7][1] = PieceFactory::createPiece(Piece::KNIGHT, Piece::WHITE);
    board[7][6] = PieceFactory::createPiece(Piece::KNIGHT, Piece::WHITE);

    // Initialize bishops
    board[0][2] = PieceFactory::createPiece(Piece::BISHOP, Piece::BLACK);
    board[0][5] = PieceFactory::createPiece(Piece::BISHOP, Piece::BLACK);
    board[7][2] = PieceFactory::createPiece(Piece::BISHOP, Piece::WHITE);
    board[7][5] = PieceFactory::createPiece(Piece::BISHOP, Piece::WHITE);

    // Initialize queens
    board[0][3] = PieceFactory::createPiece(Piece::QUEEN, Piece::BLACK);
    board[7][3] = PieceFactory::createPiece(Piece::QUEEN, Piece::WHITE);

    // Initialize kings
    board[0][4] = PieceFactory::createPiece(Piece::KING, Piece::BLACK);
    board[7][4] = PieceFactory::createPiece(Piece::KING, Piece::WHITE);
}

bool Board::isValidPosition(const Position &pos) {
    return pos.isValid();
}

const Piece *Board::getPieceAt(const Position &pos) const {
    if (!isValidPosition(pos)) {
        return nullptr;
    }

    return board[pos.row][pos.col].get();
}

Piece *Board::getPieceAt(const Position &pos) {
    if (!isValidPosition(pos)) {
        return nullptr;
    }

    return board[pos.row][pos.col].get();
}

bool Board::isPositionEmpty(const Position &pos) const {
    if (!isValidPosition(pos)) {
        return false;
    }

    return board[pos.row][pos.col].get() == nullptr;
}

bool Board::isOpponentPiece(const Position &pos, Piece::Color playerColor) const {
    if (!isValidPosition(pos)) {
        return false;
    }

    const Piece *piece = getPieceAt(pos);
    return piece != nullptr && piece->getColor() == playerColor;
}

void Board::movePiece(const Position &from, const Position &to) {
    if (!isValidPosition(from) || !isValidPosition(to)) {
        return;
    }

    if (Piece *piece = getPieceAt(from)) {
        if (piece->getPieceType() == Piece::PAWN) {
            dynamic_cast<Pawn *>(piece)->setMoved();
        } else if (piece->getPieceType() == Piece::KING) {
            dynamic_cast<King *>(piece)->setMoved();
        } else if (piece->getPieceType() == Piece::ROOK) {
            dynamic_cast<Rook *>(piece)->setMoved();
        }

        board[to.row][to.col] = std::move(board[from.row][from.col]);
    }
}

bool Board::isValidMove(const Position &from, const Position &to) const {
    if (!isValidPosition(from) || !isValidPosition(to)) {
        return false;
    }

    const Piece *piece = getPieceAt(from);
    if (!piece) {
        return false;
    }

    std::vector<Position> possibleMoves = piece->getPossibleMoves(*this, from);

    return std::ranges::any_of(possibleMoves,
                               [&to](const auto &move) {
                                   return move == to;
                               });
}

std::vector<Position> Board::getValidMovesForPieceAt(const Position &pos) const {
    std::vector<Position> validMoves;

    if (!isValidPosition(pos)) {
        return validMoves;
    }

    const Piece *piece = getPieceAt(pos);
    if (!piece) {
        return validMoves;
    }

    return piece->getPossibleMoves(*this, pos);
}

bool Board::isInCheck(const Piece::Color kingColor) const {
    const Position kingPos = getKingPosition(kingColor);
    if (!isValidPosition(kingPos)) {
        return false;
    }

    const Piece::Color opponentColor = (kingColor == Piece::WHITE) ? Piece::BLACK : Piece::WHITE;

    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            if (const Piece *piece = board[row][col].get(); piece && piece->getColor() == opponentColor) {
                Position piecePos(row, col);

                for (std::vector<Position> moves = piece->getPossibleMoves(*this, piecePos);
                     const auto &move: moves) {
                    if (move == kingPos) {
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

Position Board::getKingPosition(const Piece::Color kingColor) const {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if (const Piece *piece = board[row][col].get();
                piece->getPieceType() == Piece::KING && piece->getColor() == kingColor) {
                return {row, col};
            }
        }
    }

    // This should never happen in a valid chess game
    return {-1, -1};
}
