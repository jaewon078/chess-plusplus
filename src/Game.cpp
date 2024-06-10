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
    int fromRow = from[1] - '1';
    int fromCol = from[0] - 'a';
    int toRow = to[1] - '1';
    int toCol = to[0] - 'a';

    const Piece* piece = board.getPiece(fromRow, fromCol);

    // 1. Check if there is a piece at the selected coordinate
    if (piece == nullptr) {
        return false;
    }

    // 2. Check if it is that piece's turn
    if (piece->getColor() != (whiteTurn ? WHITE : BLACK)) {
        return false;
    }

    // 3. Check if move is valid for the piece
    if (!piece->isMoveValid(fromRow, fromCol, toRow, toCol, board)) {
        return false;
    }

    // 4. Check if move exposes the king or resolves a check
    if (willBeCheck(fromRow, fromCol, toRow, toCol)) {
        io.printOutput("Sire, do you wish to lose?");
        return false;
    }

    return true;
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

bool Game::isInCheck(const Board& boardToCheck, PieceColor color) const {
    std::pair<int, int> kingPos = boardToCheck.findKingPosition(color);
    int kingRow = kingPos.first;
    int kingCol = kingPos.second;

    // Check over the entire board to see if any opponent's piece can attack the king
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            const Piece *piece = boardToCheck.getPiece(row, col);
            if (piece != nullptr && piece->getColor() != color) {
                if (piece->isMoveValid(row, col, kingRow, kingCol, boardToCheck)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Game::willBeCheck(int fromRow, int fromCol, int toRow, int toCol) const {
    // Dangerous and complex to simulate moving the pieces around and undo it,
    // so implementing a copy board approach (although a bit expensive...)

    Board boardCopy = board;
    boardCopy.movePiece(fromRow, fromCol, toRow, toCol);

    // Check if the moving piece will lead to check in the copied board
    const Piece* movingPiece = board.getPiece(fromRow, fromCol);
    bool isKingInCheck = isInCheck(boardCopy, movingPiece->getColor());

    return isKingInCheck;
}