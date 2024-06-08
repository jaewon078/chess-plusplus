#include "Game.h"
#include <iostream>
#include <cctype>

Game::Game() : whiteTurn(true) {
    // Initialize board with pieces
    board.initialize();
}

void Game::start() {
    io.printWelcomeMessage();
    io.printBoard(board);

    while (true) {
        std::string from, to;
        std::string input;

        io.printOutput((whiteTurn ? "White" : "Black") + std::string("'s turn."));
        input = io.getInput();
        from = input.substr(0, 2);
        to = input.substr(3, 2);

        if (isMoveValid(from, to)) {
            makeMove(from, to);
            whiteTurn = !whiteTurn;
            io.printBoard(board);
        } else {
            io.printOutput("Sire, that is an invalid move. Try again.");
        }
    }
}

bool Game::isMoveValid(const std::string& from, const std::string& to) const {
    return true; // Placeholder
}

void Game::makeMove(const std::string& from, const std::string& to) {
    // Convert notation (e.g., e2, e4) to board indices
    int fromRow = from[1] - '1';
    int fromCol = from[0] - 'a';
    int toRow = to[1] - '1';
    int toCol = to[0] - 'a';

    // Move the piece on the board
    board.movePiece(fromRow, fromCol, toRow, toCol);
}
