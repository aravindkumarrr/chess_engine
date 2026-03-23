#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include "engine/Types.h"

class Board;

class Renderer {
public:
    Renderer();

    bool initialize();
    bool isWindowOpen() const;

    void handleEvents();
    void drawBoard();
    void drawPieces(const Board& board);
    void display();
    void clear();

private:
    sf::RenderWindow m_window;

    bool m_boardTextureLoaded;
    sf::Texture m_boardTexture;

    // Store textures only — sprites created on the fly in SFML 3
    std::map<std::string, sf::Texture> m_pieceTextures;

    void loadTextures();
    std::string makeKey(Color color, PieceType type) const;

    static const int WINDOW_SIZE = 800;
    static const int TILE_SIZE   = 100;
};