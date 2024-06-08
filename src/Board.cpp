#include <iostream>
#include "Board.h"

const char* DARK_BG = "\e[48;5;22m";  // Dark green background
const char* LIGHT_BG = "\e[48;5;230m"; // Light cream background
const char* RESET = "\e[0m";
const char* DARK_TEXT = "\e[30m";  // Black text
const char* LIGHT_TEXT = "\e[37m"; // White text

Board::Board() {
    board.resize(8, std::vector<std::shared_ptr<Piece>>(8, nullptr));

    // Initialize the board with pieces
    board[0][0] = std::make_shared<Rook>(BLACK);
    board[0][1] = std::make_shared<Knight>(BLACK);
    board[0][2] = std::make_shared<Bishop>(BLACK);
    board[0][3] = std::make_shared<Queen>(BLACK);
    board[0][4] = std::make_shared<King>(BLACK);
    board[0][5] = std::make_shared<Bishop>(BLACK);
    board[0][6] = std::make_shared<Knight>(BLACK);
    board[0][7] = std::make_shared<Rook>(BLACK);

    for (int i = 0; i < 8; ++i) {
        board[1][i] = std::make_shared<Pawn>(BLACK);
        board[6][i] = std::make_shared<Pawn>(WHITE);
    }

    board[7][0] = std::make_shared<Rook>(WHITE);
    board[7][1] = std::make_shared<Knight>(WHITE);
    board[7][2] = std::make_shared<Bishop>(WHITE);
    board[7][3] = std::make_shared<Queen>(WHITE);
    board[7][4] = std::make_shared<King>(WHITE);
    board[7][5] = std::make_shared<Bishop>(WHITE);
    board[7][6] = std::make_shared<Knight>(WHITE);
    board[7][7] = std::make_shared<Rook>(WHITE);
}

void Board::printPieceTop(const std::shared_ptr<Piece>& piece, const char* bg_color) const {
    if (piece == nullptr) {
        std::cout << bg_color << "       " << RESET;
    } else {
        const char* text_color = (piece->getColor() == BLACK) ? DARK_TEXT : LIGHT_TEXT;
        std::cout << bg_color << text_color << piece->getTopLine() << RESET;
    }
}

void Board::printPieceMiddle(const std::shared_ptr<Piece>& piece, const char* bg_color) const {
    if (piece == nullptr) {
        std::cout << bg_color << "       " << RESET;
    } else {
        const char* text_color = (piece->getColor() == BLACK) ? DARK_TEXT : LIGHT_TEXT;
        std::cout << bg_color << text_color << piece->getMiddleLine() << RESET;
    }
}

void Board::printPieceBottom(const std::shared_ptr<Piece>& piece, const char* bg_color) const {
    if (piece == nullptr) {
        std::cout << bg_color << "       " << RESET;
    } else {
        const char* text_color = (piece->getColor() == BLACK) ? DARK_TEXT : LIGHT_TEXT;
        std::cout << bg_color << text_color << piece->getBottomLine() << RESET;
    }
}

void Board::print() const {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            const char* bg_color = ((row + col) % 2 == 0) ? LIGHT_BG : DARK_BG;
            printPieceTop(board[row][col], bg_color);
        }
        std::cout << "\n";

        for (int col = 0; col < 8; ++col) {
            const char* bg_color = ((row + col) % 2 == 0) ? LIGHT_BG : DARK_BG;
            printPieceMiddle(board[row][col], bg_color);
        }
        std::cout << "\n";

        for (int col = 0; col < 8; ++col) {
            const char* bg_color = ((row + col) % 2 == 0) ? LIGHT_BG : DARK_BG;
            printPieceBottom(board[row][col], bg_color);
        }
        std::cout << "\n";
    }
}
