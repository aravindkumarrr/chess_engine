#pragma once

// Represents a square on the board, e.g. {3, 4}
struct Coords {
    int x; // column, 0 = leftmost
    int y; // row,    0 = topmost
};

enum class Color {
    WHITE,
    BLACK
};

enum class PieceType {
    PAWN,
    ROOK,
    KNIGHT,
    BISHOP,
    QUEEN,
    KING
};