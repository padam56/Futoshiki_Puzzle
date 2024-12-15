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

#include "optimizationTarget.h"

#ifdef HAS_BOOST_SERIALIZE
BOOST_CLASS_EXPORT_GUID(optimizationTarget, "optimizationTarget")
#endif

optimizationTarget::optimizationTarget ( )
{
#ifdef OPTIMIZATION_SYSTEM_DEBUG
    cout<< "Default optimizationTarget constructor called" << endl;
#endif
}

optimizationTarget::~optimizationTarget ( )
{
#ifdef OPTIMIZATION_SYSTEM_DEBUG
    cout<< "optimizationTarget destructor called " << endl;
#endif
}
