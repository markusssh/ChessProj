//
// Created by markusssh on 03.05.2025.
//

#include <ChessProj/Piece.h>

#include "ChessProj/Board.h"

std::vector<Position> Pawn::getPossibleMoves(const Board &board, const Position &currentPos) const {
    std::vector<Position> possibleMoves;
    const int direction = (getColor() == WHITE) ? -1 : 1;

    if (const Position forward(currentPos.row + direction, currentPos.col);
        forward.isValid() && board.isPositionEmpty(forward)) {
        possibleMoves.push_back(forward);

        if (!hasMoved) {
            if (const Position twoForward(currentPos.row + 2 * direction, currentPos.col);
                twoForward.isValid() && board.isPositionEmpty(twoForward)) {
                possibleMoves.push_back(twoForward);
            }
        }
    }

    if (const Position captureLeft(currentPos.row + direction, currentPos.col - 1);
        captureLeft.isValid() && board.isOpponentPiece(captureLeft, getColor())) {
        possibleMoves.push_back(captureLeft);
    }

    if (const Position captureRight(currentPos.row + direction, currentPos.col + 1);
        captureRight.isValid() && board.isOpponentPiece(captureRight, getColor())) {
        possibleMoves.push_back(captureRight);
    }

    return possibleMoves;
}

std::vector<Position> Rook::getPossibleMoves(const Board &board, const Position &currentPos) const {
    std::vector<Position> possibleMoves;

    for (int dir = 0; dir < 4; ++dir) {
        for (int step = 1; step < Board::BOARD_SIZE; ++step) {
            constexpr int dx[] = {0, 1, 0, -1};
            constexpr int dy[] = {-1, 0, 1, 0};

            Position newPos(currentPos.row + dy[dir] * step, currentPos.col + dx[dir] * step);

            if (!newPos.isValid()) {
                break;
            }

            if (board.isPositionEmpty(newPos)) {
                possibleMoves.push_back(newPos);
            } else if (board.isOpponentPiece(newPos, getColor())) {
                possibleMoves.push_back(newPos);
                break;
            } else {
                break;
            }
        }
    }

    return possibleMoves;
}

std::vector<Position> Knight::getPossibleMoves(const Board &board, const Position &currentPos) const {
    std::vector<Position> possibleMoves;

    const int moves[][2] = {
        {-2, -1}, {-2, 1}, {-1, -2}, {-1, 2},
        {1, -2}, {1, 2}, {2, -1}, {2, 1}
    };

    for (const auto &move: moves) {
        if (Position newPos(currentPos.row + move[0], currentPos.col + move[1]); newPos.isValid() &&
            (board.isPositionEmpty(newPos) || board.isOpponentPiece(newPos, getColor()))) {
            possibleMoves.push_back(newPos);
        }
    }

    return possibleMoves;
}

std::vector<Position> Bishop::getPossibleMoves(const Board &board, const Position &currentPos) const {
    std::vector<Position> possibleMoves;

    for (int dir = 0; dir < 4; ++dir) {
        for (int step = 1; step < Board::BOARD_SIZE; ++step) {
            constexpr int dx[] = {-1, 1, 1, -1};
            constexpr int dy[] = {-1, -1, 1, 1};
            Position newPos(currentPos.row + dy[dir] * step, currentPos.col + dx[dir] * step);

            if (!newPos.isValid()) {
                break;
            }

            if (board.isPositionEmpty(newPos)) {
                possibleMoves.push_back(newPos);
            } else if (board.isOpponentPiece(newPos, getColor())) {
                possibleMoves.push_back(newPos);
                break;
            } else {
                break;
            }
        }
    }

    return possibleMoves;
}

std::vector<Position> Queen::getPossibleMoves(const Board &board, const Position &currentPos) const {
    std::vector<Position> possibleMoves;

    for (int dir = 0; dir < 8; ++dir) {
        for (int step = 1; step < Board::BOARD_SIZE; ++step) {
            constexpr int dx[] = {0, 1, 1, 1, 0, -1, -1, -1};
            constexpr int dy[] = {-1, -1, 0, 1, 1, 1, 0, -1};
            Position newPos(currentPos.row + dy[dir] * step, currentPos.col + dx[dir] * step);

            if (!newPos.isValid()) {
                break;
            }

            if (board.isPositionEmpty(newPos)) {
                possibleMoves.push_back(newPos);
            } else if (board.isOpponentPiece(newPos, getColor())) {
                possibleMoves.push_back(newPos);
                break;
            } else {
                break;
            }
        }
    }

    return possibleMoves;
}

std::vector<Position> King::getPossibleMoves(const Board &board, const Position &currentPos) const {
    std::vector<Position> possibleMoves;

    for (int dir = 0; dir < 8; ++dir) {
        constexpr int dx[] = {0, 1, 1, 1, 0, -1, -1, -1};
        constexpr int dy[] = {-1, -1, 0, 1, 1, 1, 0, -1};

        if (Position newPos(currentPos.row + dy[dir], currentPos.col + dx[dir]); newPos.isValid() &&
            (board.isPositionEmpty(newPos) || board.isOpponentPiece(newPos, getColor()))) {
            possibleMoves.push_back(newPos);
        }
    }

    // Castling logic would go here

    return possibleMoves;
}
