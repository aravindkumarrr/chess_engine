#include "engine/pieces/Bishop.h"

std::vector<Coords> Bishop::getPseudoLegalMoves(Coords from) const {
    std::vector<Coords> moves;

    // Four diagonal directions
    int dirs[4][2] = { {-1,-1}, {1,-1}, {-1,1}, {1,1} };

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