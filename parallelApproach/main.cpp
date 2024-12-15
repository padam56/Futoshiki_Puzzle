#include <iostream>
#include <iomanip>
#include "futoshiki.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    try {
        FutoshikiSolver solver(argv[1]);
        
        std::cout << "Initial puzzle:" << std::endl;
        solver.printMatrix();
        
        solver.solve();
        
        std::cout << "\nSolved puzzle:" << std::endl;
        solver.printMatrix();
        std::cout << "Solution time: " << std::fixed << std::setprecision(0) 
          << solver.getExecutionTime() << " microseconds" << std::endl;
        
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}