/******************************************
*                                         *
*               PROTCAD                   *
*     PROTein Computer Assisted Design    *
*                                         *
*          Copyright 2002,2011            *
*        Christopher Mark Summa           *
*                 and                     *
*     The University of New Orleans        *
*       New Orleans, LA 70148             *
*                                         *
******************************************/

/**
 * @file ran3.cc
 * Concrete class for simple uniformly distributed random number generator 
 * Descended directly from the ran3 method in Numerical Recipes in C
 */

#include "ran3.h"

#ifdef HAS_BOOST_SERIALIZE
BOOST_CLASS_EXPORT_GUID(ran3, "ran3")
#endif

/**
   Default constructor with no arguments - will initialize with the seed 1235
 */
ran3::ran3 ( )
{
#ifdef RAN3_DEBUG
    cout << "ran3 constructor called:"
         << "ran3::ran3 ( )" << endl;
#endif
    initialize(1235);
}

/**
   Constructor with unsigned int seed argument 
   @param[in]     _seed An unsigned int
 */
ran3::ran3 ( unsigned int _seed )
{
#ifdef RAN3_DEBUG
    cout << "ran3 constructor called:"
         << "ran3::ran3 ( )" << endl;
#endif
        initialize(_seed);
}

/**
   Destructor
   no allocation of memory in this class so no memory cleanup needed
 */
ran3::~ran3 ( )
{
#ifdef RAN3_DEBUG
    cout<< "ran3 destructor called " << endl;
#endif
}

/**
   A method to set the seed
   @param[in]     _seed an unsigned int 
 */
void ran3::setSeed ( unsigned int _seed )
{
    initialize(_seed);
}


/**
   A method to initialize the generator with a seed
   @param[in]     _seed an unsigned int 
 */
void ran3::initialize ( unsigned int _seed )
{
    idum = _seed;
    MBIG = 1000000000;
    MSEED = 161803398;
    MZ = 0;
    FAC = 1.0 / MBIG;
// next line different also
    mj = labs(MSEED - labs(idum));
    mj %= MBIG;
    ma[55] = mj;
    mk = 1;
    for (int i = 1; i<=54; i++)
    {
        int ii;
        ii = (21 * i) % 55;
        ma[ii] = mk;
        mk = mj - mk;
        if (mk < MZ) mk += MBIG;
        mj = ma[ii];
    }
    for (int k=1; k<=4; k++)
    {
        for (int i=1; i<=55; i++)
        {
        ma[i] -= ma[1+(i+30) % 55];
        if (ma[i] < MZ) ma[i] += MBIG;
        }
    }
    inext = 0;
    inextp = 31;
    idum = 1;
}

/**
   Get the next uniformly distributed psuedo-random real number in the range 0.0 to 1.0
 */
PCReal ran3::getNext ( )
{
    if (++inext == 56) inext = 1;
// new line
    if (++inextp == 56) inextp = 1;
    mj = ma[inext]-ma[inextp];
    if (mj < MZ) mj += MBIG;
    ma[inext] = mj;
    return mj*FAC;
}

/**
   Get the next uniformly distributed psuedo-random integer number in an arbitrary range
   @param[in]     _lowerBound an int representing the lowest possible number
   @param[in]     _upperBound an int representing the highest possible number
   @return        an int representing a psuedo-random value between _lowerBound and _upperBound inclusive
 */
int ran3::getNext ( int _lowerBound, int _upperBound )
{
    PCReal tempreal = getNext();
    int tempupper = _upperBound;
    int templower = _lowerBound;
    int temprange = 0;
    int tempint = 0;
    if (tempupper == templower)
    {
    //  cout << "Error returned by ran1::getNext(int,int): " << endl;
    //  cout << "Upper and lower bounds are equal!" << endl;
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
PCReal ran3::getNext ( PCReal _lowerBound, PCReal _upperBound )
{
    PCReal tempreal = getNext();
    PCReal tempupper = _upperBound;
    PCReal templower = _lowerBound;
    PCReal temprange = 0;
    PCReal tempPCReal = 0;
    if (tempupper == templower)
    {
    //  cout << "Error returned by ran1::getNext(PCReal,PCReal): " << endl;
    //  cout << "Upper and lower bounds are equal!" << endl;
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
