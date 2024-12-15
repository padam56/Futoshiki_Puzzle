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

#include "twoVariableEnergyFunc.h"
#include "optimizationTarget.h"

#ifdef HAS_BOOST_SERIALIZE
BOOST_CLASS_EXPORT_GUID(twoVariableEnergyFunc, "twoVariableEnergyFunc")
#endif

//#define TWOVARENERGYFUNC_DEBUG

twoVariableEnergyFunc::twoVariableEnergyFunc ( )
    : optimizationTarget()
{
#ifdef TWOVARENERGYFUNC_DEBUG
    cout<< "Default twoVariableEnergyFunc constructor called" << endl;
#endif
    itsPos.push_back(0.0);
    itsPos.push_back(0.0);
}

twoVariableEnergyFunc::twoVariableEnergyFunc ( vector<PCReal> _position )
    : optimizationTarget()
{
#ifdef TWOVARENERGYFUNC_DEBUG
    cout<< "Specific twoVariableEnergyFunc constructor called" << endl;
#endif
    itsPos = _position;
}

twoVariableEnergyFunc::twoVariableEnergyFunc ( PCReal _x, PCReal _y )
    : optimizationTarget()
{
#ifdef TWOVARENERGYFUNC_DEBUG
    cout<< "Specific twoVariableEnergyFunc constructor called" << _x << "," << _y << ")" << endl;
#endif
    itsPos.push_back(_x);
    itsPos.push_back(_y);
}

twoVariableEnergyFunc::~twoVariableEnergyFunc ( )
{
#ifdef TWOVARENERGYFUNC_DEBUG
    cout<< "twoVariableEnergyFunc destructor called " << endl;
#endif
}

void twoVariableEnergyFunc::setDomain ( const PCReal& _minX, const PCReal& _maxX, const PCReal& _minY, const PCReal& _maxY )
{
    itsMinX = _minX;
    itsMaxX = _maxX;
    itsMinY = _minY;
    itsMaxY = _maxY;
}

void twoVariableEnergyFunc::movePosition ( const PCReal& _x, const PCReal& _y)
{
#ifdef TWOVARENERGYFUNC_DEBUG
    cout<< "twoVariableEnergyFunc movePosition called with (" << _x << "," << _y << ")" << endl;
#endif
    itsPos[0] = itsPos[0] + _x;
    itsPos[1] = itsPos[1] + _y;
}

void twoVariableEnergyFunc::printEverything ( const bool& _deep, ostream& _os )
{
    if (_os.good())
    {
        _os << "----------begin twoVariableEnergyFunc::printEverything()---------------" << endl;
        _os << "xyCoord == (" << itsPos[0] << "," << itsPos[1] << ")" << endl;
        _os << "---------- end twoVariableEnergyFunc::printEverything() ---------------" << endl;
    }
    else
        cerr << "ERROR -- Unable to execute twoVariableEnergyFunc::printEverything()!" << endl;
}

void twoVariableEnergyFunc::write ( const string& _filename ) const
{

    ofstream outFile( _filename.c_str() );
    if (!outFile)
    {
        cout << "ERROR: cannot write to file: " << _filename << endl;
        return;
    }

    outFile << "xyCoord == (" << itsPos[0] << "," << itsPos[1] << ")" << endl;
    outFile << "energy: "<< evaluate() << endl;

    outFile.close();
}

void twoVariableEnergyFunc::updateProbabilities ( )
{

}
