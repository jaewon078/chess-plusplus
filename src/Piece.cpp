#include "Piece.h"
#include "Board.h"

bool Pawn::isMoveValid(int fromRow, int fromCol, int toRow, int toCol, const Board& board) const {
    return true;
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