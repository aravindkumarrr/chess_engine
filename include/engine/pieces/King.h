#pragma once

#include "engine/pieces/Piece.h"

class King : public Piece {
public:
    King(Color color)
        : Piece(color, PieceType::KING) {}

    std::vector<Coords> getPseudoLegalMoves(Coords from) const override;
};