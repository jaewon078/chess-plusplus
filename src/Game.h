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
};

#endif // GAME_H
