#pragma once

#include "engine/pieces/Piece.h"

class Bishop : public Piece {
public:
    Bishop(Color color)
        : Piece(color, PieceType::BISHOP) {}

    std::vector<Coords> getPseudoLegalMoves(Coords from) const override;
};