Project: Rubik’s Cube Solver (C++)

Setup:
- Using CMake + MinGW (GCC 15)
- Folder structure:
  src/
    cube/
    solver/
    main.cpp
  build/

Commands:
- Build: cmake --build .
- Run: ./cube.exe

Progress:
- Setup complete
- Completed the major functions in the cube.h and cube.cpp files
- Structured RubiksCube3dArray class and Implemented all moves
- Tested all moves in 3D aray representation
- Implemented 1D array representation
- Structured and Implemented bitboard representation
- Implemented and Tested Unordered Map for all representations
- Implemented and Tested the generic DFS, BFS solver
- Implemented and Tested the generic IDDFS solver

- Created Dummy Pattern Database with h=0
- Structured, Implemented and Tested the IDA* Solver with h=0

- Structured and Implemented Nibble Array
- Structured and Implemented the Pattern Database
- Added getCornerIndex and getCornerOrientation in RubiksCube base class
- Added Permutation Indexer and math utility functions
- Added Corner Pattern Database
- Next : Create the Corner Database Maker using BFS

Goals:
- Multiple cube representations
- Multiple solvers
- Benchmark performance