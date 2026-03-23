cmake_minimum_required(VERSION 3.16)
project(ChessEngine)

set(CMAKE_CXX_STANDARD 17)

# --- Tell CMake where to find SFML ---
set(SFML_DIR "C:/SFML-2.6.1/SFML-3.0.2/lib/cmake/SFML")
find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

# --- All source files ---
add_executable(ChessEngine
    src/main.cpp
    src/engine/Board.cpp
    src/engine/pieces/Pawn.cpp
    src/gui/Renderer.cpp
)

# --- So we can write #include "engine/Board.h" from anywhere ---
target_include_directories(ChessEngine PRIVATE include)

# --- Link SFML 3 ---
target_link_libraries(ChessEngine SFML::Graphics SFML::Window SFML::System)