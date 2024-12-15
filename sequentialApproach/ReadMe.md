## Overview
This project implements a Futoshiki Puzzle Solver in C++ using a backtracking algorithm. It solves Futoshiki puzzles of any size, respecting inequality constraints between cells.

## Key Features
Solves Futoshiki puzzles
Supports inequality constraints
Provides execution time feedback
Handles puzzles of variable sizes

## Files
constraint.h/cpp: Defines and implements the Constraint class
matrix.h/cpp: Defines and implements the Matrix class
solver.h/cpp: Implements the solving algorithm
fileio.h/cpp: Handles file input/output operations
main.cpp: Main program to run the solver

## Usage
Compile:
g++ -o futoshiki_puzzle main.cpp constraint.cpp matrix.cpp solver.cpp fileio.cpp

Run with an input file:
./futoshiki_puzzle <input_file>

## Input File Format
First line: Size of the puzzle
Next lines: Puzzle matrix (-1 for empty cells)
Remaining lines: Inequality constraints (x1 y1 x2 y2 format)

## Output
Displays initial puzzle
Shows solved puzzle (if solvable)
Reports solution time in microseconds

## Algorithm
Uses backtracking to explore the solution space, checking row, column, and inequality constraints.

## Error Handling
Gracefully handles file opening errors
Checks for invalid constraint formats
Provides informative error messages

## Notes
Performance may vary based on puzzle complexity
Assumes valid input constraints
Does not currently use OpenMP for parallelization, but the structure allows for future implementation