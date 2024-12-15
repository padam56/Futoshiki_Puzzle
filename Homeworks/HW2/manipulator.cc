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

#include "manipulator.h"
#include "optimizationTarget.h"

#ifdef HAS_BOOST_SERIALIZE
BOOST_CLASS_EXPORT_GUID(manipulator, "manipulator")
#endif

/**
   manipulator default constructor
   sets itsWeight to default of 1.0
   sets isLoadedFlag to false
   sets isAppliedFlag to false
   sets maximumTryDepth to default of 10
 */
manipulator::manipulator ( )
{
    itsWeight = 1.0;
    isLoadedFlag = false;
    isAppliedFlag = false;
    maximumTryDepth = 10;
}

/**
   manipulator copy constructor
 */
manipulator::manipulator ( const manipulator& _rhs )
{
    itsWeight = _rhs.itsWeight;
    isLoadedFlag = _rhs.isLoadedFlag;
    isAppliedFlag = _rhs.isAppliedFlag;
    maximumTryDepth = _rhs.maximumTryDepth;
}

/**
   manipulator destructor
 */
manipulator::~manipulator ( )
{

}

/**
   manipulator resetting method - sets isLoadedFlag and isAppliedFlag to false
 */
void manipulator::reset ( )
{
    isLoadedFlag = false;
    isAppliedFlag = false;
}

/**
   method prints all information in manipulator
   @param[in]     _deep boolean value - should I also call printEverything method for all my contained classes?
   @param[in]     _os  a reference to a ostream to which the output should be piped
 */
void manipulator::printEverything ( const bool& _deep, ostream& _os ) const
{
    if (_os.good())
    {
        _os << "----------begin manipulator::printEverything()---------------" << endl;
        _os << "          isLoadedFlag: " << isLoadedFlag << endl;
        if (isLoadedFlag)
        {
            _os << "          itsWeight: " << itsWeight << endl;
            _os << "          isAppliedFlag: " << isAppliedFlag << endl;
        }
        _os<< "----------end manipulator::printEverything()---------------" << endl;
    }
    else
        cerr << "ERROR -- Unable to execute manipulator::printEverything()!" << endl;
}
