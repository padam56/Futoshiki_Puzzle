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
#include "optimizationSystem.h"
#include "ran.h"

#ifndef SIMULATED_ANNEALING_ALG_H
#define SIMULATED_ANNEALING_ALG_H

class simulatedAnnealingAlgorithm
{
public:

    // Constructor and Destructor declaration
    simulatedAnnealingAlgorithm ( );
    simulatedAnnealingAlgorithm ( optimizationSystem* _pOptimizationSystem, ran* _pItsRandomNumberGenerator );
    ~simulatedAnnealingAlgorithm ( );

    // Accessors
    void run ( PCReal _tempH,
                PCReal _tempL,
                unsigned int _iter,
                ofstream& _progressFile,
                ofstream& _acceptanceStatisticsFile,
                ofstream& _verboseFile );

    static unsigned int getHowMany ( ) { return howMany; }
    void writeEveryState ( ) { writeEveryStateFlag  = true; }
    void dontWriteEveryState ( ) { writeEveryStateFlag = false; }
    void setOutputFileBaseName ( const string& _baseName ) { itsOutputFileBaseName = _baseName; }
    void setForceAcceptance ( bool _val ) { forceAcceptance = _val; }

private:
    void   setupSystem ( );
    int    modify ( );
    PCReal energy ( );
    void   decrementTemp ( );
    void   acceptModification ( );
    void   rejectModification ( );
    void   saveState ( string& _filename );
    void   saveBestState ( string& _filename );

private:
#ifdef HAS_BOOST_SERIALIZE
    friend class boost::serialization::access;
    template<class Archive>
    void serialize ( Archive & ar, const unsigned int version )
    {
        ar & howMany;
        ar & itsTemp;
        ar & itsTempDecrement;
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
    }
#endif

private:
    //variable declarations
    static unsigned int howMany;
    PCReal itsTemp;
    PCReal itsTempDecrement;
    unsigned int itsNumIterations;
    unsigned int itsCurrentIteration;
    unsigned int itsNumNormalKeep;
    unsigned int itsNumMetropolisKeep;
    unsigned int itsLowestCounter;
    PCReal itsNewEnergy;
    PCReal itsOldEnergy;
    PCReal itsProbAccept;
    PCReal e;
    PCReal itsLowestEnergy;
    bool writeEveryStateFlag;
    PCReal firstrun;
    optimizationSystem* pItsOptimizationSystem;
    ran* pItsRandomNumberGenerator;
    string itsOutputFileBaseName;
    bool forceAcceptance;
};
#endif
