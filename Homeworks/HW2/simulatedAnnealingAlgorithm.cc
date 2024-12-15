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

#include "simulatedAnnealingAlgorithm.h"
#include "math.h"

#ifdef HAS_BOOST_SERIALIZE
BOOST_CLASS_EXPORT_GUID(simulatedAnnealingAlgorithm, "simulatedAnnealingAlgorithm")
#endif

unsigned int simulatedAnnealingAlgorithm::howMany=0;

simulatedAnnealingAlgorithm::simulatedAnnealingAlgorithm ( ) { }

simulatedAnnealingAlgorithm::simulatedAnnealingAlgorithm ( optimizationSystem* _pOptimizationSystem, ran* _pItsRandomNumberGenerator )
{
#ifdef ANNEALER_DEBUG
    cout << "Annealer constructor called:"
         << "simulatedAnnealingAlgorithm::simulatedAnnealingAlgorithm ( )" << endl;
#endif
    e =  2.71828182;
    pItsOptimizationSystem = _pOptimizationSystem;
    itsTempDecrement = -1.0;
    howMany++;
    firstrun = true;
    writeEveryStateFlag = false;
    itsLowestEnergy = PCREAL_MAX;
    itsLowestCounter = 0;
    pItsRandomNumberGenerator = _pItsRandomNumberGenerator;
    itsOutputFileBaseName = "simulatedAnnealingAlgorithmDefault";
    forceAcceptance = false;
}

simulatedAnnealingAlgorithm::~simulatedAnnealingAlgorithm ( )
{
#ifdef ANNEALER_DEBUG
    cout<< "Annealer destructor called " << endl;
#endif
    delete pItsRandomNumberGenerator;
    howMany--;
}

void simulatedAnnealingAlgorithm::run ( PCReal _tempH,
                                        PCReal _tempL,
                                        unsigned int _iter,
                                        ofstream& _progressFile,
                                        ofstream& _acceptanceStatisticsFile,
                                        ofstream& _verboseFile )
{
    itsTemp = _tempH;
    itsNumIterations = _iter;
    int whenToWrite = 0;
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

    if(_iter != 0 && _tempH >= _tempL)
    {
        itsTempDecrement = (_tempH - _tempL)/_iter;
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
    {    itsOldEnergy = energy();
    }
    cout << "STARTING ANNEAL" << endl;

    for (unsigned int itsRound=1; itsRound <= _iter; itsRound ++)
    {
        cout << "ANNEAL STEP: " << itsRound << " / " << _iter;
        cout << "\xd" << flush;
        // Check whether I should decrement temperature
        itsCurrentIteration = itsRound;
        _verboseFile << itsCurrentIteration << " ";
        if (fmod(PCReal(itsCurrentIteration),PCReal(whenToWrite)) == 0)
        {
            _progressFile << "iter: ";
            _progressFile << itsCurrentIteration;
            _progressFile << " temp: " << itsTemp;
            _progressFile << " oldE: " << itsOldEnergy;
            _progressFile << " lowE: " ;
            _progressFile << itsLowestEnergy << endl;
            _acceptanceStatisticsFile << "iter: ";
            _acceptanceStatisticsFile << itsCurrentIteration << " ";
            _acceptanceStatisticsFile << "normalkeep: ";
            _acceptanceStatisticsFile << itsNumNormalKeep << " ";
            _acceptanceStatisticsFile << "metropoliskeep: ";
            _acceptanceStatisticsFile << itsNumMetropolisKeep << endl;
            _verboseFile << itsCurrentIteration << endl;
        }
        decrementTemp();

        itsOldEnergy = energy();
        int result = modify();
        if (result == -2)
        {    cout << "Anneal cannot run because of above errors" << endl;
            cout << "Aborting anneal" << endl;
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
            _verboseFile << " OldE = " << itsOldEnergy;
            _verboseFile << " NewE = " << itsNewEnergy;
            _verboseFile << " DeltaE = " << deltaEnergy;
            _verboseFile << " Temp = " << itsTemp << endl;
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
                cout << "simulatedAnnealingAlgorithm: itsTemp has reached zero!" << endl;
                itsTemp = 1.0;
                }
                itsProbAccept = pow(e,(-deltaEnergy/itsTemp));
                if (pItsRandomNumberGenerator->getNext() < itsProbAccept)
                    keepBool = 2;
                else
                {
                    keepBool = 0;
                }
            }
            if (keepBool != 0)
            {
                acceptModification();
                if (itsNewEnergy < itsLowestEnergy)
                {
                    itsLowestEnergy = itsNewEnergy;
                    _verboseFile << "LOWEST " << itsLowestCounter << " = " << itsLowestEnergy << endl;
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
            }
            if (writeEveryStateFlag)
            {
                _verboseFile << " saving " ;
                string jason = "Debug_";
                char fmodchar[11];
                sprintf(fmodchar,"%010i",itsRound);
                string fmodstring(fmodchar,10);
//                cout << jason << " ";
//                cout << fmodstring << endl;
//                cout.flush();
                jason = jason + fmodstring + ".dat";
//                cout << jason << endl;
                saveState(jason);
                _verboseFile << " " << jason << " " << endl;
                _verboseFile << "saved" << endl;
            }
        }
        else
        {
            _verboseFile << "Abort detected at simulatedAnnealingAlgorithm level..." << endl;
        }
    }
}

int simulatedAnnealingAlgorithm::modify ( )
{
    return    pItsOptimizationSystem->modify(pItsRandomNumberGenerator);
}

PCReal simulatedAnnealingAlgorithm::energy ( )
{
    return pItsOptimizationSystem->evaluate();
}

void simulatedAnnealingAlgorithm::setupSystem ( )
{
    pItsOptimizationSystem->setupSystem(pItsRandomNumberGenerator);
}

void simulatedAnnealingAlgorithm::saveState ( string& _filename )
{
    pItsOptimizationSystem->saveState(_filename);
}

void simulatedAnnealingAlgorithm::saveBestState ( string& _filename )
{
    pItsOptimizationSystem->saveBestState(_filename);
}

void simulatedAnnealingAlgorithm::decrementTemp ( )
{
    // this temperature decrementor varies the temperature
    // roughly linearly with the number of iterations....

    // Only executed the first time through...
    if (itsTempDecrement == -1.0)
    {    itsTemp = 0.1;
        itsTempDecrement = 0.0;
    }
    itsTemp -= itsTempDecrement;
}

void simulatedAnnealingAlgorithm::acceptModification ( )
{
    pItsOptimizationSystem->acceptModification();
}

void simulatedAnnealingAlgorithm::rejectModification ( )
{
    pItsOptimizationSystem->rejectModification();
}
