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

#include "leonFunction.h"

#ifdef HAS_BOOST_SERIALIZE
BOOST_CLASS_EXPORT_GUID(leonFunction, "leonFunction")
#endif

//#define __LEON_FUNC_DEBUG

leonFunction::leonFunction ( )
    : twoVariableEnergyFunc()
{
#ifdef __LEON_FUNC_DEBUG
    cout<< "Default leonFunction constructor called" << endl;
#endif
}

leonFunction::leonFunction ( vector<PCReal> itsPosition )
    : twoVariableEnergyFunc(itsPosition)
{
#ifdef __LEON_FUNC_DEBUG
    cout<< "Specific leonFunction constructor called" << endl;
#endif
}

leonFunction::leonFunction ( PCReal _x, PCReal _y )
    : twoVariableEnergyFunc(_x,_y)
{
#ifdef __LEON_FUNC_DEBUG
    cout<< "Specific leonFunction constructor called" << _x << "," << _y << ")" << endl;
#endif
}

leonFunction::~leonFunction ( )
{
#ifdef __LEON_FUNC_DEBUG
    cout<< "leonFunction destructor called " << endl;
#endif
}

PCReal leonFunction::evaluate ( )
{
    return leonFunction::evaluate(itsPos);
}

PCReal leonFunction::evaluate ( ) const
{
#ifdef ENERGY_DEBUG
    cout << "leonFunction::energy = " << itsCurrentEnergy << endl;
#endif
    return leonFunction::evaluate(itsPos);
}

PCReal leonFunction::evaluate ( PCReal _x, PCReal _y )
{
    return 100.0*pow((_y-pow(_x,2)),2)+pow((1-_x),2);
}

PCReal leonFunction::evaluate ( vector<PCReal> _pos )
{
    return leonFunction::evaluate(_pos[0],_pos[1]);
}
