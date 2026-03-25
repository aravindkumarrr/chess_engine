#pragma once

#include "engine/pieces/Piece.h"

class Queen : public Piece {
public:
    Queen(Color color)
        : Piece(color, PieceType::QUEEN) {}

    std::vector<Coords> getPseudoLegalMoves(Coords from) const override;
};