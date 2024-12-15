#pragma once
#include "matrix.h"
#include "constraint.h"
#include <vector>

class Solver {
private:
    Matrix matrix;
    std::vector<Constraint> constraints;

    bool doesSatisfyRules(int row, int col, int value) const;
    bool solve();

public:
    Solver(const Matrix& initial, const std::vector<Constraint>& constraints);
    bool solvePuzzle();
    const Matrix& getResult() const;
};