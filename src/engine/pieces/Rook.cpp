#include "engine/pieces/Rook.h"

std::vector<Coords> Rook::getPseudoLegalMoves(Coords from) const {
    std::vector<Coords> moves;

    // Four directions: up, down, left, right
    int dirs[4][2] = { {0,-1}, {0,1}, {-1,0}, {1,0} };

    for (auto& dir : dirs) {
        int dx = dir[0];
        int dy = dir[1];

        // Keep sliding until edge of board
        for (int step = 1; step < 8; step++) {
            int nx = from.x + dx * step;
            int ny = from.y + dy * step;

            if (nx < 0 || nx > 7 || ny < 0 || ny > 7) break;

            moves.push_back({nx, ny});
        }
    }

    return moves;
}