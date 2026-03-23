#include "engine/Board.h"
#include "gui/Renderer.h"

int main() {
    Board board;
    Renderer renderer;

    renderer.initialize();

    while (renderer.isWindowOpen()) {
        renderer.handleEvents();

        renderer.clear();
        renderer.drawBoard();
        renderer.drawPieces(board);
        renderer.display();
    }

    return 0;
}