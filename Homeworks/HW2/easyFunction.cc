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

#include "easyFunction.h"

#ifdef HAS_BOOST_SERIALIZE
BOOST_CLASS_EXPORT_GUID(easyFunction, "easyFunction")
#endif

//#define TWOVARENERGYFUNC_DEBUG

easyFunction::easyFunction ( )
    : twoVariableEnergyFunc()
{
#ifdef TWOVARENERGYFUNC_DEBUG
    cout<< "Default easyFunction constructor called" << endl;
#endif
}

easyFunction::easyFunction ( vector<PCReal> itsPosition )
    : twoVariableEnergyFunc(itsPosition)
{
#ifdef TWOVARENERGYFUNC_DEBUG
    cout<< "Specific easyFunction constructor called" << endl;
#endif
}

easyFunction::easyFunction ( PCReal _x, PCReal _y )
    : twoVariableEnergyFunc(_x,_y)
{
#ifdef TWOVARENERGYFUNC_DEBUG
    cout<< "Specific easyFunction constructor called" << _x << "," << _y << ")" << endl;
#endif
}

easyFunction::~easyFunction ( )
{
#ifdef TWOVARENERGYFUNC_DEBUG
    cout<< "easyFunction destructor called " << endl;
#endif
}

PCReal easyFunction::evaluate ( )
{
    return easyFunction::evaluate(itsPos);
}

PCReal easyFunction::evaluate ( ) const
{
#ifdef ENERGY_DEBUG
    cout << "easyFunction::energy = " << itsCurrentEnergy << endl;
#endif
    return easyFunction::evaluate(itsPos);
}

PCReal easyFunction::evaluate ( PCReal _x, PCReal _y )
{
    PCReal xsqr_plus_ysqr = pow(_x, 2) + pow(_y, 2);

    return xsqr_plus_ysqr;
}

PCReal easyFunction::evaluate ( vector<PCReal> _pos )
{
    return easyFunction::evaluate(_pos[0],_pos[1]);
}
