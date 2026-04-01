cmake_minimum_required(VERSION 3.16)
project(ChessEngine)
set(CMAKE_CXX_STANDARD 17)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "C:/SFML-2.6.1/SFML-3.0.2/lib/cmake/SFML")
find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

add_executable(ChessEngine
    src/main.cpp
    src/engine/Board.cpp
    src/engine/pieces/Pawn.cpp
    src/engine/pieces/Rook.cpp
    src/engine/pieces/Knight.cpp
    src/engine/pieces/Bishop.cpp
    src/engine/pieces/Queen.cpp
    src/engine/pieces/King.cpp
    src/gui/Renderer.cpp
    src/gui/InputHandler.cpp
)

target_include_directories(ChessEngine PRIVATE include)

target_link_libraries(ChessEngine
    SFML::Graphics SFML::Window SFML::System
    opengl32 winmm gdi32
)

add_custom_command(TARGET ChessEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:ChessEngine>/assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        ${CMAKE_BINARY_DIR}/assets
)