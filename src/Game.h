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

    bool isMoveValid(const std::string& from, const std::string& to) const;
    void makeMove(const std::string& from, const std::string& to);
    bool isInCheck(const Board& boardToCheck, PieceColor color) const;
    bool willBeCheck(int fromRow, int fromCol, int toRow, int toCol) const;
    bool isCastlingMove(int fromRow, int fromCol, int toRow, int toCol) const;
};

#endif // GAME_H
