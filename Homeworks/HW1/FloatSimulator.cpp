#include "FloatSimulator.hpp"
#include <cmath>
#include <sstream>
#include <iomanip>
#include <algorithm>

FloatSimulator::FloatSimulator() : sign(0), mantissa(23, 0), exponent(8, 0) {}

FloatSimulator::FloatSimulator(unsigned int sign, const std::vector<unsigned int>& mantBitfield, const std::vector<unsigned int>& expBitfield)
    : sign(sign), mantissa(mantBitfield), exponent(expBitfield) {
    // No need to modify the exponent here, it should be correct from the main function
}

FloatSimulator::FloatSimulator(const FloatSimulator& other)
    : sign(other.sign), mantissa(other.mantissa), exponent(other.exponent) {}

FloatSimulator::~FloatSimulator() {}

FloatSimulator::FloatSimulator(unsigned int totalBits, unsigned int exponentBits)
    : totalBits(totalBits), exponentBits(exponentBits), mantissaBits(totalBits - exponentBits - 1) {
    sign = 0;
    mantissa.resize(mantissaBits, 0);
    exponent.resize(exponentBits, 0);
    bias = (1 << (exponentBits - 1)) - 1;
}

void FloatSimulator::incrementByOne() {
    bool carry = true;
    for (int i = mantissa.size() - 1; i >= 0 && carry; --i) {
        if (mantissa[i] == 0) {
            mantissa[i] = 1;
            carry = false;
        } else {
            mantissa[i] = 0;
        }
    }

    // If carry is still true, we need to increment the exponent
    if (carry) {
        carry = true;
        for (int i = 0; i < exponent.size() && carry; ++i) {
            if (exponent[i] == 0) {
                exponent[i] = 1;
                carry = false;
            } else {
                exponent[i] = 0;
            }
        }

        // Check for overflow
        if (carry) {
            std::cerr << "Warning: Exponent overflow, resetting mantissa and exponent." << std::endl;
            std::fill(exponent.begin(), exponent.end(), 1); // Set max exponent
            std::fill(mantissa.begin(), mantissa.end(), 1); // Set max mantissa
        } else {
            std::fill(mantissa.begin(), mantissa.end(), 0); // Reset mantissa
        }
    }
}


unsigned int FloatSimulator::getExponentValue() const {
    unsigned int value = 0;
    for (size_t i = 0; i < exponent.size(); ++i) {
        value = (value << 1) | exponent[i];
    }
    return value; // Return the biased exponent
}

double FloatSimulator::getMantissaValue() const {
    double value = 1.0; // Implicit leading 1 for normalized numbers
    for (size_t i = 0; i < mantissa.size(); ++i) {
        if (mantissa[i] == 1) {
            value += std::pow(2, -(i + 1)); // Add bits after the decimal point
        }
    }
    return value;
}

APNumber FloatSimulator::toAPNumber() const {
    // Calculate the exponent value
    int expValue = 0;
    for (int i = 0; i < 8; ++i) {
        expValue = (expValue << 1) | exponent[i];
    }

    int unbiasedExp = expValue - 127; // Remove the bias for single-precision floats

    // Calculate the mantissa value
    double mantissaValue = 1.0;
    for (int i = 0; i < 23; ++i) {
        if (mantissa[i]) {
            mantissaValue += std::pow(2, -(i + 1));
        }
    }

    // Calculate the final floating-point value
    double value = mantissaValue * std::pow(2, unbiasedExp);
    if (sign) {
        value = -value; // Apply the sign if necessary
    }

    // Convert to a high precision string
    std::ostringstream oss;
    oss << std::setprecision(20) << value;
    return APNumber(oss.str());
}