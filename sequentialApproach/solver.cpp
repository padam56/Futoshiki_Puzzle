#include "solver.h"
#include <algorithm>

Solver::Solver(const Matrix& initial, const std::vector<Constraint>& constraints)
    : matrix(initial), constraints(constraints) {}

bool Solver::doesSatisfyRules(int row, int col, int value) const {
    // Check row
    for (int i = 0; i < matrix.getSize(); ++i) {
        if (matrix.getValue(row, i) == value) {
            return false;
        }
    }

    // Check column
    for (int i = 0; i < matrix.getSize(); ++i) {
        if (matrix.getValue(i, col) == value) {
            return false;
        }
    }

    // Check constraints
    Matrix tempMatrix = matrix;
    tempMatrix.setValue(row, col, value);
    for (const auto& constraint : constraints) {
        if (!constraint.isSatisfied(tempMatrix)) {
            return false;
        }
    }

    return true;
}

bool Solver::solve() {
    if (matrix.isFull()) {
        return true;
    }

    auto [row, col] = matrix.findEmptyCell();
    
    for (int value = 1; value <= matrix.getSize(); ++value) {
        if (doesSatisfyRules(row, col, value)) {
            matrix.setValue(row, col, value);
            
            if (solve()) {
                return true;
            }
            
            matrix.setValue(row, col, -1);  // Backtrack
        }
    }
    
    return false;
}

bool Solver::solvePuzzle() {
    return solve();
}

const Matrix& Solver::getResult() const {
    return matrix;
}