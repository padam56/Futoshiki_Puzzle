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

#include "eggHolderFunction.h"

#ifdef HAS_BOOST_SERIALIZE
BOOST_CLASS_EXPORT_GUID(eggHolderFunction, "eggHolderFunction")
#endif

//#define __EGGHOLDER_FUNC_DEBUG

eggHolderFunction::eggHolderFunction ( )
    : twoVariableEnergyFunc()
{
#ifdef __EGGHOLDER_FUNC_DEBUG
    cout<< "Default eggHolderFunction constructor called" << endl;
#endif
}

eggHolderFunction::eggHolderFunction ( vector<PCReal> itsPosition )
    : twoVariableEnergyFunc(itsPosition)
{
#ifdef __EGGHOLDER_FUNC_DEBUG
    cout<< "Specific eggHolderFunction constructor called" << endl;
#endif
}

eggHolderFunction::eggHolderFunction ( PCReal _x, PCReal _y )
    : twoVariableEnergyFunc(_x,_y)
{
#ifdef __EGGHOLDER_FUNC_DEBUG
    cout<< "Specific eggHolderFunction constructor called" << _x << "," << _y << ")" << endl;
#endif
}

eggHolderFunction::~eggHolderFunction ( )
{
#ifdef __EGGHOLDER_FUNC_DEBUG
    cout<< "eggHolderFunction destructor called " << endl;
#endif
}

PCReal eggHolderFunction::evaluate ( )
{
    return eggHolderFunction::evaluate(itsPos);
}

PCReal eggHolderFunction::evaluate ( ) const
{
#ifdef ENERGY_DEBUG
    cout << "eggHolderFunction::energy = " << itsCurrentEnergy << endl;
#endif
    return eggHolderFunction::evaluate(itsPos);
}

PCReal eggHolderFunction::evaluate ( PCReal _x, PCReal _y )
{
    return ((-1)*(_y+47)*sin(sqrt(abs(_y+(_x/2.0)+47)))+sin(sqrt(abs(_x-(_y+47))))*(-1)*_x);
}

PCReal eggHolderFunction::evaluate ( vector<PCReal> _pos )
{
    return eggHolderFunction::evaluate(_pos[0],_pos[1]);
}
