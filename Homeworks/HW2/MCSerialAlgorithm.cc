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

#include "MCSerialAlgorithm.h"
#include "optimizationSystem.h"
#include "math.h"
#include "ran1.h"

#ifdef HAS_BOOST_SERIALIZE
BOOST_CLASS_EXPORT_GUID(MCSerialAlgorithm, "MCSerialAlgorithm")
#endif

//#define __MCSERIAL_ALGO_DEBUG

MCSerialAlgorithm::MCSerialAlgorithm ( )
    : monteCarloAlgorithm()
{
#ifdef __MCSERIAL_ALGO_DEBUG
    cout<< "MCSerialAlgorithm default constructor called " << endl;
#endif
}

MCSerialAlgorithm::MCSerialAlgorithm ( optimizationSystem* _pOptimizationSystem, ran* _pItsRandomNumberGenerator )
    : monteCarloAlgorithm(_pOptimizationSystem, _pItsRandomNumberGenerator)
{
#ifdef __MCSERIAL_ALGO_DEBUG
    cout << "MCSerialAlgorithm constructor called:"
         << "MCSerialAlgorithm::MCSerialAlgorithm ( )" << endl;
#endif
}

MCSerialAlgorithm::~MCSerialAlgorithm ( )
{
#ifdef __MCSERIAL_ALGO_DEBUG
    cout<< "MCSerialAlgorithm destructor called " << endl;
#endif
}

void MCSerialAlgorithm::run ( PCReal _temp, unsigned int _iter, ostream& _os )
{
    itsTemp = _temp;
    itsNumIterations = _iter;
    int whenToWrite = 1;
    // Decide how often to write progress report to screen
    if (_iter <= 200)
    {
        whenToWrite = 10;
    }
    if (_iter <= 1000)
    {
        whenToWrite = 100;
    }
    if (_iter >= 10000 && _iter <=100000)
    {
        whenToWrite = 100;
    }

    if (firstrun)
    {
        itsNumNormalKeep = 0;
        itsNumMetropolisKeep = 0;
        setupSystem();
        itsLowestEnergy = 1000000.0;
        itsOldEnergy = itsLowestEnergy;
        firstrun = false;
    }
    else
    {
        itsOldEnergy = energy();
    }
    cout << "STARTING MONTE CARLO" << endl;

    for (unsigned int itsRound=1; itsRound <= _iter; itsRound++)
    {
        cout << "MONTE CARLO STEP: " << itsRound << " / " << _iter;
        cout << "\xd" << flush;
        itsCurrentIteration = itsRound;
        _os << itsCurrentIteration << " ";
        if (fmod(PCReal(itsCurrentIteration),PCReal(whenToWrite)) == 0)
        {
            _os << "iter: ";
            _os << itsCurrentIteration;
            _os << " temp: " << itsTemp;
            _os << " oldE: " << itsOldEnergy;
            _os << " lowE: " ;
            _os << itsLowestEnergy << endl;
            _os << "iter: ";
            _os << itsCurrentIteration << " ";
            _os << "normalkeep: ";
            _os << itsNumNormalKeep << " ";
            _os << "metropoliskeep: ";
            _os << itsNumMetropolisKeep << endl;
            //_os << itsCurrentIteration << endl;
        }

        itsOldEnergy = energy();
        int result = modify();
        if (result == -2)
        {    cout << "Monte Carlo cannot continue because of above errors" << endl;
            cout << "Aborting Monte Carlo" << endl;
            return;
        }

        if (result != -1)
        {

            // calculate the energy of the perturbed system
            itsNewEnergy = energy();

            // calculate the energy difference between old and new
            PCReal deltaEnergy;
            deltaEnergy = itsNewEnergy - itsOldEnergy;
            // If energy of new system is lower, keep it by
            // default
            unsigned int keepBool = 0;
            _os << " OldE = " << itsOldEnergy;
            _os << " NewE = " << itsNewEnergy;
            _os << " DeltaE = " << deltaEnergy;
            _os << " Temp = " << itsTemp ;
            if (deltaEnergy <= 0.0)
            {
                keepBool = 1;
            }
            // If energy of new system is higher, apply Metropolis
            // criterion to determine if we should keep it...
            // It is also passible to force the acceptance of every state
            // by setting forceAcceptance equal to true before the run
            // (useful for debugging)
            if (deltaEnergy > 0.0 || forceAcceptance)
            {
                if (itsTemp <= 0.0)
                {
                    cout << "MCSerialAlgorithm: itsTemp has reached zero!" << endl;
                    itsTemp = 1.0;
                }
                if (useBoltzmann)
                    itsProbAccept = pow(e,(-deltaEnergy/(itsTemp * Boltzmann)));
                else
                    itsProbAccept = pow(e,(-deltaEnergy/itsTemp));

                _os << " ProbAccept = " << itsProbAccept;
                PCReal randomNum = pItsRandomNumberGenerator->getNext();
                _os << " randomNum = " << randomNum;

                if (randomNum < itsProbAccept)
                    keepBool = 2;
                else
                {
                    keepBool = 0;
                }
            }
            if (keepBool != 0)
            {
                _os << " ACCEPTING" << endl;
                if (forceAcceptance)
                    _os << " FORCED" << endl;
                acceptModification();
                if (itsNewEnergy < itsLowestEnergy)
                {
                    itsLowestEnergy = itsNewEnergy;
                    _os << "LOWEST " << itsLowestCounter << " = " << itsLowestEnergy << endl;
                    string lowest = itsOutputFileBaseName + "_lowest_";
                    char fmodchar[6];
                    sprintf(fmodchar,"%i",itsLowestCounter);
                    string fmodstring = fmodchar;
                    lowest += fmodstring;
                    lowest += ".dat";
                    saveState(lowest);
                    string bestString = "best_state.dat";
                    saveBestState(bestString);
                    itsLowestCounter++;
                }

                itsOldEnergy = itsNewEnergy;
                if (keepBool > 1)
                {
                    itsNumMetropolisKeep +=1;
                }
                else
                {
                    itsNumNormalKeep +=1;
                }
            }
            else
            {    rejectModification();
                _os << " REJECTING" << endl;
            }
            if (writeEveryStateFlag || keepBool != 0)
            {
                _os << " saving " ;
                string outfilename = "monteCarlo_";
                char fmodchar[11];
                sprintf(fmodchar,"%010i",itsRound);
                string fmodstring(fmodchar,10);
                outfilename = outfilename + fmodstring + ".dat";
                saveState(outfilename);
                _os << " " << outfilename << " " << endl;
                _os << "saved" << endl;
            }
        }
        else
        {
            _os << "Abort detected at MCSerialAlgorithm level..." << endl;
        }
    }
}

void MCSerialAlgorithm::printEverything  (  const bool& _deep, ostream& _os  )
{
    if (_os.good()) { }
    else
        cerr << "ERROR -- Unable to execute MCSerialAlgorithm::printEverything ( )!" << endl;
}
