#include "APNumber.hpp"
#include "StringHelper.hpp"
#include "FloatSimulator.hpp"
#include <stdexcept>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <iomanip>

APNumber::APNumber() : sign(true), isInfinity(false) {
    integerPart.push_back(0);
    decimalPart.push_back(0);
}


APNumber::APNumber(bool sign, bool isInf) : sign(sign), isInfinity(isInf) {}

APNumber::APNumber(const bool sign,
                   const std::vector<unsigned int>& intPart,
                   const std::vector<unsigned int>& decPart)
    : sign(sign), integerPart(intPart), decimalPart(decPart), isInfinity(false) {}

APNumber::APNumber(std::string sNum) : isInfinity(false) {
    sign = true;
    size_t decimalPos = sNum.find('.');
    std::string intString = (decimalPos == std::string::npos) ? sNum : sNum.substr(0, decimalPos);
    std::string decString = (decimalPos == std::string::npos) ? "" : sNum.substr(decimalPos + 1);

    if (intString.empty()) intString = "0";

    if (intString[0] == '-') {
        sign = false;
        intString = intString.substr(1);
    }

    for (auto it = intString.rbegin(); it != intString.rend(); ++it) {
        if (std::isdigit(*it)) {
            integerPart.push_back(*it - '0');
        }
    }

    for (char c : decString) {
        if (std::isdigit(c)) {
            decimalPart.push_back(c - '0');
        }
    }

    removeLeadingTrailingZeros();
}

APNumber::APNumber(const APNumber& rhs)
    : sign(rhs.sign), integerPart(rhs.integerPart), decimalPart(rhs.decimalPart), isInfinity(rhs.isInfinity) {}

APNumber::~APNumber() {}

void APNumber::setIntegerPart(const std::vector<unsigned int>& digits) {
    integerPart = digits;
}

void APNumber::setDecimalPart(const std::vector<unsigned int>& digits) {
    decimalPart = digits;
}

void APNumber::setSign(const bool& positive) {
    sign = positive;
}

std::vector<unsigned int> APNumber::getIntegerPart() const {
    return integerPart;
}

int APNumber::getNumIntegerDigits() const {
    return integerPart.size();
}

std::vector<unsigned int> APNumber::getDecimalPart() const {
    return decimalPart;
}

int APNumber::getNumDecimalDigits() const {
    return decimalPart.size();
}

bool APNumber::getSign() const {
    return sign;
}

void APNumber::removeLeadingTrailingZeros() {
    while (integerPart.size() > 1 && integerPart.back() == 0) {
        integerPart.pop_back();
    }
    while (!decimalPart.empty() && decimalPart.back() == 0) {
        decimalPart.pop_back();
    }
}

APNumber APNumber::pow(int exponent) const {
    if (exponent == 0) return APNumber("1");
    if (exponent < 0) throw std::runtime_error("Negative exponents not supported");
    
    APNumber result("1");
    APNumber base(*this);
    while (exponent > 0) {
        if (exponent & 1) result = result * base;
        base = base * base;
        exponent >>= 1;
    }
    return result;
}

double APNumber::toDouble() const {
    double result = 0.0;
    double factor = 1.0;
    for (auto it = integerPart.rbegin(); it != integerPart.rend(); ++it) {
        result += *it * factor;
        factor *= 10.0;
    }
    factor = 0.1;
    for (unsigned int digit : decimalPart) {
        result += digit * factor;
        factor *= 0.1;
    }
    return sign ? result : -result;
}

std::string APNumber::toScientificString(int precision) const {
    std::ostringstream oss;
    oss << std::scientific << std::setprecision(precision);
    
    // Combine integer and decimal parts
    std::vector<unsigned int> fullNumber = integerPart;
    fullNumber.insert(fullNumber.end(), decimalPart.begin(), decimalPart.end());
    
    // Find first non-zero digit
    int firstNonZero = 0;
    while (firstNonZero < fullNumber.size() && fullNumber[firstNonZero] == 0) {
        firstNonZero++;
    }
    
    if (firstNonZero == fullNumber.size()) {
        return "0.0e+00"; // Number is zero
    }
    
    // Calculate exponent
    int exponent = integerPart.size() - firstNonZero - 1;
    
    // Build mantissa string
    std::string mantissa;
    for (int i = firstNonZero; i < std::min(firstNonZero + precision + 1, (int)fullNumber.size()); ++i) {
        if (i == firstNonZero + 1) mantissa += ".";
        mantissa += std::to_string(fullNumber[i]);
    }
    
    // Pad with zeros if necessary
    while (mantissa.length() < precision + 2) mantissa += "0";
    
    oss << (sign ? "" : "-") << mantissa << "e" << (exponent >= 0 ? "+" : "-") << std::setfill('0') << std::setw(2) << std::abs(exponent);
    return oss.str();
}

