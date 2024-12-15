#pragma once
#include "matrix.h"
#include "constraint.h"
#include <string>
#include <vector>

class FileIO {
public:
    static Matrix readMatrix(const std::string& filename);
    static std::vector<Constraint> readConstraints(const std::string& filename);
};