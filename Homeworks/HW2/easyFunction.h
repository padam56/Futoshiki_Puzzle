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
#include "twoVariableEnergyFunc.h"

#ifndef EASY_FUNC_H
#define EASY_FUNC_H

class easyFunction : public twoVariableEnergyFunc
{
public:
    // Constructor and Destructor declaration
    easyFunction ( );
    easyFunction ( vector<PCReal> _position );
    easyFunction ( PCReal _x, PCReal _y );
    virtual ~easyFunction ( );

    // Accessors
    virtual PCReal evaluate ( );
    virtual PCReal evaluate ( ) const;
    static PCReal evaluate ( vector<PCReal> _pos );
    static PCReal evaluate ( PCReal _x, PCReal _y );

private:
#ifdef HAS_BOOST_SERIALIZE
    friend class boost::serialization::access;
    template<class Archive>
    void serialize ( Archive & ar, const unsigned int version )
    {
        ar & boost::serialization::base_object<twoVariableEnergyFunc>(*this);
    }
#endif

protected:
};
#endif
