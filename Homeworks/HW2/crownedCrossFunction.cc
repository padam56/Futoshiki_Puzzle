/******************************************
*                                         *
*               PROTCAD                   *
*     PROTein Computer Assisted Design    *
*                                         *
*          Copyright 2002,2011            *
*        Christopher Mark Summa           *
*                 and                     *
*    The University of New Orleans        *
*       New Orleans, LA 70148             *
*                                         *
******************************************/

#include "crownedCrossFunction.h"

#ifdef HAS_BOOST_SERIALIZE
BOOST_CLASS_EXPORT_GUID(crownedCrossFunction, "crownedCrossFunction")
#endif

//#define __CROWNEDCROSS_FUNC_DEBUG

crownedCrossFunction::crownedCrossFunction ( )
    : twoVariableEnergyFunc()
{
#ifdef __CROWNEDCROSS_FUNC_DEBUG
    cout<< "Default crownedCrossFunction constructor called" << endl;
#endif
}

crownedCrossFunction::crownedCrossFunction ( vector<PCReal> itsPosition )
    : twoVariableEnergyFunc(itsPosition)
{
#ifdef __CROWNEDCROSS_FUNC_DEBUG
    cout<< "Specific crownedCrossFunction constructor called" << endl;
#endif
}

crownedCrossFunction::crownedCrossFunction ( PCReal _x, PCReal _y )
    : twoVariableEnergyFunc(_x,_y)
{
#ifdef __CROWNEDCROSS_FUNC_DEBUG
    cout<< "Specific crownedCrossFunction constructor called" << _x << "," << _y << ")" << endl;
#endif
}

crownedCrossFunction::~crownedCrossFunction ( )
{
#ifdef __CROWNEDCROSS_FUNC_DEBUG
    cout<< "crownedCrossFunction destructor called " << endl;
#endif
}

PCReal crownedCrossFunction::evaluate ( )
{
    return crownedCrossFunction::evaluate(itsPos);
}

PCReal crownedCrossFunction::evaluate ( ) const
{
#ifdef ENERGY_DEBUG
    cout << "crownedCrossFunction::energy = " << itsCurrentEnergy << endl;
#endif
    return crownedCrossFunction::evaluate(itsPos);
}

PCReal crownedCrossFunction::evaluate ( PCReal _x, PCReal _y )
{
    return 0.0001*pow((abs(sin(_x)*sin(_y)*exp(abs(100-pow(pow(_x,2)+pow(_y,2),0.5)/M_PI)))+1.0),0.1);
}

PCReal crownedCrossFunction::evaluate ( vector<PCReal> _pos )
{
    return crownedCrossFunction::evaluate(_pos[0],_pos[1]);
}
