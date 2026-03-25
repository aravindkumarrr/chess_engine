#include "engine/pieces/King.h"

std::vector<Coords> King::getPseudoLegalMoves(Coords from) const {
    std::vector<Coords> moves;

    // All 8 surrounding squares
    int dirs[8][2] = {
        {0,-1}, {0,1}, {-1,0}, {1,0},
        {-1,-1}, {1,-1}, {-1,1}, {1,1}
    };

    for (auto& dir : dirs) {
        int nx = from.x + dir[0];
        int ny = from.y + dir[1];

        if (nx >= 0 && nx < 8 && ny >= 0 && ny < 8)
            moves.push_back({nx, ny});
    }

    return moves;
}