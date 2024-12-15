/******************************************
*                                         *
*               PROTCAD                   *
*     PROTein Computer Assisted Design    *
*                                         *
*          Copyright 2002,2011            *
*        Christopher Mark Summa           *
*                 and                     *
*     The University of New Orleans       *
*       New Orleans, LA 70148             *
*                                         *
******************************************/

#include "typedef.h"
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <algorithm>

#ifndef PCGENERALIO_H
#define PCGENERALIO_H

namespace PCGeneralIO
{
    string getEnvironmentVariable ( const string& _evname );

    string charToString ( char* cPointer );

    string intToString ( int _theInteger );

    bool compareToDelimiters ( const string& _s );

    bool compareToDelimiter ( const string& _s, const string& _delimiter );

    bool contains ( const string& _full, const string& _sub);

    vector<string> parseString ( const string& _s, const unsigned int _fieldWidth = 0 );

    vector<string> splitString ( const string& _s, const string& _delimiter );

#ifdef HAS_BOOST
    // NOTE: THIS IS NOT A FULLY FUNCTIONAL REGULAR EXPRESSION ENGINE
    // I HAVE ONLY IMPLEMENTED THE BITS I NEEDED FOR FUNCTIONALITY IN THE PROTCAD PACKAGE
    vector<string> splitStringWithRegex ( const string& _s, const string& _regex );

    vector<string> tokenizeString ( const string& _s );
#endif

    PCReal stringToReal ( const string& _s );

    int stringToInt ( const string& _s );

    bool stringToBool ( const string& _s );

    string stripLeadingAndTrailingDelimiter ( const string& _s, const string& _delimiter );

    string stripLeadingAndTrailingSpaces ( const string& _s );

    string removeAllWhitespace( const string& _s);

    string stripQuotationMarks ( const string& _s );

    bool isNumeric ( const string& _s );

    bool hasNonWhitespaceCharacters( const string& _s );

    vector<unsigned int> findAllInstancesInString ( const string& _bigString,
                          const string& _searchString );

    string stringToUpper ( const string& _original );

    string stringToLower ( const string& _original );

    string getUserInputWithPrompt( const string& _prompt);    

// these are currently not fully implented and are merely helpers for other methods - do not use!!!!

    bool matchSubstring (const string& _bigstring, const string& _searchstring );

    bool matchRegex ( const string& _bigstring, const string& _regexstring );

    void user_wait ( );
}
#endif