APNumber APNumber::operator+(const APNumber& rhs) const {
    if (isInfinity || rhs.isInfinity) {
        if (isInfinity && rhs.isInfinity && sign != rhs.sign) {
            throw std::runtime_error("Undefined operation: Infinity + (-Infinity)");
        }
        return APNumber(isInfinity ? sign : rhs.sign, true);
    }

    vector<unsigned int> rhs_decimalPart = rhs.getDecimalPart();
    vector<unsigned int> rhs_integerPart = rhs.getIntegerPart();
    // make a local copy, just in case we need to pad with zeros
    vector<unsigned int> this_decimalPart = getDecimalPart();
    vector<unsigned int> this_integerPart = getIntegerPart();
    unsigned int rhs_numDecimalDigits = rhs_decimalPart.size();
    unsigned int rhs_numIntegerDigits = rhs_integerPart.size();
    unsigned int this_numIntegerDigits = integerPart.size();
    unsigned int this_numDecimalDigits = decimalPart.size();

    unsigned int numDecimalDigits = rhs_numDecimalDigits > this_numDecimalDigits ? rhs_numDecimalDigits : this_numDecimalDigits;
    unsigned int numIntegerDigits = rhs_numIntegerDigits > this_numIntegerDigits ? rhs_numIntegerDigits : this_numIntegerDigits;

    // do padding as necessary
    if (rhs_numDecimalDigits > this_numDecimalDigits) {
        for (unsigned int extra = this_numDecimalDigits; extra < rhs_numDecimalDigits; extra++)
            this_decimalPart.push_back(0);
    }
    else if (rhs_numDecimalDigits < this_numDecimalDigits) {
        for (unsigned int extra = rhs_numDecimalDigits; extra < this_numDecimalDigits; extra++)
            rhs_decimalPart.push_back(0);
    }

    if (rhs_numIntegerDigits > this_numIntegerDigits) {
        for (unsigned int extra = this_numIntegerDigits; extra < rhs_numIntegerDigits; extra++)
            this_integerPart.push_back(0);
    }
    else if (rhs_numIntegerDigits < this_numIntegerDigits) {
        for (unsigned int extra = rhs_numIntegerDigits; extra < this_numIntegerDigits; extra++)
            rhs_integerPart.push_back(0);
    } 

    APNumber result;
    vector<unsigned int> decimalResult;
    decimalResult.resize(numDecimalDigits);
    vector<unsigned int> integerResult;
    unsigned int carryover = 0;
    if ( sign == rhs.getSign() ) {
        for (int i=numDecimalDigits-1; i >= 0; i--) {
            unsigned int rawResult = rhs_decimalPart[i] + this_decimalPart[i] + carryover;
            if (rawResult >=10) {
                rawResult = rawResult % 10;
                carryover = 1;
            } else {
                carryover = 0;
            }
            decimalResult[i] = rawResult;    
        }
        for (unsigned int i=0; i<numIntegerDigits; i++) {
            unsigned int rawResult = rhs_integerPart[i] + this_integerPart[i] + carryover;
            if (rawResult >=10) {
                rawResult = rawResult % 10;
                carryover = 1;
            } else {
                carryover = 0;
            }
            integerResult.push_back(rawResult);    
        }
        if (carryover == 1)
           integerResult.push_back(1);

        result.setDecimalPart(decimalResult);
        result.setIntegerPart(integerResult);
        result.setSign(sign);
    }
    // deal with opposite sign operands - unfinished

    return result;

} // end operator +

bool APNumber::operator==(const APNumber& rhs) const {
    if (isInfinity != rhs.isInfinity) return false;
    if (isInfinity && rhs.isInfinity) return sign == rhs.sign;
    return sign == rhs.sign && integerPart == rhs.integerPart && decimalPart == rhs.decimalPart;
}

