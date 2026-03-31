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

AppState Renderer::drawStartScreen() {
    const float centerX  = WINDOW_SIZE / 2.f;
    const float btnWidth = 260.f, btnHeight = 60.f;
    const float btn1Y    = 380.f, btn2Y = 470.f;

    sf::RectangleShape btn1({btnWidth, btnHeight});
    btn1.setOrigin({btnWidth / 2.f, btnHeight / 2.f});
    btn1.setPosition({centerX, btn1Y});
    btn1.setFillColor(sf::Color(100, 180, 100));

    sf::RectangleShape btn2({btnWidth, btnHeight});
    btn2.setOrigin({btnWidth / 2.f, btnHeight / 2.f});
    btn2.setPosition({centerX, btn2Y});
    btn2.setFillColor(sf::Color(100, 130, 200));

    sf::Font font;
    bool fontLoaded = font.openFromFile("assets/font.ttf");

    while (m_window.isOpen()) {
        while (const std::optional<sf::Event> event = m_window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                m_window.close();
                return AppState::START_SCREEN;
            }

            if (const auto* click = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (click->button == sf::Mouse::Button::Left) {
                    sf::Vector2f mouse(click->position.x, click->position.y);
                    if (btn1.getGlobalBounds().contains(mouse))
                        return AppState::USER_VS_USER;
                    if (btn2.getGlobalBounds().contains(mouse))
                        return AppState::USER_VS_ENGINE;
                }
            }
        }

        m_window.clear(sf::Color(30, 30, 30));

        // Buttons first
        m_window.draw(btn1);
        m_window.draw(btn2);

        // Text on top
        if (fontLoaded) {
            sf::Text title(font, "Chess Engine", 52);
            title.setFillColor(sf::Color::White);
            auto tb = title.getLocalBounds();
            title.setOrigin({tb.size.x / 2.f, 0.f});
            title.setPosition({centerX, 180.f});
            m_window.draw(title);

            sf::Text label1(font, "User vs User", 26);
            label1.setFillColor(sf::Color::White);
            auto lb1 = label1.getLocalBounds();
            label1.setOrigin({lb1.size.x / 2.f, lb1.size.y / 2.f});
            label1.setPosition({centerX, btn1Y});
            m_window.draw(label1);

            sf::Text label2(font, "User vs Engine", 26);
            label2.setFillColor(sf::Color::White);
            auto lb2 = label2.getLocalBounds();
            label2.setOrigin({lb2.size.x / 2.f, lb2.size.y / 2.f});
            label2.setPosition({centerX, btn2Y});
            m_window.draw(label2);
        }

        m_window.display();
    }

    return AppState::START_SCREEN;
}