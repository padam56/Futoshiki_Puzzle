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

#include "twoVarEnergyManipulator.h"
#include "twoVariableEnergyFunc.h"
#include "ran.h"

#ifdef HAS_BOOST_SERIALIZE
BOOST_CLASS_EXPORT_GUID(twoVarEnergyManipulator, "twoVarEnergyManipulator")
#endif

#define TWOVARENERGYMANIP_DEBUG

twoVarEnergyManipulator::twoVarEnergyManipulator ( )
    : manipulator ( )
{
#ifdef TWOVARENERGYMANIP_DEBUG
    cout << "twoVarEnergyManipulator:: default constructor called" << endl;
#endif
	reset();
}

twoVarEnergyManipulator::~twoVarEnergyManipulator ( )
{
#ifdef TWOVARENERGYMANIP_DEBUG
    cout << "twoVarEnergyManipulator:: destructor called" << endl;
#endif
}

void twoVarEnergyManipulator::reset ( )
{
#ifdef TWOVARENERGYMANIP_DEBUG
    cout << "twoVarEnergyManipulator::reset called" << endl;
#endif
	manipulator::reset();
	itsdXdY.resize(0);
}

void twoVarEnergyManipulator::chooseModification (optimizationTarget* _pTarget, ran* _pRan )
{
	reset();
	PCReal delta = dynamic_cast<twoVariableEnergyFunc*>(_pTarget)->getDeltaRange();
#ifdef TWOVARENERGYMANIP_DEBUG
    cout << "twoVarEnergyManipulator::chooseModification called and delta range is " << delta << endl;
#endif
	PCReal dx = _pRan->getNext(-1.0*delta,delta);
	PCReal dy = _pRan->getNext(-1.0*delta,delta);
	itsdXdY.push_back(dx);
	itsdXdY.push_back(dy);
	setSuccessfulChoose(true);
}

void twoVarEnergyManipulator::applyModification (optimizationTarget* _pTarget)
{
	if (successfulChoose())
	{
    	PCReal dx = itsdXdY[0];
    	PCReal dy = itsdXdY[1];
    	(dynamic_cast<twoVariableEnergyFunc*>(_pTarget))->movePosition(dx,dy);
		setSuccessfulApply(true);
		return;
	}
	setSuccessfulApply(false);
    return;
}

void twoVarEnergyManipulator::acceptModification (optimizationTarget* _pTarget )
{
#ifdef TWOVARENERGYMANIP_DEBUG
    cout << "twoVarEnergyManipulator::acceptModification called" << endl;
#endif
}

void twoVarEnergyManipulator::rejectModification (optimizationTarget* _pTarget )
{
#ifdef TWOVARENERGYMANIP_DEBUG
    cout << "twoVarEnergyManipulator::rejectModification called" << endl;
#endif
    if (successfulChoose())
    {
#ifdef TWOVARENERGYMANIP_DEBUG
        cout << "manip is initialized!" << endl;
#endif
        (dynamic_cast<twoVariableEnergyFunc*>(_pTarget))->movePosition(-1.0*itsdXdY[0],-1.0*itsdXdY[1]);
    }
    else
    {
        string func = "twoVarEnergyManipulator::rejectModification()";
        string issue = "uninitialized";
#ifdef TWOVARENERGYMANIP_DEBUG
		cout << func << issue << endl;
#endif
        throw xNotFound(func,issue);
    }
}

void twoVarEnergyManipulator::printEverything ( const bool& _deep, ostream& _os ) const
{
	if (_os.good())
	{
   		_os << "----------begin twoVarEnergyManipulator::printEverything()---------------" << endl;
		if (successfulChoose())
		{
    		_os << "dXdY == (" << itsdXdY[0] << "," << itsdXdY[1] << ")" << endl;
			if (_deep)
				manipulator::printEverything(_deep, _os);
		}
    	_os << "----------end twoVarEnergyManipulator::printEverything()---------------" << endl;
	}
	else
		cerr << "ERROR -- Unable to execute twoVarEnergyManipulator::printEverything()!" << endl;
}
