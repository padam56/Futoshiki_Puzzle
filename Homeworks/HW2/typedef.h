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


#include <csignal>
#include <cmath>
#include <float.h>
#include "enums.h"

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>

#ifdef HAS_BOOST
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/unordered_map.hpp>
#endif

#ifdef HAS_BOOST_SERIALIZE
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/set.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>
#else
#include <set>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#endif

#ifdef HAS_MPI_AND_BOOST
#include <boost/mpi.hpp>
namespace mpi = boost::mpi;
#endif

#ifndef TYPEDEF_H
#define TYPEDEF_H
#define DOUBLE_PRECISION

using namespace std;
typedef unsigned int UInt;

#ifndef DOUBLE_PRECISION
typedef float PCReal;
#define PCREAL_MAX FLT_MAX
#define PCREAL_MIN FLT_MIN
#endif

#ifdef DOUBLE_PRECISION
typedef double PCReal;
#define PCREAL_MAX DBL_MAX
#define PCREAL_MIN DBL_MIN
#endif

typedef int PCSerialNumber;
typedef unsigned int PCIndex;

typedef vector<PCReal> DouVec;
typedef vector<string> StrVec;

#ifdef HAS_BOOST
typedef boost::numeric::ublas::vector<PCReal> realVec;
typedef boost::numeric::ublas::matrix<PCReal> realMat;
typedef boost::numeric::ublas::vector<unsigned int> UIntVec;
typedef boost::numeric::ublas::matrix<unsigned int> UIntMat;
#else
typedef std::vector<PCReal> realVec;
typedef std::vector<vector<PCReal> > realMat;
typedef std::vector<unsigned int> UIntVec;
typedef std::vector< vector< unsigned int> > UIntMat;
#endif

typedef map<string, string>                stringToStringMap;
typedef map<string, PCReal>                stringToRealMap;
typedef map<string, vector<PCReal> >       stringToRealVecMap;
typedef map<string, vector<unsigned int> > stringToUIntVecMap;
typedef map<string, unsigned int>          stringToUIntMap;

const PCReal PI = 3.14159265358979323846264338327950288;
const PCReal FOURTHIRDS = 4.0/3.0;
const PCReal RT = 0.582;    // RT at 293K - value is in kcal per mol
const PCReal COORDINATE_TOLERANCE = 0.0001;

#include "exceptions.h"

class realVecGenerator
{
public:
    realVecGenerator ( ) { }
    realVecGenerator ( PCReal _x )
    {
#ifdef __REALVECGEN_DEBUG
        cout << "realVecGenerator::realVecGenerator constructor ( _x ) called w/: " << _x << endl;
        cout << "itsVec.size(): " << itsVec.size() << endl;
#endif
        itsVec.push_back(_x);
#ifdef __REALVECGEN_DEBUG
        cout << "itsVec.size(): " << itsVec.size() << endl;
#endif
    }

    realVecGenerator& operator() ( PCReal _x )
    {
#ifdef __REALVECGEN_DEBUG
        cout << "realVecGenerator::operator() ( _x ) called w/: " << _x << endl;
        cout << "itsVec.size(): " << itsVec.size() << endl;
#endif
        itsVec.push_back(_x);
#ifdef __REALVECGEN_DEBUG
        cout << "itsVec.size(): " << itsVec.size() << endl;
#endif
        return *this;
    }
    realVec getRealVec ( )
    {
#ifdef __REALVECGEN_DEBUG
        cout << "realVecGenerator::getRealVec() called" << endl;
        cout << "itsVec.size(): " << itsVec.size() << endl;
#endif
        realVec result(itsVec.size(),0.0);
#ifdef __REALVECGEN_DEBUG
        cout << result << endl;
#endif

        for (PCIndex i = 0; i < itsVec.size(); i++)
            result[i] = itsVec[i];

#ifdef __REALVECGEN_DEBUG
        cout << "  returning > " <<
        cout << result << endl;
#endif
        return result;
    }

private:
    vector<PCReal> itsVec;
};
#endif
