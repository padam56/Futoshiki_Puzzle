## Futoshiki Puzzle Solver - Two Approaches
This project presents two implementations of a Futoshiki Puzzle Solver in C++, both using backtracking algorithms but with different 
approaches to parallelization and code structure.

## Overview
Both implementations solve Futoshiki puzzles of any size, respecting inequality constraints between cells. The key difference lies in their approach to parallelization and code organization.

## Key Features
Both solvers:
Solve Futoshiki puzzles
Support inequality constraints
Provide execution time feedback
Handle puzzles of variable sizes

Differences:
First implementation:
Utilizes OpenMP for parallel processing

Second implementation:
More modular code structure
Prepared for future parallelization implementation

## Files
First implementation:
futoshiki.h: Header file declaring the FutoshikiSolver class
futoshiki.cpp: Implementation of the FutoshikiSolver class
main.cpp: Main program to run the solver

Second implementation:
constraint.h/cpp: Defines and implements the Constraint class
matrix.h/cpp: Defines and implements the Matrix class
solver.h/cpp: Implements the solving algorithm
fileio.h/cpp: Handles file input/output operations
main.cpp: Main program to run the solver

## Usage
First implementation (with OpenMP):
text
g++ -o futoshiki_puzzle_omp futoshiki.cpp main.cpp -fopenmp
./futoshiki_puzzle_omp <input_file>

Second implementation:
text
g++ -o futoshiki_puzzle main.cpp constraint.cpp matrix.cpp solver.cpp fileio.cpp
./futoshiki_puzzle <input_file>

## Input File Format
Both implementations use the same input format:
First line: Size of the puzzle
Next lines: Puzzle matrix (-1 for empty cells)
Remaining lines: Inequality constraints
The second implementation specifies the constraint format as (x1 y1 x2 y2).

## Output
Both implementations:
Display the initial puzzle
Show the solved puzzle (if solvable)
Report solution time in microseconds

## Algorithm
First implementation: Uses backtracking with OpenMP tasks for parallel exploration of the solution space.
Second implementation: Uses backtracking to explore the solution space, checking row, column, and inequality constraints.

## Error Handling
Both implementations handle file opening errors and invalid inputs. The second implementation additionally checks for invalid constraint formats and provides more informative error messages.

## Notes
Performance may vary based on puzzle complexity and available CPU cores for both implementations.
Both assume valid input constraints.
The first implementation actively uses OpenMP for parallelization, while the second is structured to allow for future parallel implementation.
These two approaches offer different trade-offs between immediate parallel processing and code modularity, catering to different use cases and future development possibilities.
