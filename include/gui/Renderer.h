#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <optional>
#include "engine/Types.h"

enum class AppState {
    START_SCREEN,
    USER_VS_USER,
    USER_VS_ENGINE
};

class Board;

class Renderer {
public:
    Renderer();
    AppState drawStartScreen();
    bool initialize();
    bool isWindowOpen() const;

    void handleEvents();
    void drawBoard();
    void drawPieces(const Board& board);
    void highlightSquare(std::optional<Coords> square); // NEW
    void display();
    void clear();

    sf::RenderWindow& getWindow() { return m_window; } // NEW

private:
    sf::RenderWindow m_window;

    bool m_boardTextureLoaded;
    sf::Texture m_boardTexture;

    std::map<std::string, sf::Texture> m_pieceTextures;

    void loadTextures();
    std::string makeKey(Color color, PieceType type) const;

    static const int WINDOW_SIZE = 800;
    static const int TILE_SIZE   = 100;
};