/******************************************
*                                         *
*               PROTCAD                   *
*     PROTein Computer Assisted Design    *
*                                         *
*          Copyright 2002,2011            *
*        Christopher Mark Summa           *
*                 and                     *
*	 The University of New Orleans        *
*       New Orleans, LA 70148             *
*                                         *
******************************************/

#include "mainInclude.h"

int main ( int argc, char* argv[] )
{
	if (argc != 7)
	{
		cout << "Usage: mcoptimizer xMin[real] xMax[real] yMin[real] yMax[real] xGuess[real] yGuess[real]" << endl;
		return 1;
	}
    PCReal xMin = PCGeneralIO::stringToReal(argv[1]);
    PCReal xMax = PCGeneralIO::stringToReal(argv[2]);
    PCReal yMin = PCGeneralIO::stringToReal(argv[3]);
    PCReal yMax = PCGeneralIO::stringToReal(argv[4]);
    PCReal xGuess = PCGeneralIO::stringToReal(argv[5]);
    PCReal yGuess = PCGeneralIO::stringToReal(argv[6]);


    // build the funcion object to optimize
    // easyFunction* pOptimizationFunction = new easyFunction(xGuess, yGuess);
    boothFunction* pOptimizationFunction = new boothFunction(xGuess, yGuess);

    // set the domain to be explored
    pOptimizationFunction->setDomain(xMin,xMax,yMin,yMax);    

    pOptimizationFunction->setDeltaRange(5.0);

    // build a random number generator object
    ran* pRan = new ran3();

    // build an optimizationSystem object - this is the thing the algorithm operates on
    // and is a combination of the thing to be optimized and the ways in which the system
    // can me modified (which are modeled as manipulator objects)
    optimizationSystem* pOptSystem = new optimizationSystem(pOptimizationFunction);

    // add a manipulator that knows how to change the state of two-variable functions
    // i.e. but choosing a deltaX and deltaY
    pOptSystem->addManipulator( new twoVarEnergyManipulator() );

    // build a serial monte carlo algorithm object, and give it the optimization system to work
    // on and a random number generator
    MCSerialAlgorithm* pMonteCarlo = new MCSerialAlgorithm(pOptSystem, pRan);

    // tell it to run for 1000 steps at temperature 300K

    pMonteCarlo->run(300,1000);

	return 0;
}