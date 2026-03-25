#pragma once

#include "engine/pieces/Piece.h"

class Knight : public Piece {
public:
    Knight(Color color)
        : Piece(color, PieceType::KNIGHT) {}

    std::vector<Coords> getPseudoLegalMoves(Coords from) const override;
};