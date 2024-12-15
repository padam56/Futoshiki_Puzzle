#include "matrix.h"
#include <iostream>

Matrix::Matrix(int size) : size(size), data(size, std::vector<int>(size, -1)) {}

void Matrix::setValue(int row, int col, int value) {
    data[row][col] = value;
}

int Matrix::getValue(int row, int col) const {
    return data[row][col];
}

int Matrix::getSize() const {
    return size;
}

bool Matrix::isEmpty(int row, int col) const {
    return data[row][col] == -1;
}

std::pair<int, int> Matrix::findEmptyCell() const {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (isEmpty(i, j)) {
                return {i, j};
            }
        }
    }
    return {-1, -1};
}

bool Matrix::isFull() const {
    return findEmptyCell() == std::pair<int, int>(-1, -1);
}

void Matrix::print() const {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cout << data[i][j] << " ";
        }
        std::cout << std::endl;
    }
}