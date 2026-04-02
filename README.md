## 🛠 Building and Running the Project

This project uses **CMake** as the build system and **SFML 3.0** for graphics. 

### 1. Prerequisites
- **C++ Compiler**: Supporting C++17 or higher (GCC, Clang, or MSVC).
- **CMake**: Version 3.10 or higher.
- **SFML 3.0**: Ensure SFML is installed and added to your system's `PATH`.

### 2. Build and Run Commands

**Important:** The engine requires the `assets/` directory to be in the same folder as the final executable to load textures and fonts properly.

**For Linux / macOS:**
```bash
cd chess_engine
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build .
./ChessEngine
