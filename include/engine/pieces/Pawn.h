#pragma once

#include "engine/pieces/Piece.h"

class Pawn : public Piece {
public:
    Pawn(Color color)
        : Piece(color, PieceType::PAWN) {}

    std::vector<Coords> getPseudoLegalMoves(Coords from) const override;
};