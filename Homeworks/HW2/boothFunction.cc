#include "boothFunction.h"
#include <cmath>
#include <iostream>

#ifdef BOOTHFUNC_DEBUG
#define DEBUG_PRINT(x) std::cout << x << std::endl;
#else
#define DEBUG_PRINT(x)
#endif

// Default constructor
boothFunction::boothFunction()
    : twoVariableEnergyFunc()
{
    DEBUG_PRINT("Default boothFunction constructor called");
}

// Constructor with position vector
boothFunction::boothFunction(vector<PCReal> itsPosition)
    : twoVariableEnergyFunc(itsPosition)
{
    DEBUG_PRINT("Specific boothFunction constructor called with vector");
}

// Constructor with specific x and y values
boothFunction::boothFunction(PCReal _x, PCReal _y)
    : twoVariableEnergyFunc(_x, _y)
{
    DEBUG_PRINT("Specific boothFunction constructor called with x=" << _x << ", y=" << _y);
}

// Destructor
boothFunction::~boothFunction()
{
    DEBUG_PRINT("boothFunction destructor called");
}

// Evaluate function without arguments (uses internal position)
PCReal boothFunction::evaluate()
{
    return boothFunction::evaluate(itsPos);
}

// Evaluate function without arguments (const version)
PCReal boothFunction::evaluate() const
{
#ifdef ENERGY_DEBUG
    std::cout << "boothFunction::energy = " << itsCurrentEnergy << std::endl;
#endif
    return boothFunction::evaluate(itsPos);
}

// Evaluate function with specific x and y values
PCReal boothFunction::evaluate(PCReal _x, PCReal _y)
{
    // Booth function formula: (x + 2y - 7)^2 + (2x + y - 5)^2
    PCReal term1 = pow((_x + 2 * _y - 7), 2);
    PCReal term2 = pow((2 * _x + _y - 5), 2);

    return term1 + term2;
}

// Evaluate function with position vector
PCReal boothFunction::evaluate(vector<PCReal> _pos)
{
    return boothFunction::evaluate(_pos[0], _pos[1]);
}