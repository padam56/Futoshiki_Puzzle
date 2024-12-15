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
#include "manipulator.h"

#ifndef TWOVAR_ENERGY_MANIPU_H
#define TWOVAR_ENERGY_MANIPU_H

class ran;
class optimizationTarget;

class twoVarEnergyManipulator: public manipulator
{
public:

    // Constructor and Destructor declaration
    twoVarEnergyManipulator ( );
    virtual ~twoVarEnergyManipulator ( );

	virtual void chooseModification (optimizationTarget* _pTarget, ran* _pRan );
	virtual void applyModification (optimizationTarget* _pTarget);
	virtual void acceptModification (optimizationTarget* _pTarget);
	virtual void rejectModification (optimizationTarget* _pTarget);

    virtual void reset ( );
    virtual void printEverything ( const bool& _deep=false, ostream& _os=cout ) const;

private:
#ifdef HAS_BOOST_SERIALIZE
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<manipulator>(*this);
        ar & itsdXdY;
    }
#endif

protected:
    vector<PCReal> itsdXdY;

};
#endif
