#ifndef BOARD_H
#define BOARD_H

#include "Piece.h"
#include <vector>
#include <memory>

extern const char* DARK_BG;
extern const char* LIGHT_BG;
extern const char* RESET;
extern const char* DARK_TEXT;
extern const char* LIGHT_TEXT;

class Board {
public:
    Board();
    void print() const;

private:
    std::vector<std::vector<std::shared_ptr<Piece>>> board;
    void printPieceTop(const std::shared_ptr<Piece>& piece, const char* bg_color) const;
    void printPieceMiddle(const std::shared_ptr<Piece>& piece, const char* bg_color) const;
    void printPieceBottom(const std::shared_ptr<Piece>& piece, const char* bg_color) const;
};

#endif // BOARD_H
