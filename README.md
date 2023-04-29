# Maze Solver

Maze Solver is a simple program that generates a random maze and tries to find a solution using a stack-based algorithm.

## Usage

To use Maze Solver, simply download or clone the repository and compile the maze_solver.cpp file using a C++ compiler. Then run the executable to generate a random maze and see the solution path.

## Dependencies

Maze Solver requires a C++ compiler and the following libraries:

 - iostream
 - cstdlib
 - ctime
 - unistd.h

## How it Works

Maze Solver generates a random maze using a depth-first search algorithm, and then tries to find a solution using a stack-based algorithm. The algorithm works by starting at the entrance of the maze and exploring the adjacent cells, adding them to a stack if they are unexplored. When a dead end is reached, the algorithm backtracks to the previous cell on the stack and continues exploring.
