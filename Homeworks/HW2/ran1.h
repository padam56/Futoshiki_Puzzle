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

#ifndef RAN1_H
#define RAN1_H

class ran1 : public ran
{
public:
    // Constructor and Destructor declaration
    ran1 ( );
    ran1 ( unsigned int _seed );
    ~ran1 ( );

    // Accessors
    void setSeed ( unsigned int _seed );
    PCReal getNext ( );
    PCReal  getNext ( PCReal _lowerBound, PCReal _upperBound );
    int getNext ( int _lowerBound, int _upperBound );

private:
    void initialize ( unsigned int _seed );

private:
#ifdef HAS_BOOST_SERIALIZE
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<ran>(*this);
        ar & idum;
        ar & M1;
        ar & IA1;
        ar & IC1;
        ar & RM1;
        ar & M2;
        ar & IA2;
        ar & IC2;
        ar & RM2;
        ar & M3;
        ar & IA3;
        ar & IC3;
        ar & r;
        ar & ix1;
        ar & ix2;
        ar & ix3;
    }
#endif


private:
    //variable declarations
    unsigned int idum;
    unsigned int M1;
    unsigned int IA1;
    unsigned int IC1;
    PCReal RM1;
    unsigned int M2;
    unsigned int IA2;
    unsigned int IC2;
    PCReal RM2;
    unsigned int M3;
    unsigned int IA3;
    unsigned int IC3;
    PCReal r[98];
    long ix1;
    long ix2;
    long ix3;
};
#endif
