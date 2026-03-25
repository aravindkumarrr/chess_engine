#include "engine/pieces/Queen.h"

std::vector<Coords> Queen::getPseudoLegalMoves(Coords from) const {
    std::vector<Coords> moves;

    // 8 directions: straight + diagonal combined
    int dirs[8][2] = {
        {0,-1}, {0,1}, {-1,0}, {1,0},   // Rook directions
        {-1,-1}, {1,-1}, {-1,1}, {1,1}  // Bishop directions
    };

    for (auto& dir : dirs) {
        int dx = dir[0];
        int dy = dir[1];

        for (int step = 1; step < 8; step++) {
            int nx = from.x + dx * step;
            int ny = from.y + dy * step;

            if (nx < 0 || nx > 7 || ny < 0 || ny > 7) break;

            moves.push_back({nx, ny});
        }
    }

    return moves;
}