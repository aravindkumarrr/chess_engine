#pragma once

#include "engine/pieces/Piece.h"

class Rook : public Piece {
public:
    Rook(Color color)
        : Piece(color, PieceType::ROOK) {}

    std::vector<Coords> getPseudoLegalMoves(Coords from) const override;
};