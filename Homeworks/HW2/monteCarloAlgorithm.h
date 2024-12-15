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

#include "typedef.h"
#include "optimizationSystem.h"
#include "ran.h"

#ifndef MONTE_CARLO_ALG_H
#define MONTE_CARLO_ALG_H

class monteCarloAlgorithm
{
public:

    // Constructor and Destructor declaration
    monteCarloAlgorithm ( );
    monteCarloAlgorithm ( optimizationSystem* _pOptimizationSystem, ran* _pitsRandomNumberGenerator );
    virtual ~monteCarloAlgorithm ( );

    // Accessors
    void writeEveryState ( ) { writeEveryStateFlag  = true; }
    void dontWriteEveryState ( ) { writeEveryStateFlag = false; }
    void setOutputFileBaseName ( const string& _baseName ) { itsOutputFileBaseName = _baseName; }
    void setForceAcceptance ( bool _val ) { forceAcceptance = _val; }
    void setUseBoltzmann ( bool _val ) { useBoltzmann = _val; }

    virtual PCReal energy ( );
    virtual void setupSystem ( );
    virtual int  modify ( );
    virtual void acceptModification ( );
    virtual void rejectModification ( );
    virtual void saveState ( string& _filename );
    virtual void saveBestState ( string& _filename );
    virtual void printEverything ( const bool& _deep=false, ostream& _os=cout );

    virtual void run ( PCReal _temp, unsigned int _iter, ostream& _os=cout ) = 0;

private:
#ifdef HAS_BOOST_SERIALIZE
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & howMany;
        ar & itsTemp;
        ar & itsNumIterations;
        ar & itsCurrentIteration;
        ar & itsNumNormalKeep;
        ar & itsNumMetropolisKeep;
        ar & itsLowestCounter;
        ar & itsNewEnergy;
        ar & itsOldEnergy;
        ar & itsProbAccept;
        ar & e;
        ar & itsLowestEnergy;
        ar & writeEveryStateFlag;
        ar & firstrun;
        ar & pItsOptimizationSystem;
        ar & pItsRandomNumberGenerator;
        ar & itsOutputFileBaseName;
        ar & forceAcceptance;
        ar & useBoltzmann;
        ar & Boltzmann;
    }
#endif

protected:
    //variable declarations
    static unsigned int howMany;
    PCReal              itsTemp;
    unsigned int        itsNumIterations;
    unsigned int        itsCurrentIteration;
    unsigned int        itsNumNormalKeep;
    unsigned int        itsNumMetropolisKeep;
    unsigned int        itsLowestCounter;
    PCReal              itsNewEnergy;
    PCReal              itsOldEnergy;
    PCReal              itsProbAccept;
    PCReal              e;
    PCReal              itsLowestEnergy;
    bool                writeEveryStateFlag;
    bool                firstrun;
    optimizationSystem* pItsOptimizationSystem;
    ran*                pItsRandomNumberGenerator;
    string              itsOutputFileBaseName;
    bool                forceAcceptance;
    bool                useBoltzmann;
    PCReal              Boltzmann;
};
#endif
