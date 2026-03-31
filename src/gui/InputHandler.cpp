#include "gui/InputHandler.h"
#include "engine/pieces/Piece.h"  // needed to call getColor() and getType()
#include <iostream>

std::optional<Coords> InputHandler::pixelToCoords(const sf::Vector2i& pixelPos) const {
    if (pixelPos.x < 0 || pixelPos.x >= 800 ||
        pixelPos.y < 0 || pixelPos.y >= 800) {
        return std::nullopt;
    }
    int col = pixelPos.x / TILE_SIZE;
    int row = pixelPos.y / TILE_SIZE;
    return Coords{col, row};
}

void InputHandler::handleClick(const sf::Vector2i& pixelPos, Board& board) {
    auto clickedOpt = pixelToCoords(pixelPos);
    if (!clickedOpt) return;

    Coords clicked = *clickedOpt;

    if (!m_selected) {
        // First click — select a piece if it belongs to current player
        Piece* piece = board.getPieceAt(clicked);
        if (piece && piece->getColor() == board.getCurrentTurn()) {
            m_selected = clicked;
            std::cout << "Selected: (" << clicked.x << ", " << clicked.y << ")\n";
        }
    } else {
        Coords from = *m_selected;
        Piece* piece = board.getPieceAt(clicked);

        // Clicked your own piece — re-select it
        if (piece && piece->getColor() == board.getCurrentTurn()) {
            m_selected = clicked;
            std::cout << "Re-selected: (" << clicked.x << ", " << clicked.y << ")\n";
            return;
        }

        // Attempt move
        bool success = board.movePiece(from, clicked);
        if (success)
            std::cout << "Moved to: (" << clicked.x << ", " << clicked.y << ")\n";
        else
            std::cout << "Illegal move, deselecting.\n";

        m_selected = std::nullopt;
    }
}

std::optional<Coords> InputHandler::getSelectedSquare() const {
    return m_selected;
}