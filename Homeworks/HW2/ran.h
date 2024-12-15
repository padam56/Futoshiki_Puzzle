// $Id$
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

#ifndef RAN_H
#define RAN_H

class ran
{
public:
    ran ( );
    ran ( unsigned int _seed );
    virtual ~ran ( );

    // Accessors
    virtual void setSeed ( unsigned int _seed ) = 0;
    virtual PCReal getNext ( ) = 0;
    virtual PCReal getNext ( PCReal _lowerBound, PCReal _upperBound ) = 0;
    virtual int getNext ( int _lowerBound, int _upperBound ) = 0;

private:
#ifdef HAS_BOOST_SERIALIZE
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {

    }
#endif

};
#endif
