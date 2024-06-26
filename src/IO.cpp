#include "IO.h"
#include <iostream>
#include <regex>

const char* BLACK_BG = "\e[48;5;0m";   // Black background
const char* WHITE_BG = "\e[48;5;15m";  // White background

void IO::printWelcomeMessage() const {
    std::string spacer = "         ";
    std::cout << spacer << WHITE_BG <<                   "                                               " << RESET << "\n";
    std::cout << spacer << WHITE_BG << "  " << BLACK_BG << "                                           " << WHITE_BG << "  " << RESET << "\n";
    std::cout << spacer << WHITE_BG << "  " << BLACK_BG << "              WELCOME TO CHESS             " << WHITE_BG << "  " << RESET << "\n";
    std::cout << spacer << WHITE_BG << "  " << BLACK_BG << "                                           " << WHITE_BG << "  " << RESET << "\n";
    std::cout << spacer << WHITE_BG << "  " << BLACK_BG << "              ♖ ♘ ♗ ♕ ♔ ♗ ♘ ♖              " << WHITE_BG << "  " << RESET << "\n";
    std::cout << spacer << WHITE_BG << "  " << BLACK_BG << "              ♜ ♞ ♝ ♛ ♚ ♝ ♞ ♜              " << WHITE_BG << "  " << RESET << "\n";
    std::cout << spacer << WHITE_BG << "  " << BLACK_BG << "                                           " << WHITE_BG << "  " << RESET << "\n";
    std::cout << spacer << WHITE_BG <<                   "                                               " << RESET << "\n";
    std::cout << "\n" << "\n";
}

void IO::printBoard(const Board& board) const {
    board.print();
}

void IO::printOutput(const std::string& message) const {
    std::cout << message << std::endl;
}

std::string IO::getInput() const {
    std::string input;
    std::regex move_regex("^[a-h][1-8] [a-h][1-8]$");

    while (true) {
        printOutput("Enter move (e.g., e2 e4):");
        std::getline(std::cin, input);

        if (std::regex_match(input, move_regex)) {
            // Check if the input contains two identical coordinates
            std::string from = input.substr(0, 2);
            std::string to = input.substr(3, 2);

            if (from == to) {
                printOutput("Sire, the coordinates cannot be the same.");
            } else {
                return input;
            }
        } else {
            printOutput("Sire, that input is invalid.");
        }
    }
}

std::string IO::getInputPromotion() const {
    std::string input;

    while (true) {
        printOutput("Promotion! Choose: R (Rook), K (Knight), B (Bishop), Q (Queen)");
        std::getline(std::cin, input);
        if (input == "Q") {
            return input;
        } else if (input == "R" || input == "K" || input == "B") {
            printOutput("An interesting choice sire...");
            return input;
        } else {
            printOutput("Sire, that input is invalid.");
        }
    }
}

std::string IO::getPlayAgain() const {
    std::string input;

    while (true) {
        printOutput("Play again? (Y/N)");
        std::getline(std::cin, input);

        if (input == "Y" || input == "N") {
            return input;
        } else {
            printOutput("Sire, that input is invalid.");
        }
    }
}