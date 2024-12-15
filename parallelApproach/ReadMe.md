## Overview
This project implements a Futoshiki Puzzle Solver in C++ using a backtracking algorithm with OpenMP parallelization. It solves Futoshiki puzzles of any size, respecting inequality constraints between cells.

## Key Features
Solves Futoshiki puzzles
Supports inequality constraints
Utilizes OpenMP for parallel processing
Provides execution time feedback

## Files
futoshiki.h: Header file declaring the FutoshikiSolver class
futoshiki.cpp: Implementation of the FutoshikiSolver class
main.cpp: Main program to run the solver

## Usage
Compile with OpenMP support:

g++ -o futoshiki_puzzle futoshiki.cpp main.cpp -fopenmp

Run with an input file:

./futoshiki_puzzle <input_file>

## Input File Format
First line: Size of the puzzle
Next lines: Puzzle matrix (-1 for empty cells)
Remaining lines: Inequality constraints

## Output
Displays initial puzzle
Shows solved puzzle
Reports solution time in microseconds

## Algorithm
Uses backtracking with OpenMP tasks for parallel exploration of the solution space.

## Error Handling
Gracefully handles file opening errors and invalid inputs.

## Notes
Performance may vary based on puzzle complexity and available CPU cores
Assumes valid input constraints