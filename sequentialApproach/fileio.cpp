#include "fileio.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

Matrix FileIO::readMatrix(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Unable to open file: " + filename);
    }

    int size;
    file >> size;

    Matrix matrix(size);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            int value;
            file >> value;
            matrix.setValue(i, j, value);
        }
    }

    return matrix;
}

std::vector<Constraint> FileIO::readConstraints(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Unable to open file: " + filename);
    }

    int size;
    file >> size;

    // Skip the matrix
    for (int i = 0; i < size * size; ++i) {
        int dummy;
        file >> dummy;
    }

    std::vector<Constraint> constraints;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        
        std::istringstream iss(line);
        int x1, y1, x2, y2;
        if (!(iss >> x1 >> y1 >> x2 >> y2)) {
            throw std::runtime_error("Invalid constraint format");
        }
        constraints.emplace_back(x1 - 1, y1 - 1, x2 - 1, y2 - 1);
    }

    return constraints;
}