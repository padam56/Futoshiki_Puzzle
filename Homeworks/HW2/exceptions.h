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

#ifndef PC_EXCEPTIONS_H
#define PC_EXCEPTIONS_H

class myException : public runtime_error
{
public:
    // Constructor and Destructor declaration
    myException ( );
    myException ( const myException& _rhs );
    myException ( const string& _throwingFunction, const string& _msg );
    ~myException ( ) throw () { }

    void printEverything ( const bool& _deep=false, ostream& _os=cout ) const;    

protected:
    string throwingFunction;
    string message;
};

class xNotFound: public myException
{
public:
    // Constructor and Destructor declaration
    xNotFound ( );
    xNotFound ( const xNotFound& _rhs );
    xNotFound ( const string& _throwingFunction, const string& _msg );
    virtual ~xNotFound ( ) throw ( ) { }
};

class xInvalidSelection: public myException
{
public:
    // Constructor and Destructor declaration
    xInvalidSelection ( );
    xInvalidSelection ( const xInvalidSelection& _rhs );
    xInvalidSelection ( const string& _throwingFunction, const string& _msg );
    virtual ~xInvalidSelection ( ) throw ( ) { }
};

class xNotPDB: public myException
{
public:
    // Constructor and Destructor declaration
    xNotPDB ( );
    xNotPDB ( const xNotPDB& _rhs );
    xNotPDB ( const string& _throwingFunction, const string& _msg );
    virtual ~xNotPDB ( ) throw ( ) { }
};

class xGeneralFailure: public myException
{
public:
    // Constructor and Destructor declaration
    xGeneralFailure ( );
    xGeneralFailure ( const xGeneralFailure& _rhs );
    xGeneralFailure ( const string& _throwingFunction, const string& _msg );
    virtual ~xGeneralFailure ( ) throw ( ) { }
};

class xIOFailure: public myException
{
public:
    // Constructor and Destructor declaration
    xIOFailure ( );
    xIOFailure ( const xIOFailure& _rhs );
    xIOFailure ( const string& _throwingFunction, const string& _msg );
    virtual ~xIOFailure ( ) throw ( ) { }
};

class xUnparseable: public myException
{
public:
    // Constructor and Destructor declaration
    xUnparseable ( );
    xUnparseable ( const xUnparseable& _rhs );
    xUnparseable ( const string& _throwingFunction, const string& _msg );
    virtual ~xUnparseable ( ) throw ( ) { }
};

class xOutOfBounds: public myException
{
public:
    // Constructor and Destructor declaration
    xOutOfBounds ( );
    xOutOfBounds ( const xOutOfBounds& _rhs );
    xOutOfBounds ( const string& _throwingFunction, const string& _msg );
    virtual ~xOutOfBounds ( ) throw ( ) { }
};

class xUninvertableMatrix: public myException
{
public:
    // Constructor and Destructor declaration
    xUninvertableMatrix ( );
    xUninvertableMatrix ( const xUninvertableMatrix& _rhs );
    xUninvertableMatrix ( const string& _throwingFunction, const string& _msg );
    virtual ~xUninvertableMatrix ( ) throw ( ) { }
};

class xBuildFailure: public myException
{
public:
    // Constructor and Destructor declaration
    xBuildFailure ( );
    xBuildFailure ( const xBuildFailure& _rhs );
    xBuildFailure ( const string& _throwingFunction, const string& _msg );
    virtual ~xBuildFailure ( ) throw ( ) { }
};

#endif
