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

#include "monteCarloAlgorithm.h"
#include "optimizationSystem.h"
#include "math.h"
#include "ran.h"
#include <limits>

#ifdef HAS_BOOST_SERIALIZE
BOOST_CLASS_EXPORT_GUID(monteCarloAlgorithm, "monteCarloAlgorithm")
#endif

//#define MONTE_CARLO_DEBUG

unsigned int monteCarloAlgorithm::howMany=0;

monteCarloAlgorithm::monteCarloAlgorithm ( )
{
#ifdef MONTE_CARLO_DEBUG
    cout << "monteCarloAlgorithm default constructor called:"
         << "monteCarloAlgorithm::monteCarloAlgorithm( )" << endl;
#endif
    e =  2.71828182;
    //Boltzmann's constant is 1.38065e-23 in units of Joule/K
    // 1 cal = 4.1868 J
    //Boltzmann's constant is 3.2674e-27 in units of kcal/K
    // Energy in most forcefields is in units of kcal/mol
    // R is the gas constant, related to Boltzmann's constant by Avogadro's number
    // and is 1.9858774 cal / K mol
    // converting this to kcal gives
    // 0.0019858775 kcal / K mol
    Boltzmann = 0.0019858775;
    useBoltzmann = true;
    howMany++;
    firstrun = true;
    writeEveryStateFlag = false;
    itsLowestEnergy = PCREAL_MAX;
    itsLowestCounter = 0;

    itsOutputFileBaseName = "monteCarloSerialAlgorithmDefault";
    forceAcceptance = false;
    itsNumIterations = 0;
    itsCurrentIteration = 0;
    itsNumNormalKeep = 0;
    itsNumMetropolisKeep = 0;
    itsNewEnergy = 0.0;
    itsOldEnergy = 0.0;
    itsProbAccept = 0.0;
    itsLowestEnergy = numeric_limits<PCReal>::infinity();
}

monteCarloAlgorithm::monteCarloAlgorithm ( optimizationSystem* _pOptimizationSystem, ran* _pItsRandomNumberGenerator )
{
#ifdef MONTE_CARLO_DEBUG
    cout << "monteCarloAlgorithm constructor called:"
         << "monteCarloAlgorithm::monteCarloAlgorithm( )" << endl;
#endif
    e =  2.71828182;
    //Boltzmann's constant is 1.38065e-23 in units of Joule/K
    // 1 cal = 4.1868 J
    //Boltzmann's constant is 3.2674e-27 in units of kcal/K
    // Energy in most forcefields is in units of kcal/mol
    // R is the gas constant, related to Boltzmann's constant by Avogadro's number
    // and is 1.9858774 cal / K mol
    // converting this to kcal gives
    // 0.0019858775 kcal / K mol
    Boltzmann = 0.0019858775;
    useBoltzmann = true;
    pItsOptimizationSystem = _pOptimizationSystem;
    howMany++;
    firstrun = true;
    writeEveryStateFlag = false;
    itsLowestEnergy = PCREAL_MAX;
    itsLowestCounter = 0;
    pItsRandomNumberGenerator = _pItsRandomNumberGenerator;

    itsOutputFileBaseName = "monteCarloSerialAlgorithmDefault";
    forceAcceptance = false;
    itsNumIterations = 0;
    itsCurrentIteration = 0;
    itsNumNormalKeep = 0;
    itsNumMetropolisKeep = 0;
    itsNewEnergy = 0.0;
    itsOldEnergy = 0.0;
    itsProbAccept = 0.0;
    itsLowestEnergy = numeric_limits<PCReal>::infinity();
}

monteCarloAlgorithm::~monteCarloAlgorithm ( )
{
#ifdef MONTE_CARLO_DEBUG
    cout<< "monteCarloAlgorithm destructor called " << endl;
#endif
    howMany--;
}

PCReal monteCarloAlgorithm::energy ( )
{
#ifdef MONTE_CARLO_DEBUG
    cout<< "monteCarloAlgorithm energy called " << endl;
#endif
    return pItsOptimizationSystem->evaluate();
}

int monteCarloAlgorithm::modify ( )
{
#ifdef MONTE_CARLO_DEBUG
    cout<< "monteCarloAlgorithm modify called " << endl;
#endif
    return pItsOptimizationSystem->modify(pItsRandomNumberGenerator);
}

void monteCarloAlgorithm::setupSystem ( )
{
#ifdef MONTE_CARLO_DEBUG
    cout<< "monteCarloAlgorithm setupSystem called " << endl;
#endif
    pItsOptimizationSystem->setupSystem(pItsRandomNumberGenerator);
}

void monteCarloAlgorithm::saveState ( string& _filename )
{
#ifdef MONTE_CARLO_DEBUG
    cout<< "monteCarloAlgorithm saveState called " << endl;
#endif
    pItsOptimizationSystem->saveState(_filename);
}

void monteCarloAlgorithm::saveBestState ( string& _filename )
{
#ifdef MONTE_CARLO_DEBUG
    cout<< "monteCarloAlgorithm saveBestState called " << endl;
#endif
    pItsOptimizationSystem->saveBestState(_filename);
}

void monteCarloAlgorithm::acceptModification ( )
{
#ifdef MONTE_CARLO_DEBUG
    cout<< "monteCarloAlgorithm acceptModification called " << endl;
#endif
    pItsOptimizationSystem->acceptModification();
}

void monteCarloAlgorithm::rejectModification ( )
{
#ifdef MONTE_CARLO_DEBUG
    cout<< "monteCarloAlgorithm rejectModification called " << endl;
#endif
    pItsOptimizationSystem->rejectModification();
}

void monteCarloAlgorithm::printEverything ( const bool& _deep, ostream& _os )
{
    if (_os.good())
    {
        _os << " ----- Begin monteCarloAlgorithm::printEverything ----- " << endl;
        _os << "\t" << "howMany: " << howMany;
        _os << "\t" << "itsTemp: " << itsTemp;
        _os << "\t" << "itsNumIterations: " << itsNumIterations;
        _os << "\t" << "itsCurrentIteration: " << itsCurrentIteration;
        _os << "\t" << "itsNumNormalKeep: " << itsNumNormalKeep;
        _os << "\t" << "itsNumMetropolisKeep: " << itsNumMetropolisKeep;
        _os << "\t" << "itsLowestCounter: " << itsLowestCounter;
        _os << "\t" << "itsNewEnergy: " << itsNewEnergy;
        _os << "\t" << "itsOldEnergy: " << itsOldEnergy;
        _os << "\t" << "itsProbAccept: " << itsProbAccept;
        _os << "\t" << "e" << e;
        _os << "\t" << "itsLowestEnergy" << itsLowestEnergy;
        _os << "\t" << "writeEveryStateFlag" << writeEveryStateFlag;
        _os << "\t" << "firstrun: " << firstrun;
        _os << "\t" << "itsOutputFileBaseName: " << itsOutputFileBaseName;
        _os << "\t" << "forceAcceptance: " << forceAcceptance;
        _os << "\t" << "useBoltzmann: " << useBoltzmann;
        _os << "\t" << "Boltzmann: " << Boltzmann;
        if (_deep)
        {
            pItsOptimizationSystem->printEverything(_deep,_os);
        }
        _os << " ----- End monteCarloAlgorithm::printEverything ----- " << endl;
    }
    else
        cerr << "ERROR -- Unable to execute monteCarloAlgorithm::printEverything()!" << endl;

}
