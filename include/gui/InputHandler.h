#pragma once

#include "engine/Types.h"
#include <optional>

class Board;

class InputHandler {
public:
    InputHandler();

    // Call this when a mouse click occurs
    void handleClick(int pixelX, int pixelY, Board& board);

    // Returns selected square if one is active
    bool hasSelection() const;
    Coords getSelection() const;

    void clearSelection();

private:
    std::optional<Coords> m_selectedSquare;

    // Converts pixel position to board coordinate
    Coords pixelToBoard(int pixelX, int pixelY) const;

    static const int TILE_SIZE = 100;
};