#ifndef PIECE_H
#define PIECE_H

#include <cstdint>
#include <string>

enum PieceColor : uint8_t {
    WHITE = 0,
    BLACK
};

class Board;

class Piece {
public:
    Piece(PieceColor color) : color(color) {}
    virtual ~Piece() = default;
    virtual std::string getTopLine() const = 0;
    virtual std::string getMiddleLine() const = 0;
    virtual std::string getBottomLine() const = 0;
    PieceColor getColor() const { return color; }
    virtual bool isMoveValid(int fromRow, int fromCol, int toRow, int toCol, const Board& board) const = 0;
    virtual void setMoved() {};
    virtual bool getMoved() const { return false; }

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

    bool isMoveValid(int fromRow, int fromCol, int toRow, int toCol, const Board& board) const override;
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

    bool isMoveValid(int fromRow, int fromCol, int toRow, int toCol, const Board& board) const override;
    bool getMoved() const override { return moved; }
    void setMoved() override { moved = true; }

private:
    bool moved { false };
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

    bool isMoveValid(int fromRow, int fromCol, int toRow, int toCol, const Board& board) const override;
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

    bool isMoveValid(int fromRow, int fromCol, int toRow, int toCol, const Board& board) const override;
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

    bool isMoveValid(int fromRow, int fromCol, int toRow, int toCol, const Board& board) const override;
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

    bool isMoveValid(int fromRow, int fromCol, int toRow, int toCol, const Board& board) const override;
    bool getMoved() const override { return moved; }
    void setMoved() override{ moved = true; }

private:
    bool moved { false };
};

#endif // PIECE_H
