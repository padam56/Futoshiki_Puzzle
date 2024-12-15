#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "omp.h"
#include "futoshiki.h"
#include <chrono>

FutoshikiSolver::FutoshikiSolver(const std::string& filename) 
    : matrix(nullptr), solutionFound(false), executionTime(0.0) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    file >> size;
    threshold = size / 2;
    
    readMatrix(file);
    getConstraints(file);
    file.close();
}

FutoshikiSolver::~FutoshikiSolver() {
    if (matrix) {
        for (int i = 0; i < size; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
}

void FutoshikiSolver::readMatrix(std::ifstream& file) {
    matrix = new int*[size];
    for (int i = 0; i < size; i++) {
        matrix[i] = new int[size];
        for (int j = 0; j < size; j++) {
            file >> matrix[i][j];
        }
    }
}

void FutoshikiSolver::getConstraints(std::ifstream& file) {
    std::string constraint;
    std::getline(file, constraint); // Clear the remaining newline
    while (std::getline(file, constraint)) {
        if (constraint.empty()) continue;
        
        std::stringstream ss(constraint);
        int val1, val2, val3, val4;
        ss >> val1 >> val2 >> val3 >> val4;
        constraints.push_back({{val1 - 1, val2 - 1}, {val3 - 1, val4 - 1}});
    }
}

bool FutoshikiSolver::solved() const {
    for (const auto& constraint : constraints) {
        if (matrix[constraint.first.first][constraint.first.second] <
            matrix[constraint.second.first][constraint.second.second]) {
            return false;
        }
    }

    std::vector<int> rows(size);
    std::vector<int> cols(size);
    
    for (int rc = 0; rc < size; rc++) {
        for (int s = 0; s < size; s++) {
            rows[s] = matrix[rc][s];
            cols[s] = matrix[s][rc];
        }

        std::sort(rows.begin(), rows.end());
        std::sort(cols.begin(), cols.end());

        if (rows[0] == -1 || cols[0] == -1) return false;

        for (int i = 0; i < size - 1; i++) {
            if (rows[i] == rows[i + 1] || cols[i] == cols[i + 1]) {
                return false;
            }
        }
    }
    return true;
}

bool FutoshikiSolver::canUseInRow(int currentRowIndex, int value) const {
    for (int i = 0; i < size; i++) {
        if (matrix[currentRowIndex][i] == value) return false;
    }
    return true;
}

bool FutoshikiSolver::canUseInColumn(int currentColIndex, int value) const {
    for (int i = 0; i < size; i++) {
        if (matrix[i][currentColIndex] == value) return false;
    }
    return true;
}

bool FutoshikiSolver::isSatisfyConstraints(int currentRow, int currentCol, int value) const {
    for (const auto& constraint : constraints) {
        if (currentRow == constraint.first.first && currentCol == constraint.first.second) {
            if (matrix[constraint.second.first][constraint.second.second] != -1 &&
                value < matrix[constraint.second.first][constraint.second.second]) {
                return false;
            }
        } else if (currentRow == constraint.second.first && currentCol == constraint.second.second) {
            if (matrix[constraint.first.first][constraint.first.second] != -1 &&
                value > matrix[constraint.first.first][constraint.first.second]) {
                return false;
            }
        }
    }
    return true;
}

bool FutoshikiSolver::isCurrentCellEmpty(int currentRow, int currentCol) const {
    return matrix[currentRow][currentCol] == -1;
}

bool FutoshikiSolver::doesSatisfyRules(int currentRow, int currentCol, int value) const {
    return canUseInRow(currentRow, value) &&
           canUseInColumn(currentCol, value) &&
           isSatisfyConstraints(currentRow, currentCol, value) &&
           isCurrentCellEmpty(currentRow, currentCol);
}

std::pair<int, int> FutoshikiSolver::findEmptyCell() const {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (matrix[i][j] == -1) return {i, j};
        }
    }
    return {-1, -1};
}

void FutoshikiSolver::solveRecursive() {
    auto emptyCell = findEmptyCell();
    int currentRow = emptyCell.first;
    int currentCol = emptyCell.second;

    if (currentRow == -1 && currentCol == -1) {
        if (solved()) {
            #pragma omp critical
            solutionFound = true; // Ensure only one thread sets this flag
        }
        return;
    }

    for (int value = 1; value <= size && !solutionFound; value++) {
        if (doesSatisfyRules(currentRow, currentCol, value)) {
            matrix[currentRow][currentCol] = value;

            #pragma omp task firstprivate(currentRow, currentCol, value)
            {
                solveRecursive();
            }

            #pragma omp taskwait // Wait for all child tasks at this level

            if (!solutionFound) {
                matrix[currentRow][currentCol] = -1; // Backtrack
            }
        }
    }
}

void FutoshikiSolver::solve() {
    auto start = std::chrono::high_resolution_clock::now();

    #pragma omp parallel
    {
        #pragma omp single
        {
            solveRecursive();
        }
    }

    auto end = std::chrono::high_resolution_clock::now();

    executionTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    if (!solutionFound) {
        std::cout << "No solution found!" << std::endl;
    }
}


double FutoshikiSolver::getExecutionTime() const {
    return executionTime.count();
}

void FutoshikiSolver::printMatrix() const {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}