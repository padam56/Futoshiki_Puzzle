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

#include "typedef.h"
#include "optimizationTarget.h"

#ifndef TWO_VAR_ENERGY_FUNC_H
#define TWO_VAR_ENERGY_FUNC_H

class twoVariableEnergyFunc : public optimizationTarget
{
public:
    // Constructor and Destructor declaration
    twoVariableEnergyFunc ( );
    twoVariableEnergyFunc ( vector<PCReal> _position );
    twoVariableEnergyFunc ( PCReal _x, PCReal _y );
    virtual ~twoVariableEnergyFunc ( );

    // Accessors
    virtual PCReal evaluate ( ) { return 0.0; };
    virtual PCReal evaluate ( ) const { return 0.0; };
    virtual void write ( const string& _filename ) const;
    virtual void updateProbabilities ( );

    twoVariableEnergyFunc* getCopy ( ) { return new twoVariableEnergyFunc(*this); }

public:
    void setDomain ( const PCReal& _minX, const PCReal& _maxX, const PCReal& _minY, const PCReal& _maxY );
    void movePosition ( const PCReal& _x, const PCReal& _y);
    //PCReal schaffer ( const vector<PCReal>& _pos ) const;
    void setDeltaRange ( const PCReal _delta ) { itsDeltaRange = _delta;}
    PCReal getDeltaRange ( ) const { return itsDeltaRange; }
    virtual void printEverything ( const bool& _deep=false, ostream& _os=cout );

private:
#ifdef HAS_BOOST_SERIALIZE
    friend class boost::serialization::access;
    template<class Archive>
    void serialize ( Archive & ar, const unsigned int version )
    {
        ar & boost::serialization::base_object<optimizationTarget>(*this);
        ar & itsPos;
        ar & itsDeltaRange;
        ar & itsMinX;
        ar & itsMaxX;
        ar & itsMinY;
        ar & itsMaxY;
    }
#endif

protected:
    vector<PCReal> itsPos;
    PCReal itsDeltaRange;
    PCReal itsMinX;
    PCReal itsMaxX;
    PCReal itsMinY;
    PCReal itsMaxY;
};
#endif
