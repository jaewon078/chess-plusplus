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

// Add printPGN functionality here later

std::string IO::getInput() const {
    std::string input;
    std::regex move_regex("^[a-h][1-8] [a-h][1-8]$");

    while (true) {
        printOutput("Enter move (e.g., e2 e4) or type \"pgn\":");
        std::getline(std::cin, input);

        if (input == "pgn" || std::regex_match(input, move_regex)) {
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