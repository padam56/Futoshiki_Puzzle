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

#include "monteCarloAlgorithm.h"
#include "typedef.h"

#ifndef MCSERIAL_ALGO_H
#define MCSERIAL_ALGO_H

class ran;
class optimizationSystem;

class MCSerialAlgorithm : public monteCarloAlgorithm
{
public:

    // Constructor and Destructor declaration
    MCSerialAlgorithm ( );
    MCSerialAlgorithm ( optimizationSystem* _pOptimizationSystem, ran* _pitsRandomNumberGenerator );
    virtual ~MCSerialAlgorithm ( );

    // Accessors
    virtual void run ( PCReal _temp, unsigned int _iter, ostream& _os=cout );
    virtual void printEverything ( const bool& _deep=false, ostream& _os=cout );

private:
#ifdef HAS_BOOST_SERIALIZE
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<monteCarloAlgorithm>(*this);
    }
#endif

};
#endif