APNumber APNumber::operator-(const APNumber& rhs) const {
    if (isInfinity || rhs.isInfinity) {
        if (isInfinity && rhs.isInfinity && sign == rhs.sign) {
            throw std::runtime_error("Undefined operation: Infinity - Infinity");
        }
        return APNumber(isInfinity ? sign : !rhs.sign, true);
    }

    // If signs are different, convert to addition
    if (sign != rhs.getSign()) {
        APNumber rhsCopy = rhs;
        rhsCopy.setSign(!rhs.getSign());
        return *this + rhsCopy;
    }

    // If signs are the same, we need to determine which number is larger
    bool thisLarger = (*this >= rhs);
    const APNumber& larger = thisLarger ? *this : rhs;
    const APNumber& smaller = thisLarger ? rhs : *this;

    vector<unsigned int> resultInteger;
    vector<unsigned int> resultDecimal;
    int borrow = 0;

    // Subtract decimal parts
    for (int i = max(larger.decimalPart.size(), smaller.decimalPart.size()) - 1; i >= 0; --i) {
        int largerDigit = i < larger.decimalPart.size() ? larger.decimalPart[i] : 0;
        int smallerDigit = i < smaller.decimalPart.size() ? smaller.decimalPart[i] : 0;
        int diff = largerDigit - smallerDigit - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        resultDecimal.insert(resultDecimal.begin(), diff);
    }

    // Subtract integer parts
    for (size_t i = 0; i < max(larger.integerPart.size(), smaller.integerPart.size()); ++i) {
        int largerDigit = i < larger.integerPart.size() ? larger.integerPart[i] : 0;
        int smallerDigit = i < smaller.integerPart.size() ? smaller.integerPart[i] : 0;
        int diff = largerDigit - smallerDigit - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        resultInteger.push_back(diff);
    }

    // Remove leading zeros from integer part
    while (resultInteger.size() > 1 && resultInteger.back() == 0) {
        resultInteger.pop_back();
    }

    // Check if the result is zero
    if (resultInteger.empty() && resultDecimal.empty()) {
        APNumber result;
        result.setIntegerPart({0});
        result.setDecimalPart({0});
        result.setSign(true);
        return result;
    }

    APNumber result;
    result.setIntegerPart(resultInteger);
    result.setDecimalPart(resultDecimal);
    result.setSign(thisLarger ? larger.getSign() : !larger.getSign());

    return result;
}
bool APNumber::operator<=(const APNumber& rhs) const {
    return rhs >= *this;
}

bool APNumber::operator>(const APNumber& rhs) const {
    return !(*this <= rhs);
}

bool APNumber::operator<(const APNumber& rhs) const {
    return !(*this >= rhs);
}

bool APNumber::operator!=(const APNumber& rhs) const {
    return !(*this == rhs);
}

APNumber APNumber::operator-() const {
    APNumber result(*this);
    result.setSign(!sign);
    return result;
}

