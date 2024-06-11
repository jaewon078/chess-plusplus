#ifndef IO_H
#define IO_H

#include "Board.h"

class IO {
public:
    void printWelcomeMessage() const;
    void printBoard(const Board& board) const;
    std::string getInput() const;
    void printOutput(const std::string& message) const;
    std::string getInputPromotion() const;
    std::string getPlayAgain() const;
};

#endif // IO_H
