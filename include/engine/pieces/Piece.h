#pragma once

#include "engine/Types.h"
#include <vector>

class Piece {
public:
    Piece(Color color, PieceType type)
        : m_color(color), m_type(type) {}

    virtual ~Piece() = default;

    // Every piece must implement this
    virtual std::vector<Coords> getPseudoLegalMoves(Coords from) const = 0;

    Color getColor()     const { return m_color; }
    PieceType getType()  const { return m_type;  }

private:
    Color m_color;
    PieceType m_type;
};