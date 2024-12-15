#ifndef FLOAT_SIMULATOR_HPP
#define FLOAT_SIMULATOR_HPP

#include <vector>
#include "APNumber.hpp"

class FloatSimulator {
public:
    FloatSimulator();
    FloatSimulator(unsigned int sign, const std::vector<unsigned int>& mantBitfield, const std::vector<unsigned int>& expBitfield);
    FloatSimulator(const FloatSimulator& other);  // Declaration only
    virtual ~FloatSimulator(); 
    FloatSimulator(unsigned int totalBits, unsigned int exponentBits); // Declaration only

    
    void incrementByOne();
    APNumber toAPNumber() const;

protected:
    std::vector<unsigned int> mantissa;
    std::vector<unsigned int> exponent;
    unsigned int sign;

private:
    unsigned int totalBits;
    unsigned int exponentBits;
    unsigned int mantissaBits;
    unsigned int bias;
    void normalizeAndAdjustExponent();
    unsigned int getExponentValue() const;
    double getMantissaValue() const;
};

#endif // FLOAT_SIMULATOR_HPP
