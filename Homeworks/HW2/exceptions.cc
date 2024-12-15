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

#include "exceptions.h"
#include "generalio.h"

#ifdef EXCEPTIONS_VERBOSE
#define EXCEPTIONS_WAIT
#endif

myException::myException()
    : runtime_error("General runtime_error:  No message specified.")
{}
myException::myException(const myException& _rhs)
    : runtime_error(_rhs)
{
    throwingFunction = _rhs.throwingFunction;
    message =          _rhs.message;
}

myException::myException(const string& _throwingFunction, const string& _msg)
    : runtime_error(_throwingFunction + "::" + _msg)
{
    throwingFunction =  _throwingFunction;
    message = _msg;
#ifdef EXCEPTIONS_VERBOSE
    printEverything();
#endif
#ifdef EXCEPTIONS_WAIT
    PCGeneralIO::user_wait();
#endif
}

void myException::printEverything ( const bool& _deep, ostream& _os ) const
{
    _os << "EXCEPTION THROWN FROM: " <<  throwingFunction << endl;
    _os << "MSG: " << message << endl;
}

xNotFound::xNotFound() : myException()
{}
xNotFound::xNotFound(const xNotFound& _rhs) : myException(_rhs)
{}
xNotFound::xNotFound(const string& _throwingFunction, const string& _msg): myException(_throwingFunction,_msg)
{}

xInvalidSelection::xInvalidSelection() : myException()
{}
xInvalidSelection::xInvalidSelection(const xInvalidSelection& _rhs) : myException(_rhs)
{}
xInvalidSelection::xInvalidSelection(const string& _throwingFunction, const string& _msg): myException(_throwingFunction,_msg)
{}

xNotPDB::xNotPDB() : myException()
{}
xNotPDB::xNotPDB(const xNotPDB& _rhs) : myException(_rhs)
{}
xNotPDB::xNotPDB(const string& _throwingFunction, const string& _msg) : myException(_throwingFunction, _msg)
{}

xGeneralFailure::xGeneralFailure() : myException()
{}
xGeneralFailure::xGeneralFailure(const xGeneralFailure& _rhs) :myException(_rhs)
{}
xGeneralFailure::xGeneralFailure(const string& _throwingFunction, const string& _msg) : myException(_throwingFunction, _msg)
{}

xIOFailure::xIOFailure() : myException()
{}
xIOFailure::xIOFailure(const xIOFailure& _rhs) :myException(_rhs)
{}
xIOFailure::xIOFailure(const string& _throwingFunction, const string& _msg) : myException(_throwingFunction, _msg)
{}

xUnparseable::xUnparseable() : myException()
{}
xUnparseable::xUnparseable(const xUnparseable& _rhs) : myException(_rhs)
{}
xUnparseable::xUnparseable(const string& _throwingFunction, const string& _msg) : myException(_throwingFunction, _msg)
{}

xOutOfBounds::xOutOfBounds() : myException()
{}
xOutOfBounds::xOutOfBounds(const xOutOfBounds& _rhs) :myException(_rhs)
{}
xOutOfBounds::xOutOfBounds(const string& _throwingFunction, const string& _msg) : myException(_throwingFunction, _msg)
{}

xUninvertableMatrix::xUninvertableMatrix() : myException()
{}
xUninvertableMatrix::xUninvertableMatrix(const xUninvertableMatrix& _rhs) : myException(_rhs)
{}
xUninvertableMatrix::xUninvertableMatrix(const string& _throwingFunction, const string& _msg) : myException(_throwingFunction, _msg)
{}

xBuildFailure::xBuildFailure() : myException()
{}
xBuildFailure::xBuildFailure(const xBuildFailure& _rhs) : myException(_rhs)
{}
xBuildFailure::xBuildFailure(const string& _throwingFunction, const string& _msg) : myException(_throwingFunction, _msg)
{}
