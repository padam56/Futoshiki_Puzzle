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

/**
 * @file manipulator.h
 * Header file for the class manipulator.
 * Manipulator is a base class from which all the different manipulators are
 * inherit - contains method signatures and common instance variables of all
 * manipulators. Abstract class that cannot be instantiated.
 *
 * @author Christopher M. Summa
 */

#include "typedef.h"
#include "optimizationTarget.h"
#include "enums.h"

#ifndef MANIPULATOR_H
#define MANIPULATOR_H

class ran;

class manipulator
{
public:

    // Constructor and Destructor declaration
    manipulator ( );
    manipulator ( const manipulator& _rhs );
    virtual ~manipulator ( );

    virtual void chooseModification ( optimizationTarget* _pTarget, ran* _pRan ) = 0;
    virtual void applyModification ( optimizationTarget* _pTarget ) = 0;
    virtual void acceptModification ( optimizationTarget* _pTarget ) = 0;
    virtual void rejectModification ( optimizationTarget* _pTarget ) = 0;
    virtual void printEverything ( const bool& _deep=false, ostream& _os=cout ) const;

    virtual void reset();

    bool successfulApply ( ) const { return isAppliedFlag; }
    bool successfulChoose ( ) const { return isLoadedFlag; }
    void setSuccessfulChoose ( bool val ) { isLoadedFlag = val; }
    void setSuccessfulApply ( bool val ) { isAppliedFlag = val; }
    void   setWeight ( PCReal _weight ) { itsWeight = _weight; }
    PCReal getWeight ( ) const { return itsWeight; }

    void setMaximumTryDepth ( unsigned int _depth ) { maximumTryDepth = _depth; }
    unsigned int getMaximumTryDepth ( ) const { return maximumTryDepth; }

private:
#ifdef HAS_BOOST_SERIALIZE
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & itsWeight;
        ar & maximumTryDepth;
        ar & isLoadedFlag;
        ar & isAppliedFlag;
    }
#endif

protected:

    PCReal itsWeight; /*!< The weight (0.0 - 1.0) assigned to this mainpulator when making a random choice amongst many manipulators */
    unsigned int maximumTryDepth; /*!< How many times to attempt to make a modification before failing */
    bool isLoadedFlag; /*!< Has a valid choice been made? */
    bool isAppliedFlag; /*!< Has this manipulator actual made its change? */

};
#endif
