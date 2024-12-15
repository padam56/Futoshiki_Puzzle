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

#include "optimizationSystem.h"
#include "optimizationTarget.h"
#include "manipulator.h"
#include "ran.h"

#ifdef HAS_BOOST_SERIALIZE
BOOST_CLASS_EXPORT_GUID(optimizationSystem, "optimizationSystem")
#endif

//#define OPTIMIZATION_SYSTEM_DEBUG

optimizationSystem::optimizationSystem ( )
{
#ifdef OPTIMIZATION_SYSTEM_DEBUG
    cout<< "Default optimizationSystem constructor called" << endl;
#endif
}

optimizationSystem::optimizationSystem ( optimizationTarget* pTarget )
{
#ifdef OPTIMIZATION_SYSTEM_DEBUG
    cout<< "Specific optimizationSystem constructor called" << endl;
#endif
    pItsWorkingTarget = pTarget;
    pItsMostRecentManipulator = 0;
    itsManipulators.resize(0);
    itsBestStates.resize(0);
    itsBestStateEvals.resize(0);
}

optimizationSystem::~optimizationSystem ( )
{
#ifdef OPTIMIZATION_SYSTEM_DEBUG
    cout<< "optimizationSystem destructor called " << endl;
#endif
}


/**
 * This will randomly select a manipulation from itsManipulators, then
 * randomly select a value within the range of that manipulator and finally
 * apply this manipulator to itsOptimizationSystem
 */
int optimizationSystem::modify ( ran* _pRan )
{
#ifdef OPTIMIZATION_SYSTEM_DEBUG
    cout << "optimizationSystem::modify called with ran @: " << _pRan << endl;
    cout << "pItsMostRecentManipulator = " << pItsMostRecentManipulator << endl;
    cout << "itsManipulators.size() = " << itsManipulators.size() << endl;
#endif
    pItsWorkingTarget->updateProbabilities();
    if (pItsMostRecentManipulator != 0)
    {
        pItsMostRecentManipulator->reset();
        pItsMostRecentManipulator = 0;
    }
    if (itsManipulators.size() != 0)
    {
        unsigned int manipIndex = chooseManipulator(_pRan);
        pItsMostRecentManipulator = itsManipulators[manipIndex];
#ifdef OPTIMIZATION_SYSTEM_DEBUG
        cout << "Choosing manipulator at index: " << manipIndex << endl;
        cout << "before choosing manipulation: " << endl;
        pItsMostRecentManipulator->printEverything(true);
#endif
        pItsMostRecentManipulator->chooseModification(pItsWorkingTarget,_pRan);
#ifdef OPTIMIZATION_SYSTEM_DEBUG
        cout << "after choosing manipulation: " << endl;
        pItsMostRecentManipulator->printEverything(true);
#endif
		pItsMostRecentManipulator->applyModification(pItsWorkingTarget);
#ifdef OPTIMIZATION_SYSTEM_DEBUG
        cout << "after applying manipulation: " << endl;
        pItsMostRecentManipulator->printEverything(true);
#endif
        return 0;
    }
    else
    {
        cout << "Error! no manipulators added to the optimizationSystem!" << endl;
        cout << "Exiting...";
    }
    return -1;
}

PCIndex optimizationSystem::chooseManipulator ( ran* _pRan )
{
#ifdef OPTIMIZATION_SYSTEM_DEBUG
    cout<< "Specific optimizationSystem chooseManipulator called" << endl;
#endif
    PCReal totalWeights = 0.0;
    for (unsigned int i=0; i<itsManipulatorWeights.size(); i++)
    {
#ifdef OPTIMIZATION_SYSTEM_DEBUG
    cout << " itsManipulatorWeights[" << i << "] = " << itsManipulatorWeights[i] << endl;
#endif
        totalWeights += itsManipulatorWeights[i];
    }
    PCReal randomNum  = _pRan->getNext(0.0,totalWeights);
    PCReal sum = 0.0;
#ifdef OPTIMIZATION_SYSTEM_DEBUG
    cout << " randNum = " << randomNum << endl;
#endif
    for (unsigned int i=0; i<itsManipulatorWeights.size(); i++)
    {
#ifdef OPTIMIZATION_SYSTEM_DEBUG
        cout << " sum + itsManipulatorWeights[i] = " << sum + itsManipulatorWeights[i] << endl;
#endif
        if (randomNum <= sum + itsManipulatorWeights[i])
        {
#ifdef OPTIMIZATION_SYSTEM_DEBUG
            cout << "found!  Returning: " << i << endl;
#endif
            return i;
        }
        sum += itsManipulatorWeights[i];
    }
#ifdef OPTIMIZATION_SYSTEM_DEBUG
            cout << "not found!  Returning: 0" << endl;
#endif
    return 0;
}

