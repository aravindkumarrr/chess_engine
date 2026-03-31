#include "engine/Board.h"
#include "gui/Renderer.h"
#include "gui/InputHandler.h"

int main() {
    Board board;
    board.resetBoard();

    Renderer renderer;
    renderer.initialize();
    InputHandler input;

    AppState mode = renderer.drawStartScreen();
    if (!renderer.isWindowOpen()) return 0;
    if (mode == AppState::USER_VS_ENGINE) {
        // hand off to your partner's code here
        return 0;
    }

    sf::RenderWindow& window = renderer.getWindow();

    while (window.isOpen()) {
        while (const std::optional<sf::Event> event = window.pollEvent()) {

            // Window close button
            if (event->is<sf::Event::Closed>())
                window.close();

            // Left mouse click
            if (const auto* mouseClick = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mouseClick->button == sf::Mouse::Button::Left) {
                    sf::Vector2i clickPos(mouseClick->position.x, mouseClick->position.y);
                    input.handleClick(clickPos, board);
                }
            }
        }

        renderer.clear();
        renderer.drawBoard();
        renderer.drawPieces(board);
        renderer.highlightSquare(input.getSelectedSquare());
        renderer.display();
    }

    return 0;
}