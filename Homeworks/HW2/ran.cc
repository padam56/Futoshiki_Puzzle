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
 * @file ran.cc
 * Abstract base class for random number generator classes
 */
// $Log$

#include "ran.h"

#ifdef HAS_BOOST_SERIALIZE
BOOST_CLASS_EXPORT_GUID(ran, "ran")
#endif

/**
   Default constructor with no arguments
   does nothing
 */
ran::ran ( )
{
#ifdef RAN_DEBUG
    cout << "ran constructor called:"
         << "ran::ran ( )" << endl;
#endif
}

/**
   Destructor
   no data in this abstract class so no memory cleanup needed
 */
ran::~ran ( )
{
#ifdef RAN_DEBUG
    cout<< "ran destructor called " << endl;
#endif
}

