#include <iostream>
#include "Piece.h"
#include "Board.h"

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
    if (abs(toCol-fromCol) == 1 && toRow == fromRow + direction) {
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
    return true;
}

bool Knight::isMoveValid(int fromRow, int fromCol, int toRow, int toCol, const Board& board) const {
    return true;
}

bool Bishop::isMoveValid(int fromRow, int fromCol, int toRow, int toCol, const Board& board) const {
    return true;
}

bool Queen::isMoveValid(int fromRow, int fromCol, int toRow, int toCol, const Board& board) const {
    return true;
}

bool King::isMoveValid(int fromRow, int fromCol, int toRow, int toCol, const Board& board) const {
    return true;
}