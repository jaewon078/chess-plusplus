#include "Piece.h"
#include "Board.h"
#include <cmath>

bool Pawn::isMoveValid(int fromRow, int fromCol, int toRow, int toCol, const Board& board) const {
    // Check the direction that the pawn is supposed to move (black moves down, white up)
    int direction = (color == WHITE) ? 1 : -1;

    // Check for forward moves (can move 1 or 2)
    if(fromCol == toCol) {
        // Advance one condition
        if (toRow == fromRow + direction and board.getPiece(toRow, toCol) == nullptr) {
            return true;
        }
        // Advance two condition
        if (toRow == fromRow + (2*direction) and board.getPiece(toRow,toCol) == nullptr
                                and board.getPiece(fromRow+direction, toCol) == nullptr) {
            return (color == WHITE and fromRow == 1) || (color == BLACK and fromRow == 6);
        }
    }

    // Check for diagonal moves
    if (std::abs(toCol-fromCol) == 1 && toRow == fromRow + direction) {
        const Piece* target = board.getPiece(toRow, toCol);
        if (target != nullptr && target->getColor() != color) {
            return true;
        }
    }

    // Add in en passant logic
    // Handle promotion later

    return false;
}

bool Rook::isMoveValid(int fromRow, int fromCol, int toRow, int toCol, const Board& board) const {
    // The rook must move either horizontally or vertically
    if (fromRow != toRow && fromCol != toCol) {
        return false;
    }

    // Same row (horizontal)
    if (fromRow == toRow) {
        int direction = (toCol > fromCol) ? 1 : -1; // Determine direction of movement

        // Check if any pieces block the rook within the row
        for (int col = fromCol + direction; col != toCol; col+=direction) {
            if (board.getPiece(toRow, col) != nullptr) {
                return false;
            }
        }
    }

    // Same col (vertical)
    if (fromCol == toCol) {
        int direction = (toRow > fromRow) ? 1 : -1; // Determine direction of movement

        // Check if any pieces block the rook within the col
        for (int row = fromRow + direction; row != toRow; row += direction) {
            if (board.getPiece(row, fromCol) != nullptr) {
                return false;
            }
        }
    }

    // The piece that rook potentially takes must be opponent
    const Piece* target = board.getPiece(toRow, toCol);
    if (target == nullptr || target->getColor() != color) {
        return true;
    }

    // Add castling at another time

    return false;
}

bool Knight::isMoveValid(int fromRow, int fromCol, int toRow, int toCol, const Board& board) const {
    // Must move either two squares vertically and one square horizontally or move
    // two squares horizontally and one square vertically
    if (!((std::abs(toRow - fromRow) == 2 && std::abs(toCol - fromCol) == 1) ||
          (std::abs(toCol - fromCol) == 2 && std::abs(toRow - fromRow) == 1))) {
        return false;
    }

    // The piece that the knight potentially takes must be opponent
    const Piece* target = board.getPiece(toRow, toCol);
    if (target == nullptr || target->getColor() != color) {
        return true;
    }

    return false;
}

bool Bishop::isMoveValid(int fromRow, int fromCol, int toRow, int toCol, const Board& board) const {
    // Bishop can only move diagonally (row and col delta must be the same)
    if (std::abs(toCol-fromCol) != std::abs(toRow-fromRow)) {
        return false;
    }

    // Get direction
    int colDirection = (toCol > fromCol) ? 1 : -1;
    int rowDirection = (toRow > fromRow) ? 1: -1;

    // Check if any pieces block the bishop
    int row = fromRow + rowDirection;
    for (int col = fromCol + colDirection; col != toCol; col += colDirection) {
        if (board.getPiece(row, col) != nullptr) {
            return false;
        }
        row += rowDirection;
    }

    // The piece that the bishop potentially takes must be opponent
    const Piece* target = board.getPiece(toRow, toCol);
    if (target == nullptr || target->getColor() != color) {
        return true;
    }

    return false;
}

bool Queen::isMoveValid(int fromRow, int fromCol, int toRow, int toCol, const Board& board) const {
    // The queen acts like a combined rook and bishop
    Rook tempRook(color);
    Bishop tempBishop(color);

    if (tempRook.isMoveValid(fromRow, fromCol, toRow, toCol, board) ||
        tempBishop.isMoveValid(fromRow, fromCol, toRow, toCol, board)) {
        return true;
    }

    return false;
}

bool King::isMoveValid(int fromRow, int fromCol, int toRow, int toCol, const Board& board) const {
    return true;
}