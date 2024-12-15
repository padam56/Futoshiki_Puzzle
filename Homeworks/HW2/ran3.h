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
#include "ran.h"


#ifndef RAN3_H
#define RAN3_H

// NOTE:  for some reason, ran3 currently does not return a truly
// uniform deviate between 0 and 1.  Use ran1 instead!!!

class ran3 : public ran
{
public:

    // Constructor and Destructor declaration
    ran3 ( );
    ran3 ( unsigned int _seed );
    ~ran3 ( );

    // Accessors
    void setSeed ( unsigned int _seed );
    PCReal getNext ( );
    PCReal getNext ( PCReal _lowerBound, PCReal _upperBound );
    int getNext ( int _lowerBound, int _upperBound );

private:
    void initialize ( unsigned int _seed );

#ifdef HAS_BOOST_SERIALIZE
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<ran>(*this);
        ar & idum;
        ar & MBIG;
        ar & MSEED;
        ar & MZ;
        ar & FAC;
        ar & inext;
        ar & inextp;
        ar & ma;
        ar & mj;
        ar & mk;
    }
#endif

private:
    //variable declarations
    int idum;
    int MBIG;
    int MSEED;
    int MZ;
    PCReal FAC;
    int inext;
    int inextp;
    long ma[56];
    long mj;
    long mk;
};
#endif