PCReal optimizationSystem::evaluateAndRecord ( )
{
#ifdef EVALUATE_DEBUG
    cout << "optimizationSystem::evaluateAndRecord( ) called ";
#endif
    itsCurrentEvaluation = evaluate();
    PCIndex numevals = itsBestStateEvals.size();
    if ((numevals == 0) || (itsCurrentEvaluation < itsBestStateEvals[numevals-1]))
    {
        itsBestStateEvals.push_back(itsCurrentEvaluation);
        record();
    }
    return itsCurrentEvaluation;
}

void optimizationSystem::acceptModification ( )
{
#ifdef EVALUATE_DEBUG
    cout << "optimizationSystem::acceptModification( ) called ";
#endif
    if (pItsMostRecentManipulator != 0)
        pItsMostRecentManipulator->acceptModification(pItsWorkingTarget);
}

void optimizationSystem::rejectModification ( )
{
#ifdef EVALUATE_DEBUG
    cout << "optimizationSystem::rejectModification( ) called ";
#endif
    if (pItsMostRecentManipulator != 0)
        pItsMostRecentManipulator->rejectModification(pItsWorkingTarget);
}

void optimizationSystem::setupSystem ( ran* _pRan )
{
#ifdef EVALUATE_DEBUG
    cout << "optimizationSystem::setupSystem( ) called ";
#endif
    for (unsigned int i=0; i < 100; i++)
    {
        modify(_pRan);
        acceptModification();
    }
}
void optimizationSystem::setupSystem ( )
{
#ifdef EVALUATE_DEBUG
    cout << "optimizationSystem::setupSystem( ) called ";
#endif
// !CS
// this should put the protein in the first allowed state
}

void optimizationSystem::saveState ( string& _filename )
{
#ifdef EVALUATE_DEBUG
    cout << "optimizationSystem::saveState( ) called ";
#endif
    pItsWorkingTarget->write(_filename);
}

void optimizationSystem::saveBestState ( string& _filename )
{
#ifdef EVALUATE_DEBUG
    cout << "optimizationSystem::saveBestState( ) called ";
#endif
    pItsWorkingTarget->write(_filename);
}
void optimizationSystem::printEverything  (  const bool& _deep, ostream& _os  )
{
    if (_os.good())
    {
        _os << "optimizationSystem::printEverything called" << endl;
        _os << "\tnumManips: " << itsManipulators.size() << endl;
        for (PCIndex i = 0; i < itsManipulators.size(); i++)
        {
            if (itsManipulators[i] == pItsMostRecentManipulator)
                _os << "**MostRecentUsed** ";
            _os << "[" << i << "|" << itsManipulators.size() << "] manipWeight: " << itsManipulatorWeights[i] << endl;
            itsManipulators[i]->printEverything(_deep,_os);
        }
        if (_deep)
        {
            _os << "\tBegin itsWorkingTarget:";
            pItsWorkingTarget->printEverything(_deep,_os);
        }
    }
    else
        cerr << "ERROR -- Unable to execute optimizationSystem::printEverything ( )!" << endl;
}

void optimizationSystem::manipulateTargetWith  (  vector<manipulator*>& _manipulators  )
{
#ifdef OPTIMIZATION_SYSTEM_DEBUG
    cout << "optimizationSystem::manipulateTargetWith called with length: [" << _manipulators.size ( ) << "]" << endl;
#endif
    vector<manipulator*>::iterator it;

    for (it = _manipulators.begin(); it != _manipulators.end(); ++it)
    {
        manipulator* currManip = *it;
        currManip->applyModification(pItsWorkingTarget);
    }
#ifdef OPTIMIZATION_SYSTEM_DEBUG
    cout << "optimizationSystem::manipulateTargetWith exiting" << endl;
#endif
}

void optimizationSystem::rejectAllFromList  (  vector<manipulator*>& _manipulators  )
{
#ifdef OPTIMIZATION_SYSTEM_DEBUG
    cout << "optimizationSystem::rejectAllFromList called with length: [" << _manipulators.size ( ) << "]" << endl;
#endif
    vector<manipulator*>::reverse_iterator rit;
    for (rit = _manipulators.rbegin(); rit != _manipulators.rend(); ++rit)
    {
        manipulator* currManip = *rit;
        currManip->rejectModification(pItsWorkingTarget);
    }
#ifdef OPTIMIZATION_SYSTEM_DEBUG
    cout << "optimizationSystem::rejectAllFromList exiting" << endl;
#endif
}

void optimizationSystem::record ( )
{
    itsBestStates.push_back(pItsWorkingTarget->getCopy());
}

PCReal optimizationSystem::evaluate ( )
{
    return pItsWorkingTarget->evaluate();
}
