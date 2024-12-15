#include "matrix.h"
#include "constraint.h"
#include "solver.h"
#include "fileio.h"
#include <iostream>
#include <chrono>

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    std::string filename(argv[1]);
    
    try {
        Matrix matrix = FileIO::readMatrix(filename);
        std::vector<Constraint> constraints = FileIO::readConstraints(filename);

        std::cout << "Initial Matrix:" << std::endl;
        matrix.print();

        Solver solver(matrix, constraints);

        auto t1 = std::chrono::high_resolution_clock::now();
        bool solved = solver.solvePuzzle();
        auto t2 = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
        std::cout << "Duration in microseconds: " << duration << std::endl;

        if (solved) {
            std::cout << "Puzzle solved successfully!" << std::endl;
            std::cout << "Solution:" << std::endl;
            solver.getResult().print();
        } else {
            std::cout << "No solution found." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
