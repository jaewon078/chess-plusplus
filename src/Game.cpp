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

    // 3. Check if move is castling
    if (isCastlingMove(fromRow, fromCol, toRow, toCol)) {
        return true;
    }

    // 4. Check if move is valid for the piece
    if (!piece->isMoveValid(fromRow, fromCol, toRow, toCol, board)) {
        if (isEnPassant(fromRow, fromCol, toRow, toCol)) {
            return true;
        }
        return false;
    }

    // 5. Check if move exposes the king or resolves a check
    if (willBeCheck(fromRow, fromCol, toRow, toCol)) {
        io.printOutput("Sire, this move would put us in dire straits.");
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

    // Check if the move is a castling move
    if (isCastlingMove(fromRow, fromCol, toRow, toCol)) {
        // Perform the actual castling
        if (toCol == 6) { // Kingside
            board.movePiece(fromRow, fromCol, toRow, toCol, false); // king
            board.movePiece(fromRow, 7, fromRow, 5, false); // rook
        } else if (toCol == 2) { // Queenside
            board.movePiece(fromRow, fromCol, toRow, toCol, false); // king
            board.movePiece(fromRow, 0, fromRow, 3, false);
        }
    } else if (isEnPassant(fromRow, fromCol, toRow, toCol)) {
        // We can move the capturing pawn onto the captured pawn first to delete
        // Then move to proper position
        board.movePiece(fromRow, fromCol, fromRow, toCol, false);
        board.movePiece(fromRow, toCol, toRow, toCol, false);
    } else {
        // Normal move
        board.movePiece(fromRow, fromCol, toRow, toCol, false);
    }

    lastMove = from + to;
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
    boardCopy.movePiece(fromRow, fromCol, toRow, toCol, true);

    // Check if the moving piece will lead to check in the copied board
    const Piece* movingPiece = board.getPiece(fromRow, fromCol);
    bool isKingInCheck = isInCheck(boardCopy, movingPiece->getColor());

    return isKingInCheck;
}

bool Game::isCastlingMove(int fromRow, int fromCol, int toRow, int toCol) const {
    const Piece* piece1 = board.getPiece(fromRow, fromCol);
    const Piece* piece2 = nullptr;

    // Determine kingside/queenside castling move
    if (toCol == 6) {
        piece2 = board.getPiece(fromRow, 7);
    } else if (toCol == 2) {
        piece2 = board.getPiece(fromRow, 0);
    } else {
        return false;
    }

    // This hurt to write as it might hurt to read, but if you follow the if statements
    // The code is fairly simple to understand

    // First check that piece1 is a king and piece2 is a rook
    if (const King* king = dynamic_cast<const King*>(piece1)) {
        if (const Rook *rook = dynamic_cast<const Rook *>(piece2)) {
            // Now make sure that neither the king nor rook has moved
            if (!king->getMoved() && !rook->getMoved()) {
                // Now make sure that path between king and rook is clear

                if (toCol == 6) { // Kingside
                    if (board.getPiece(fromRow, 5) == nullptr && board.getPiece(fromRow, 6) == nullptr) {
                        // Make sure that king not in check and will not pass through/end up in check
                        if (!willBeCheck(fromRow, fromCol, fromRow, 5) &&
                            !willBeCheck(fromRow, fromCol, fromRow, 6)) {
                            return true;
                        }
                    }
                } else if (toCol == 2) { // Queenside
                    if (board.getPiece(fromRow, 1) == nullptr && board.getPiece(fromRow, 2) == nullptr &&
                        board.getPiece(fromRow, 3) == nullptr) {
                        // Make sure that king not in check and will not pass through/end up in check
                        if (!willBeCheck(fromRow, fromCol, fromRow, 3) &&
                            !willBeCheck(fromRow, fromCol, fromRow, 2)) {
                            return true;
                        }
                    }
                }
            }
        }
    }

    return false;
}

bool Game::isEnPassant(int fromRow, int fromCol, int toRow, int toCol) const {
    const Piece* piece = board.getPiece(fromRow, fromCol);
    // Check if piece is pawn
    if (const Pawn* pawn = dynamic_cast<const Pawn*>(piece)) {
        // The move must be diagonal and
        if (abs(fromCol - toCol) == 1 && (toRow - fromRow == (whiteTurn ? 1 : -1))) {
            // The target square must be empty
            if (board.getPiece(toRow, toCol) == nullptr) {
                int lastFromRow = lastMove[1] - '1';
                int lastToRow = lastMove[3] - '1';
                int lastToCol = lastMove[2] - 'a';

                // Now we check if the last move was a two-square pawn move
                if (const Pawn* lastPawn = dynamic_cast<const Pawn*>(board.getPiece(lastToRow, lastToCol))) {
                    if (lastToCol == toCol && abs(lastToRow - lastFromRow) == 2) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}