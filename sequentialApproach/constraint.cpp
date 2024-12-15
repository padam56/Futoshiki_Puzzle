#include "constraint.h"
#include "matrix.h"

Constraint::Constraint(int x1, int y1, int x2, int y2) 
    : start(x1, y1), end(x2, y2) {}

bool Constraint::isSatisfied(const Matrix& matrix) const {
    int startValue = matrix.getValue(start.first, start.second);
    int endValue = matrix.getValue(end.first, end.second);
    
    if (startValue == -1 || endValue == -1) {
        return true;  // Not yet violated
    }
    
    return startValue > endValue;
}