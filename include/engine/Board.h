#pragma once
#include "engine/Types.h"
#include "engine/pieces/Piece.h"   // needed for unique_ptr<Piece> destruction
#include <memory>
#include <array>

class Board {
public:
    Board();

    void resetBoard();
    bool movePiece(Coords from, Coords to);

    const Piece* getPiece(Coords pos) const;
    Piece* getPieceAt(const Coords& c) const;

    Color getCurrentTurn() const { return m_currentTurn; }

private:
    std::array<std::array<std::unique_ptr<Piece>, 8>, 8> m_grid;
    Color m_currentTurn;
};