/******************************************
*                                         *
*               PROTCAD                   *
*     PROTein Computer Assisted Design    *
*                                         *
*          Copyright 2002,2011            *
*        Christopher Mark Summa           *
*                 and                     *
*     The University of New Orleans       *
*       New Orleans, LA 70148             *
*                                         *
******************************************/
/**
 * @file ran1.cc
 * Concrete class for simple uniformly distributed random number generator 
 * Descended directly from the ran1 method in Numerical Recipes in C
 */

#include "ran1.h"
#include <math.h>
#include <stdlib.h>

#ifdef HAS_BOOST_SERIALIZE
BOOST_CLASS_EXPORT_GUID(ran1, "ran1")
#endif


/**
   Default constructor with no arguments - will initialize with the seed 1235
 */
ran1::ran1 ( )
{
#ifdef RAN1_DEBUG
    cout << "ran1 constructor called:"
         << "ran1::ran1 ( )" << endl;
#endif
initialize(1235);
}

/**
   Constructor with unsigned int seed argument 
   @param[in]     _seed An unsigned int between 0 and 54773 inclusive
   @throw         xOutOfBounds Will throw an out-of-bounds exception if the value of _seed exceeds 54773
 */
ran1::ran1 ( unsigned int _seed )
{
#ifdef RAN1_DEBUG
    cout << "ran1 constructor called:"
         << "ran1::ran1 ( )" << endl;
#endif
    if (_seed > 54773 )
    {
		string func = "ran1::ran1 ( unsigned int _seed )";
        string err = "Error from ran1: random seed may not exceed 54773";
		throw xOutOfBounds(func,err);
    }
    initialize(_seed);
}

/**
   Destructor
   no allocation of memory in this class so no memory cleanup needed
 */
ran1::~ran1 ( )
{
#ifdef RAN1_DEBUG
    cout<< "ran1 destructor called " << endl;
#endif
}

/**
   A method to set the seed
   @param[in]     _seed An unsigned int between 0 and 54773 inclusive
   @throw         xOutOfBounds Will throw an out-of-bounds exception if the value of _seed exceeds 54773
 */
void ran1::setSeed ( unsigned int _seed )
{
    if (_seed > 54773 )
    {
		string func = "void ran1::setSeed ( unsigned int _seed )";
        string err = "Error from ran1: random seed may not exceed 54773";
		throw xOutOfBounds(func,err);
    }
    initialize(_seed);
}

/**
   A method to initialize the generator with a seed
   @param[in]     _seed An unsigned int between 0 and 54773 inclusive
 */
void ran1::initialize ( unsigned int _seed )
{
    idum = _seed;
    M1 = 259200;
    IA1 = 7141;
    IC1 = 54773;
    RM1 = 1.0 / M1;
    M2 = 134456;
    IA2 = 8121;
    IC2 = 28411;
    RM2 = 1.0 / M2;
    M3 = 243000;
    IA3 = 4561;
    IC3 = 52349;

    ix1 = (IC1 - idum) % M1;
    ix1 = (IA1 * ix1 + IC1) % M1;
    ix2 = ix1 % M2;
    ix1 = (IA1 * ix1 + IC1) % M1;
    ix3 = ix1 % M3;
    for (int j=1; j<=97; j++)
    {
        ix1 = (IA1 * ix1 + IC1) % M1;
        ix2 = (IA2 * ix2 + IC2) % M2;
        r[j] = (ix1+ix2*RM2) * RM1;
    }
    idum = 1;
}

/**
   Get the next uniformly distributed psuedo-random real number in the range 0.0 to 1.0
 */
PCReal ran1::getNext ( )
{
    ix1 = (IA1 * ix1 + IC1) % M1;
    ix2 = (IA2 * ix2 + IC2) % M2;
    ix3 = (IA3 * ix3 + IC3) % M3;
    int j;
    j = 1 + ((97*ix3)/M3);
    if (j>97 || j<1)
    {
        cout  << "ran1: fatal error!" << endl;
    }
    PCReal temp = r[j];
    r[j] = (ix1+ix2*RM2) * RM1;
    return temp;
}

/**
   Get the next uniformly distributed psuedo-random integer number in an arbitrary range
   @param[in]     _lowerBound an int representing the lowest possible number
   @param[in]     _upperBound an int representing the highest possible number
   @return        an int representing a psuedo-random value between _lowerBound and _upperBound inclusive
 */
int ran1::getNext ( int _lowerBound, int _upperBound )
{
    PCReal tempreal = getNext();
    int tempupper = _upperBound;
    int templower = _lowerBound;
    int temprange = 0;
    int tempint = 0;
    if (tempupper == templower)
    {
    //    cout << "Error returned by ran1::getNext ( int,int ): " << endl;
    //    cout << "Upper and lower bounds are equal!" << endl;
        return tempupper;
    }

    if (tempupper < templower)
    {
        // Swap 'em!
        int temptemp = templower;
        templower = tempupper;
        tempupper = temptemp;
    }

    temprange = tempupper - templower;
    tempreal = (tempreal * (temprange + 1.0)) + templower;
    tempint = (int)tempreal;
    return tempint;
}

/**
   Get the next uniformly distributed psuedo-random floating point number in an arbitrary range
   @param[in]     _lowerBound a floating point number representing the lowest possible number
   @param[in]     _upperBound a floating point number representing the highest possible number
   @return        a floating point number representing a psuedo-random value between _lowerBound and _upperBound inclusive
 */
PCReal ran1::getNext ( PCReal _lowerBound, PCReal _upperBound )
{
    PCReal tempreal = getNext();
    PCReal tempupper = _upperBound;
    PCReal templower = _lowerBound;
    PCReal temprange = 0;
    PCReal tempPCReal = 0;
    if (tempupper == templower)
    {
    //    cout << "Error returned by ran1::getNext ( PCReal,PCReal ): " << endl;
    //    cout << "Upper and lower bounds are equal!" << endl;
        return tempupper;
    }

    if (tempupper < templower)
    {
        // Swap 'em!
        PCReal temptemp = templower;
        templower = tempupper;
        tempupper = temptemp;
    }

    temprange = tempupper - templower;
    tempPCReal = (tempreal * temprange) + templower;
    return tempPCReal;
}
