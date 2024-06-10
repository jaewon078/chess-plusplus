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
    void initialize();
    void print() const;
    void movePiece(int fromRow, int fromCol, int toRow, int toCol);
    const Piece* getPiece(int row, int col) const { return board[row][col].get(); }
    std::pair<int, int> findKingPosition(PieceColor color) const;

private:
    std::vector<std::vector<std::shared_ptr<Piece>>> board;
    void printPieceTop(const std::shared_ptr<Piece>& piece, const char* bg_color) const;
    void printPieceMiddle(const std::shared_ptr<Piece>& piece, const char* bg_color) const;
    void printPieceBottom(const std::shared_ptr<Piece>& piece, const char* bg_color) const;
    void printColumnLabels() const;
    void printTopBorder() const;
    void printBottomBorder() const;
};

#endif // BOARD_H
