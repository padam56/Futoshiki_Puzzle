#pragma once
#include <utility>

class Matrix;

class Constraint {
private:
    std::pair<int, int> start;
    std::pair<int, int> end;

public:
    Constraint(int x1, int y1, int x2, int y2);
    bool isSatisfied(const Matrix& matrix) const;
};