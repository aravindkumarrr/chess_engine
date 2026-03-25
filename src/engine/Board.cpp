#include "engine/Board.h"
#include "engine/pieces/Piece.h"
#include "engine/pieces/Pawn.h"
#include "engine/pieces/Rook.h"
#include "engine/pieces/Knight.h"
#include "engine/pieces/Bishop.h"
#include "engine/pieces/Queen.h"
#include "engine/pieces/King.h"

Board::Board() {
    m_currentTurn = Color::WHITE;
    resetBoard();
}

void Board::resetBoard() {
    // Clear the entire board first
    for (auto& row : m_grid)
        for (auto& cell : row)
            cell = nullptr;

    // Place black pawns on row 1
    for (int x = 0; x < 8; x++)
        m_grid[1][x] = std::make_unique<Pawn>(Color::BLACK);

    // Place white pawns on row 6
    for (int x = 0; x < 8; x++)
        m_grid[6][x] = std::make_unique<Pawn>(Color::WHITE);

    // Place rooks
    m_grid[0][0] = std::make_unique<Rook>(Color::BLACK);
    m_grid[0][7] = std::make_unique<Rook>(Color::BLACK);
    m_grid[7][0] = std::make_unique<Rook>(Color::WHITE);
    m_grid[7][7] = std::make_unique<Rook>(Color::WHITE);

    // Place knights
    m_grid[0][1] = std::make_unique<Knight>(Color::BLACK);
    m_grid[0][6] = std::make_unique<Knight>(Color::BLACK);
    m_grid[7][1] = std::make_unique<Knight>(Color::WHITE);
    m_grid[7][6] = std::make_unique<Knight>(Color::WHITE);

    // Place bishops
    m_grid[0][2] = std::make_unique<Bishop>(Color::BLACK);
    m_grid[0][5] = std::make_unique<Bishop>(Color::BLACK);
    m_grid[7][2] = std::make_unique<Bishop>(Color::WHITE);
    m_grid[7][5] = std::make_unique<Bishop>(Color::WHITE);

    // Place queens
    m_grid[0][3] = std::make_unique<Queen>(Color::BLACK);
    m_grid[7][3] = std::make_unique<Queen>(Color::WHITE);

    // Place kings
    m_grid[0][4] = std::make_unique<King>(Color::BLACK);
    m_grid[7][4] = std::make_unique<King>(Color::WHITE);
}

bool Board::movePiece(Coords from, Coords to) {
    // Check bounds
    if (from.x < 0 || from.x > 7 || from.y < 0 || from.y > 7) return false;
    if (to.x < 0   || to.x > 7   || to.y < 0   || to.y > 7)   return false;

    // No piece at source
    if (!m_grid[from.y][from.x]) return false;

    Piece* piece = m_grid[from.y][from.x].get();

    // Wrong player's turn
    if (piece->getColor() != m_currentTurn) return false;

    // Check if destination is in pseudo-legal moves
    std::vector<Coords> moves = piece->getPseudoLegalMoves(from);
    bool isValid = false;
    for (const Coords& move : moves) {
        if (move.x == to.x && move.y == to.y) {
            isValid = true;
            break;
        }
    }
    if (!isValid) return false;

    // Cannot capture your own piece
    if (m_grid[to.y][to.x] &&
        m_grid[to.y][to.x]->getColor() == m_currentTurn) return false;

    // Pawn specific: cannot move forward into an occupied square
    if (piece->getType() == PieceType::PAWN) {
        if (to.x == from.x && m_grid[to.y][to.x] != nullptr) return false;
        // Diagonal only valid if capturing an enemy
        if (to.x != from.x && m_grid[to.y][to.x] == nullptr) return false;
    }

    // Execute the move
    m_grid[to.y][to.x] = std::move(m_grid[from.y][from.x]);
    m_grid[from.y][from.x] = nullptr;

    // Switch turns
    m_currentTurn = (m_currentTurn == Color::WHITE) ? Color::BLACK : Color::WHITE;

    return true;
}

const Piece* Board::getPiece(Coords pos) const {
    return m_grid[pos.y][pos.x].get();
}