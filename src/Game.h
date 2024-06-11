#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "IO.h"
#include "Piece.h"

class Game {
public:
    Game();
    void start();

private:
    Board board;
    IO io;
    bool whiteTurn;
    std::string lastMove;

    bool isMoveValid(int fromRow, int fromCol, int toRow, int toCol) const;
    void makeMove(const std::string& from, const std::string& to);
    bool isInCheck(const Board& boardToCheck, PieceColor color) const;
    bool willBeCheck(int fromRow, int fromCol, int toRow, int toCol) const;
    bool isValidCastlingMove(int fromRow, int fromCol, int toRow, int toCol) const;
    bool isValidEnPassant(int fromRow, int fromCol, int toRow, int toCol) const;
    bool isPromotion(int fromRow, int fromCol, int toRow, int toCol) const;
    bool isCheckmate(PieceColor color) const;
    void resetGame();
};

#endif // GAME_H