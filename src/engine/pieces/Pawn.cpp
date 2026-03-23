#include "engine/pieces/Pawn.h"

std::vector<Coords> Pawn::getPseudoLegalMoves(Coords from) const {
    std::vector<Coords> moves;

    // White moves up (y decreases), Black moves down (y increases)
    int direction = (getColor() == Color::WHITE) ? -1 : 1;

    // --- Move forward 1 ---
    Coords oneStep = { from.x, from.y + direction };
    if (oneStep.y >= 0 && oneStep.y < 8) {
        moves.push_back(oneStep);
    }

    // --- Move forward 2 (only from starting row) ---
    int startRow = (getColor() == Color::WHITE) ? 6 : 1;
    if (from.y == startRow) {
        Coords twoStep = { from.x, from.y + (2 * direction) };
        moves.push_back(twoStep);
    }

    // --- Diagonal captures ---
    for (int dx : {-1, 1}) {
        Coords capture = { from.x + dx, from.y + direction };
        if (capture.x >= 0 && capture.x < 8 &&
            capture.y >= 0 && capture.y < 8) {
            moves.push_back(capture);
        }
    }

    return moves;
}