#include "gui/Renderer.h"
#include "engine/Board.h"
#include "engine/pieces/Piece.h"

Renderer::Renderer()
    : m_window(sf::VideoMode({WINDOW_SIZE, WINDOW_SIZE}), "Chess Engine"),
      m_boardTextureLoaded(false) {
}

bool Renderer::initialize() {
    loadTextures();
    return true;
}

bool Renderer::isWindowOpen() const {
    return m_window.isOpen();
}

void Renderer::handleEvents() {
    while (const std::optional<sf::Event> event = m_window.pollEvent()) {
        if (event->is<sf::Event::Closed>())
            m_window.close();
    }
}

void Renderer::clear() {
    m_window.clear();
}

void Renderer::display() {
    m_window.display();
}

void Renderer::drawBoard() {
    if (m_boardTextureLoaded) {
        sf::Sprite boardSprite(m_boardTexture);
        m_window.draw(boardSprite);
        return;
    }

    // Fallback: draw colored rectangles
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            sf::RectangleShape tile(sf::Vector2f(TILE_SIZE, TILE_SIZE));
            tile.setPosition(sf::Vector2f(col * TILE_SIZE, row * TILE_SIZE));

            if ((row + col) % 2 == 0)
                tile.setFillColor(sf::Color(240, 217, 181)); // light
            else
                tile.setFillColor(sf::Color(181, 136, 99));  // dark

            m_window.draw(tile);
        }
    }
}

void Renderer::drawPieces(const Board& board) {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            const Piece* piece = board.getPiece({col, row});
            if (!piece) continue;

            std::string key = makeKey(piece->getColor(), piece->getType());

            if (m_pieceTextures.count(key)) {
                sf::Sprite sprite(m_pieceTextures[key]);
                float scale = (float)TILE_SIZE / 150.f;
                sprite.setScale(sf::Vector2f(scale, scale));
                sprite.setPosition(sf::Vector2f(col * TILE_SIZE, row * TILE_SIZE));
                m_window.draw(sprite);
            }
        }
    }
}

void Renderer::loadTextures() {

    if (m_boardTexture.loadFromFile("assets/board.png"))
        m_boardTextureLoaded = true;
    else
        printf("FAILED to load board texture\n");

    std::vector<std::pair<Color, std::string>> colors = {
        { Color::WHITE, "w" },
        { Color::BLACK, "b" }
    };
    std::vector<std::pair<PieceType, std::string>> types = {
        { PieceType::PAWN,   "pawn"   },
        { PieceType::ROOK,   "rook"   },
        { PieceType::KNIGHT, "knight" },
        { PieceType::BISHOP, "bishop" },
        { PieceType::QUEEN,  "queen"  },
        { PieceType::KING,   "king"   }
    };

    for (auto& [color, colorStr] : colors) {
        for (auto& [type, typeStr] : types) {
            std::string filename = "assets/" + colorStr + "_" + typeStr + ".png";
            std::string key = makeKey(color, type);

            sf::Texture texture;
            if (texture.loadFromFile(filename))
                m_pieceTextures[key] = std::move(texture);
        }
    }
}
void Renderer::highlightSquare(std::optional<Coords> square) {
    if (!square) return; // nothing selected, draw nothing

    sf::RectangleShape highlight(sf::Vector2f(TILE_SIZE, TILE_SIZE));
    highlight.setFillColor(sf::Color(0, 255, 0, 100)); // semi-transparent green
    highlight.setPosition(
        sf::Vector2f(square->x * TILE_SIZE, square->y * TILE_SIZE)
    );
    m_window.draw(highlight);
}

std::string Renderer::makeKey(Color color, PieceType type) const {
    std::string colorStr = (color == Color::WHITE) ? "WHITE" : "BLACK";
    std::string typeStr;
    switch (type) {
        case PieceType::PAWN:   typeStr = "PAWN";   break;
        case PieceType::ROOK:   typeStr = "ROOK";   break;
        case PieceType::KNIGHT: typeStr = "KNIGHT"; break;
        case PieceType::BISHOP: typeStr = "BISHOP"; break;
        case PieceType::QUEEN:  typeStr = "QUEEN";  break;
        case PieceType::KING:   typeStr = "KING";   break;
    }
    return colorStr + "_" + typeStr;
}