#pragma once
#include <vector>
#include <utility>

class Matrix {
private:
    std::vector<std::vector<int>> data;
    int size;

public:
    Matrix(int size);
    void setValue(int row, int col, int value);
    int getValue(int row, int col) const;
    int getSize() const;
    bool isEmpty(int row, int col) const;
    std::pair<int, int> findEmptyCell() const;
    bool isFull() const;
    void print() const;
};