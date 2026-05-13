# 🎲 Rubik's Cube Solver

A high-performance **C++ implementation** of a Rubik's Cube solver using multiple algorithmic approaches and optimized cube representations.

## 🎯 Features

### Cube Representations
- **3D Array**: Traditional 3D representation for intuitive understanding
- **1D Array**: Memory-efficient linear representation
- **Bitboard**: Ultra-compact bit-level representation for performance

### Solving Algorithms
- **BFS (Breadth-First Search)**: Guaranteed shortest path solution
- **DFS (Depth-First Search)**: Memory-efficient exploration
- **IDA\* (Iterative Deepening A\*)**: Optimal solution with heuristics
- **IDDFS (Iterative Deepening Depth-First Search)**: Balance between optimality and memory usage

### Optimization
- **Pattern Database**: Precomputed heuristics for corner piece positions
- **Nibble Array**: Compact storage for permutation data
- **Permutation Indexing**: Efficient state space mapping

## 🚀 Getting Started

### Prerequisites
- **CMake** (3.10 or higher)
- **C++11 or higher** compiler (tested with GCC 15)
- **MinGW** (if on Windows)

### Build Instructions

```bash
# Clone the repository
git clone https://github.com/sachin9919/Rubics_cube_solver.git
cd Rubics_cube_solver

# Create and navigate to build directory
mkdir build
cd build

# Configure and build
cmake ..
cmake --build .

# Run the solver
./cube.exe
```

## 📁 Project Structure

```
src/
├── cube/                      # Cube representations
│   ├── RubiksCube.h/cpp       # Base cube interface
│   ├── RubiksCube3dArray.cpp  # 3D array representation
│   ├── RubiksCube1dArray.cpp  # 1D array representation
│   └── RubiksCubeBitboard.cpp # Bitboard representation
│
├── solver/                    # Solving algorithms
│   ├── BFSSolver.h            # Breadth-first search
│   ├── DFSSolver.h            # Depth-first search
│   ├── IDAStarSolver.h        # IDA* with heuristics
│   └── IDDFSSolver.h          # Iterative deepening DFS
│
├── PatternDatabase/           # Optimization & heuristics
│   ├── PatternDatabase.h/cpp  # Pattern database manager
│   ├── CornerPatternDatabase.h/cpp
│   ├── NibbleArray.h/cpp      # Compact data storage
│   ├── PermutationIndexer.h   # State space indexing
│   └── math.h/cpp            # Math utilities
│
└── main.cpp                   # Entry point
```

## 💡 How It Works

1. **Parse Input**: Accept a scrambled Rubik's Cube state
2. **Select Algorithm**: Choose from BFS, DFS, IDA*, or IDDFS
3. **Solve**: Compute the optimal or near-optimal solution sequence
4. **Output**: Return the sequence of moves to solve the cube

## 🔬 Development Progress

✅ Multiple cube representations implemented and tested  
✅ Generic solver algorithms (DFS, BFS, IDDFS)  
✅ IDA* solver with heuristic support  
✅ Corner pattern database infrastructure  
✅ Permutation indexing system  

🚧 Performance benchmarking  
🚧 Enhanced heuristics  

## 🎓 Algorithm Details

### IDA\* with Pattern Database
- Uses precomputed corner piece heuristics
- Employs iterative deepening for memory efficiency
- Achieves optimal solutions within practical time limits

### Cube State Representation
- **Corners**: 8 pieces × 3 orientations = 24 states per corner
- **Edges**: 12 pieces × 2 orientations = 24 states per edge
- **State Space**: ~4.3 × 10¹⁹ possible configurations

## 📊 Performance Notes

- **Bitboard representation**: Fastest for pure computation
- **1D Array**: Best memory/performance balance
- **3D Array**: Easiest to understand and debug
- **Pattern Database**: Enables faster solving with IDA*

## 🤝 Contributing

Feel free to fork, modify, and enhance this project!

## 📝 License

This project is open source. Check LICENSE file for details.

## 👤 Author

**Sachin** - Rubik's Cube Solver Development

---

**Happy Cubing!** 🎲✨
