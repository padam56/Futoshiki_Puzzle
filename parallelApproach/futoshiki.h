#ifndef FUTOSHIKI_H
#define FUTOSHIKI_H

#include <vector>
#include <utility>
#include <string>
#include <chrono>

class FutoshikiSolver {
public:
    FutoshikiSolver(const std::string& filename);
    ~FutoshikiSolver();
    void solve();
    double getExecutionTime() const;
    void printMatrix() const;

private:
    int** matrix;
    int size;
    int threshold;
    bool solutionFound;
    std::chrono::duration<double, std::micro> executionTime;
    std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> constraints;

    void readMatrix(std::ifstream& file);
    void getConstraints(std::ifstream& file);
    bool solved() const;
    bool canUseInRow(int currentRowIndex, int value) const;
    bool canUseInColumn(int currentColIndex, int value) const;
    bool isSatisfyConstraints(int currentRow, int currentCol, int value) const;
    bool isCurrentCellEmpty(int currentRow, int currentCol) const;
    bool doesSatisfyRules(int currentRow, int currentCol, int value) const;
    std::pair<int, int> findEmptyCell() const;
    void solveRecursive();
    void solveParallel();
    int** createMatrixCopy() const;
    void deleteMatrix(int** mat);
};

#endif