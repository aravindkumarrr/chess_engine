#pragma once
#include "engine/Board.h"
#include "engine/Types.h"
#include <SFML/Graphics.hpp>
#include <optional>

class InputHandler {
public:
    // Call this every time a MouseButtonPressed event fires
    void handleClick(const sf::Vector2i& pixelPos, Board& board);

    // Returns the currently selected square (for Renderer to highlight it)
    std::optional<Coords> getSelectedSquare() const;

private:
    std::optional<Coords> m_selected; // nullopt = nothing selected

    // Converts pixel (x, y) → board Coords (col, row)
    // Returns nullopt if click is outside the board
    std::optional<Coords> pixelToCoords(const sf::Vector2i& pixelPos) const;

    static constexpr int TILE_SIZE = 100; // 800px window / 8 tiles
};
