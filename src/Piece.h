#ifndef PIECE_H
#define PIECE_H

#include <cstdint>
#include <string>

enum PieceColor : uint8_t {
    NONE = 0,
    WHITE,
    BLACK
};

class Piece {
public:
    Piece(PieceColor color) : color(color) {}
    virtual ~Piece() = default;
    virtual std::string getTopLine() const = 0;
    virtual std::string getMiddleLine() const = 0;
    virtual std::string getBottomLine() const = 0;
    PieceColor getColor() const { return color; }

protected:
    PieceColor color;
};

class Pawn : public Piece {
public:
    Pawn(PieceColor color) : Piece(color) {}
    std::string getTopLine() const override {
        return "   O   ";
    }
    std::string getMiddleLine() const override {
        return "  ( )  ";
    }
    std::string getBottomLine() const override {
        return "  ===  ";
    }
};

class Rook : public Piece {
public:
    Rook(PieceColor color) : Piece(color) {}
    std::string getTopLine() const override {
        return "  ooo  ";
    }
    std::string getMiddleLine() const override {
        return "  | |  ";
    }
    std::string getBottomLine() const override {
        return "  ===  ";
    }
};

class Knight : public Piece {
public:
    Knight(PieceColor color) : Piece(color) {}
    std::string getTopLine() const override {
        return "  <*^  ";
    }
    std::string getMiddleLine() const override {
        return "  / |  ";
    }
    std::string getBottomLine() const override {
        return "  ===  ";
    }
};

class Bishop : public Piece {
public:
    Bishop(PieceColor color) : Piece(color) {}
    std::string getTopLine() const override {
        return "  (/)  ";
    }
    std::string getMiddleLine() const override {
        return "  / \\  ";
    }
    std::string getBottomLine() const override {
        return "  ===  ";
    }
};

class Queen : public Piece {
public:
    Queen(PieceColor color) : Piece(color) {}
    std::string getTopLine() const override {
        return "  oOo  ";
    }
    std::string getMiddleLine() const override {
        return "  )|(  ";
    }
    std::string getBottomLine() const override {
        return "  ===  ";
    }
};

class King : public Piece {
public:
    King(PieceColor color) : Piece(color) {}
    std::string getTopLine() const override {
        return "  ^+^  ";
    }
    std::string getMiddleLine() const override {
        return "  )|(  ";
    }
    std::string getBottomLine() const override {
        return "  ===  ";
    }
};

#endif // PIECE_H
