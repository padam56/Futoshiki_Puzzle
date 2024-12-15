#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include "FloatSimulator.hpp"
#include "APNumber.hpp"

int main() {
    std::cout << std::setprecision(10) << std::fixed;

    for (int exp = 10; exp <= 15; exp++) {
        std::cout << "Exponent: " << exp << std::endl;

        // Initialize FloatSimulator with exponent 'exp'
        std::vector<unsigned int> mantissa(23, 0);
        std::vector<unsigned int> exponent(8, 0);
        unsigned int expValue = exp + 127;
        for (int i = 0; i < 8; ++i) {
            exponent[i] = (expValue >> (7-i)) & 1;
        }
        unsigned int sign = 0;
        FloatSimulator fs(sign, mantissa, exponent);

        double mantissaValue = 1.0;
        for (int i = 0; i < 23; ++i) {
            if (mantissa[i]) {
                mantissaValue += std::pow(2, -(i + 1));
            }
        }

        // Get current value
        APNumber current = fs.toAPNumber();

        // Get next value by incrementing the value by 1
        fs.incrementByOne();
        APNumber next = fs.toAPNumber();

        // Display spacing for exponents 
        APNumber spacing = next - current;
        std::cout << "Exponent " << exp << ": Spacing = " << spacing.toScientificString(15) << std::endl;

        std::cout << std::endl;
    }
    return 0;
}