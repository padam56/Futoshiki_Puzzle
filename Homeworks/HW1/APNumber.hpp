/*
*        a crude, rudimentary implementation of an arbitrary precision number
*        in C++
*
*        Author:  Christopher M. Summa
*        Version:  0.10
*
*        For a MUCH more robust version , see the GMP library at
*        https://gmplib.org
*
*/


#ifndef APNUMBER_HPP
#define APNUMBER_HPP

#include <vector>
#include <string>
#include <iostream>

class APNumber {
public:
    APNumber();
    APNumber(bool sign, bool isInf);
    APNumber(const bool sign,
             const std::vector<unsigned int>& intPart,
             const std::vector<unsigned int>& decPart);
    APNumber(std::string stringizedNum);
    APNumber(const APNumber& rhs);
    ~APNumber();

    void setIntegerPart(const std::vector<unsigned int>& digits);
    void setDecimalPart(const std::vector<unsigned int>& digits);
    void setSign(const bool& positive);
    std::vector<unsigned int> getIntegerPart() const;
    int getNumIntegerDigits() const;
    std::vector<unsigned int> getDecimalPart() const;
    int getNumDecimalDigits() const;
    bool getSign() const;
    bool isInfinite() const { return isInfinity; }
    void setInfinity(bool inf) { isInfinity = inf; }

    // Overloaded operators
    bool operator<=(const APNumber& rhs) const;
    bool operator==(const APNumber& rhs) const;
    bool operator>=(const APNumber& rhs) const;
    bool operator>(const APNumber& rhs) const;
    bool operator<(const APNumber& rhs) const;
    bool operator!=(const APNumber& rhs) const;
    double toDouble() const;
    APNumber pow(int exponent) const;
    APNumber operator-() const;
    APNumber operator-(const APNumber& rhs) const;
    APNumber operator*(const APNumber& rhs) const;
    APNumber operator/(const APNumber& rhs) const;
    void removeLeadingTrailingZeros();
    APNumber operator+(const APNumber &rhs) const;

    std::string toScientificString(int precision) const;

    friend std::ostream& operator<<(std::ostream& os, const APNumber& num);

private:
    std::vector<unsigned int> integerPart;
    std::vector<unsigned int> decimalPart;
    bool sign;
    bool isInfinity = false;
};

std::ostream& operator<<(std::ostream& os, const APNumber& num);

#endif // APNUMBER_HPP
