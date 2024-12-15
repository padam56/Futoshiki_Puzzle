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
#include "manipulator.h"
#include "optimizationTarget.h"

#ifndef PROTEIN_FOLDER_H
#define PROTEIN_FOLDER_H

class ran;

class optimizationSystem
{
public:
    // Constructor and Destructor declaration
    optimizationSystem ( );
    optimizationSystem ( optimizationTarget* pTarget );
    ~optimizationSystem ( );

    // Accessors
    int modify ( ran* _pRan );
    PCReal evaluate ( );
    void record ( );
    PCReal evaluateAndRecord ( );
    void acceptModification ( );
    void rejectModification ( );
    void setupSystem ( ran* _pRan );
    void setupSystem ( );
    void saveState ( string& _filename );
    void saveBestState ( string& _filename );
    vector<optimizationTarget*> getBestStates ( ) { return itsBestStates; }
    vector<PCReal> getBestStateEvals ( ) { return itsBestStateEvals; }

    void addManipulator ( manipulator* _pManip, PCReal _weight = 1.0 ) { itsManipulators.push_back(_pManip); itsManipulatorWeights.push_back(_weight); }
    manipulator* getLastUsedManipulator ( ) { return pItsMostRecentManipulator; }

    void printEverything ( const bool& _deep=false, ostream& _os=cout );
    optimizationTarget* getTargetPointer ( ) { return pItsWorkingTarget; }

    void rejectAllFromList ( vector<manipulator*>& _manipulators );
    void manipulateTargetWith ( vector<manipulator*>& _manipulators );

#ifdef HAS_BOOST_SERIALIZE
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & itsManipulators;
        ar & itsManipulatorWeights;
        ar & pItsMostRecentManipulator;
        ar & itsBestStates;
        ar & itsBestStateEvals;
        ar & pItsWorkingTarget;
        ar & itsCurrentEvaluation;
    }
#endif
protected:
    PCIndex chooseManipulator ( ran* _pRan );

protected:
    vector<manipulator*>        itsManipulators;
    vector<PCReal>              itsManipulatorWeights;
    manipulator*                pItsMostRecentManipulator;
    vector<optimizationTarget*> itsBestStates;
    vector<PCReal>              itsBestStateEvals;
    optimizationTarget*         pItsWorkingTarget;
    PCReal                      itsCurrentEvaluation;
};
#endif
