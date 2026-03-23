#pragma once
#include "engine/pieces/Piece.h"
#include "engine/Types.h"
#include <memory>
#include <array>

// Forward declaration — avoids including Piece.h here
class Piece;

class Board {
public:
    Board();

    void resetBoard();
    bool movePiece(Coords from, Coords to);

    // Returns raw pointer — caller cannot own or delete it
    const Piece* getPiece(Coords pos) const;

    Color getCurrentTurn() const { return m_currentTurn; }

private:
    // 8x8 grid. [row][col]. nullptr means empty square.
    std::array<std::array<std::unique_ptr<Piece>, 8>, 8> m_grid;

    Color m_currentTurn;
};