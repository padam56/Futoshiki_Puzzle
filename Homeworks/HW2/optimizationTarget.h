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

#include "typedef.h"

#ifndef OPTIMIZATION_TARGET_H
#define OPTIMIZATION_TARGET_H

class optimizationTarget
{
public:
    // Constructor and Destructor declaration
    optimizationTarget ( );
    virtual ~optimizationTarget ( );

    // Accessors
    virtual PCReal evaluate ( ) = 0;
    virtual void write ( const string& _filename ) const = 0;
    virtual void updateProbabilities ( ) = 0;
    virtual void printEverything ( const bool& _deep=false, ostream& _os=cout ) = 0;
    virtual optimizationTarget* getCopy ( ) = 0;

#ifdef HAS_BOOST_SERIALIZE
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) { }
#endif

};
#endif