APNumber APNumber::operator*(const APNumber& rhs) const {

    if (isInfinity || rhs.isInfinity) {
        return APNumber(sign == rhs.sign, true);
    }
    // Determine the sign of the result
    bool resultSign = (this->sign == rhs.sign);

    // Multiply the absolute values
    vector<unsigned int> result(this->integerPart.size() + this->decimalPart.size() + 
                                rhs.integerPart.size() + rhs.decimalPart.size(), 0);

    for (size_t i = 0; i < this->integerPart.size() + this->decimalPart.size(); ++i) {
        for (size_t j = 0; j < rhs.integerPart.size() + rhs.decimalPart.size(); ++j) {
            unsigned int digit1 = (i < this->integerPart.size()) ? this->integerPart[i] : 
                                  (i < this->integerPart.size() + this->decimalPart.size() ? 
                                   this->decimalPart[i - this->integerPart.size()] : 0);
            unsigned int digit2 = (j < rhs.integerPart.size()) ? rhs.integerPart[j] : 
                                  (j < rhs.integerPart.size() + rhs.decimalPart.size() ? 
                                   rhs.decimalPart[j - rhs.integerPart.size()] : 0);
            result[i + j] += digit1 * digit2;
        }
    }

    // Handle carries
    for (size_t i = 0; i < result.size() - 1; ++i) {
        result[i + 1] += result[i] / 10;
        result[i] %= 10;
    }

    // Determine decimal point position
    size_t decimalPosition = this->decimalPart.size() + rhs.decimalPart.size();

    // Create the result APNumber
    APNumber resultNumber;
    resultNumber.setSign(resultSign);
    resultNumber.setIntegerPart(vector<unsigned int>(result.begin() + decimalPosition, result.end()));
    resultNumber.setDecimalPart(vector<unsigned int>(result.begin(), result.begin() + decimalPosition));

    // Remove leading zeros from integer part
    while (resultNumber.integerPart.size() > 1 && resultNumber.integerPart.back() == 0) {
        resultNumber.integerPart.pop_back();
    }

    // Remove trailing zeros from decimal part
    while (resultNumber.decimalPart.size() > 1 && resultNumber.decimalPart.back() == 0) {
        resultNumber.decimalPart.pop_back();
    }

    return resultNumber;
}
APNumber APNumber::operator/(const APNumber& rhs) const {
    if (rhs.isInfinity) {
        return APNumber(true, false); // Return zero
    }
    if (isInfinity) {
        if (rhs == APNumber("0")) {
            throw std::runtime_error("Undefined operation: Infinity / 0");
        }
        return APNumber(sign == rhs.sign, true);
    }
    if (rhs == APNumber("0")) {
        throw std::runtime_error("Division by zero");
    }

    APNumber dividend = *this;
    APNumber divisor = rhs;
    dividend.setSign(true);
    divisor.setSign(true);

    APNumber quotient;
    std::vector<unsigned int> quotientDigits;

    // Align decimal points
    int decimalShift = std::max(dividend.getNumDecimalDigits(), divisor.getNumDecimalDigits());
    dividend = dividend * APNumber(std::string(decimalShift * 2, '0'));
    divisor = divisor * APNumber(std::string(decimalShift, '0'));

    while (dividend >= divisor) {
        int count = 0;
        while (dividend >= divisor) {
            dividend = dividend - divisor;
            count++;
        }
        quotientDigits.push_back(count);
        dividend = dividend * APNumber("10");
    }

    // Set decimal point position
    int decimalPosition = decimalShift;

    // Remove trailing zeros
    while (!quotientDigits.empty() && quotientDigits.back() == 0) {
        quotientDigits.pop_back();
        decimalPosition--;
    }

    // Separate integer and decimal parts
    std::vector<unsigned int> integerResult(quotientDigits.begin(), quotientDigits.begin() + decimalPosition);
    std::vector<unsigned int> decimalResult(quotientDigits.begin() + decimalPosition, quotientDigits.end());

    quotient.setIntegerPart(integerResult);
    quotient.setDecimalPart(decimalResult);
    quotient.setSign(sign == rhs.getSign());

    return quotient;
}

/**
   Overloaded stream redirection operator
   @param[in]     _os a reference to the target output stream
   @param[in]     _s a reference to the target point
   @returns       a reference to the target output stream for chaining purpo    ses
 */

bool APNumber::operator>=(const APNumber& rhs) const {
    if (isInfinity != rhs.isInfinity) return isInfinity;
    if (isInfinity && rhs.isInfinity) return sign >= rhs.sign;
    if (sign != rhs.getSign()) return sign;
    if (integerPart.size() != rhs.getIntegerPart().size())
        return (integerPart.size() > rhs.getIntegerPart().size()) == sign;
    for (int i = integerPart.size() - 1; i >= 0; i--)
        if (integerPart[i] != rhs.getIntegerPart()[i])
            return (integerPart[i] > rhs.getIntegerPart()[i]) == sign;
    for (int i = 0; i < min(decimalPart.size(), rhs.getDecimalPart().size()); i++)
        if (decimalPart[i] != rhs.getDecimalPart()[i])
            return (decimalPart[i] > rhs.getDecimalPart()[i]) == sign;
    return decimalPart.size() >= rhs.getDecimalPart().size();
}

ostream& operator<<(ostream& _os, const APNumber& _s) {
    if (_s.isInfinite()) {
        return _os << (_s.getSign() ? "inf" : "-inf");
    }

    if (_s.getIntegerPart().empty() && _s.getDecimalPart().empty()) {
        return _os << "0";
    }

    if (!_s.getSign()) {
        _os << "-";
    }

    const vector<unsigned int>& integerPart = _s.getIntegerPart();
    const vector<unsigned int>& decimalPart = _s.getDecimalPart();

    // Print integer part
    if (integerPart.empty()) {
        _os << "0";
    } else {
        for (size_t i = integerPart.size(); i-- > 0; ) {
            _os << integerPart[i];
        }
    }

    // Print decimal part if it exists
    if (!decimalPart.empty()) {
        _os << ".";
        for (size_t i = 0; i < decimalPart.size(); ++i) {
            _os << decimalPart[i];
        }
    }

    return _os;
}

