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

#include "schafferFunction.h"

#ifdef HAS_BOOST_SERIALIZE
BOOST_CLASS_EXPORT_GUID(schafferFunction, "schafferFunction")
#endif

//#define TWOVARENERGYFUNC_DEBUG

schafferFunction::schafferFunction ( )
    : twoVariableEnergyFunc()
{
#ifdef TWOVARENERGYFUNC_DEBUG
    cout<< "Default schafferFunction constructor called" << endl;
#endif
}

schafferFunction::schafferFunction ( vector<PCReal> itsPosition )
    : twoVariableEnergyFunc(itsPosition)
{
#ifdef TWOVARENERGYFUNC_DEBUG
    cout<< "Specific schafferFunction constructor called" << endl;
#endif
}

schafferFunction::schafferFunction ( PCReal _x, PCReal _y )
    : twoVariableEnergyFunc(_x,_y)
{
#ifdef TWOVARENERGYFUNC_DEBUG
    cout<< "Specific schafferFunction constructor called" << _x << "," << _y << ")" << endl;
#endif
}

schafferFunction::~schafferFunction ( )
{
#ifdef TWOVARENERGYFUNC_DEBUG
    cout<< "schafferFunction destructor called " << endl;
#endif
}

PCReal schafferFunction::evaluate ( )
{
    return schafferFunction::evaluate(itsPos);
}

PCReal schafferFunction::evaluate ( ) const
{
#ifdef ENERGY_DEBUG
    cout << "schafferFunction::energy = " << itsCurrentEnergy << endl;
#endif
    return schafferFunction::evaluate(itsPos);
}

PCReal schafferFunction::evaluate ( PCReal _x, PCReal _y )
{
    PCReal xsqr_plus_ysqr = pow(_x, 2) + pow(_y, 2);

    return 0.5 + (pow(sin(sqrt(xsqr_plus_ysqr)),2) - 0.5) / pow((1 + 0.001*xsqr_plus_ysqr),2);
}

PCReal schafferFunction::evaluate ( vector<PCReal> _pos )
{
    return schafferFunction::evaluate(_pos[0],_pos[1]);
}
