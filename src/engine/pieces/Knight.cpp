#include "engine/pieces/Knight.h"

std::vector<Coords> Knight::getPseudoLegalMoves(Coords from) const {
    std::vector<Coords> moves;

    // All 8 possible L-shaped jumps
    int jumps[8][2] = {
        {-2, -1}, {-2, 1},
        { 2, -1}, { 2, 1},
        {-1, -2}, { 1, -2},
        {-1,  2}, { 1,  2}
    };

    for (auto& jump : jumps) {
        int nx = from.x + jump[0];
        int ny = from.y + jump[1];

        if (nx >= 0 && nx < 8 && ny >= 0 && ny < 8)
            moves.push_back({nx, ny});
    }

    return moves;
}