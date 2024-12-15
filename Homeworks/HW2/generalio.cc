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

#ifdef HAS_BOOST
#include "boost/regex.hpp"
#endif
#include "generalio.h"
#include "exceptions.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdio.h>

string PCGeneralIO::getEnvironmentVariable ( const string& _evname )
{
    const char* convEVName = _evname.c_str();
    char* pEVString = getenv(convEVName);
    if (pEVString == 0)
    {    cout << "Environment variable " << _evname << " undefined." << endl;
        cout << "Please set it properly and re-execute the program." << endl;
        exit(1);
    }
    string EVstring = charToString(pEVString);
    return EVstring;
}

string PCGeneralIO::getUserInputWithPrompt( const string& _prompt)
{
    cout << _prompt << " ";
    string response;
    getline(cin,response);
    return response;
}

string PCGeneralIO::charToString ( char* cPointer )
{
    string EVstring;
    for (;*cPointer != '\0'; cPointer++)
    {
        EVstring += *cPointer;
    }
    return EVstring;
}

string PCGeneralIO::intToString ( int _theInteger )
{
    ostringstream ostr;
    ostr << _theInteger;
    string s(ostr.str());
    return s;
}

bool PCGeneralIO::compareToDelimiters ( const string& _s )
{
    string space = " ";
    string comma = ",";
    string semi = ";";
    string colon = ":";
    string tab = "\t";
    if ( _s == space || _s == comma || _s == semi ||
        _s == colon || _s == tab)
    {    return true;
    }
    return false;
}

bool PCGeneralIO::compareToDelimiter ( const string& _s, const string&  _delimiter )
{
	//cout << "comparing " << _s << " and " << _delimiter << endl;
    if ( _s  == _delimiter)
    {    
		//cout << "same!" << endl;
		return true;
    }
    return false;
}

bool PCGeneralIO::contains ( const string& _full, const string& _sub)
{
    int fullsize = _full.size();
    int subsize  = _sub.size();
    for (unsigned int i=0; i<fullsize-subsize+1; i++)
    {
        string temp = _full.substr(i,subsize);
        if (temp == _sub)
            return true;
    }
    return false;
}

bool PCGeneralIO::hasNonWhitespaceCharacters( const string& _s )
{
    string space = " ";
    string tab = "\t";
    string newline = "\n";
    for (unsigned int i=0; i<_s.size(); i++)
    {
        string tempchar = _s.substr(i,1);
        if (tempchar != space && tempchar != tab && tempchar != newline)
            return true;
    }
    return false;
}

vector<string> PCGeneralIO::parseString ( const string& _longString, const unsigned int _fieldWidth )
{
    vector<string> stringVec;
    string tempstring;
    string shortstring;
    bool startOfWordFound = false;
    if (_fieldWidth == 0)
    {
        unsigned int i=0;
        while (i< _longString.size())
        {
            shortstring = _longString.substr(i,1);
            if ( !(compareToDelimiters(shortstring) ) )
            {
                if (startOfWordFound)
                {
                    tempstring += shortstring;
                }
                else
                {
                    tempstring += shortstring;
                    startOfWordFound = true;
                }
                i++;
                continue;
            }
            else
            {
                if (!startOfWordFound)
                {
                    i++;
                    continue;
                }
                else
                {
                    startOfWordFound = false;
                    stringVec.push_back(tempstring);
                    tempstring = "";
                }
            }
            i++;
        }
        if (startOfWordFound)
            stringVec.push_back(tempstring);
        return stringVec;
    }
    else
    {
        unsigned int len = _longString.size();
        unsigned int j=0;
        unsigned int currentPos = j;
        while (j + _fieldWidth <len)
        {
            //cout << "in while loop" << endl;
            tempstring = stripLeadingAndTrailingSpaces(_longString.substr(j,_fieldWidth));
            stringVec.push_back(tempstring);
            j+= _fieldWidth;
            currentPos = j;
        }
        //cout << "outside of while loop" << endl;
        if (currentPos < len)
        {
            tempstring = stripLeadingAndTrailingSpaces(_longString.substr(currentPos,(len-currentPos)));
            stringVec.push_back(tempstring);
        }
    }
    return stringVec;
}

vector<string> PCGeneralIO::splitString ( const string& _longString, const string& _delimiter )
{
	//cout << "in splitString " << _longString << " " <<  _delimiter << endl;
    vector<string> stringVec;
    string tempstring;
    string shortstring;
    bool startOfWordFound = false;
        unsigned int i=0;
        while (i< _longString.size())
        {
            shortstring = _longString.substr(i,1);
            if ( !(compareToDelimiter(shortstring,_delimiter) ) )
            {
                if (startOfWordFound)
                {
                    tempstring += shortstring;
                }
                else
                {
                    tempstring += shortstring;
                    startOfWordFound = true;
                }
                i++;
                continue;
            }
            else
            {
				//cout << "delimiter found" << endl;
                if (!startOfWordFound)
                {
                    i++;
                    continue;
                }
                else
                {
                    startOfWordFound = false;
                    stringVec.push_back(tempstring);
                    tempstring = "";
                }
            }
            i++;
        }
        if (startOfWordFound)
            stringVec.push_back(tempstring);
		//cout << "end of splitString" << endl;
        return stringVec;
}

#ifdef HAS_BOOST
vector<string> PCGeneralIO::splitStringWithRegex ( const string& _longString, const string& _regex )
{
    boost::regex re(_regex);
    boost::sregex_token_iterator i(_longString.begin(), _longString.end(), re, -1);
    boost::sregex_token_iterator j;
    vector<string> tokenList;

    while(i != j)
    {
        string curr = *i++;
        tokenList.push_back(curr);
    }

    return tokenList;
}

vector<string> PCGeneralIO::tokenizeString ( const string& _s )
{
    string whiteSpaceRegex = "\\s+";
    return splitStringWithRegex(_s,whiteSpaceRegex);
}

#endif

/*
vector<string> PCGeneralIO::splitString ( const string& _longString, const char _delimiter )
{
    vector<string> stringVec;
    string delimiter = "" + _delimiter;
    string tempstring;
    string shortstring;
    bool startOfWordFound = false;
        unsigned int i=0;
        while (i< _longString.size())
        {
            shortstring = _longString.substr(i,1);
            if ( !(shortstring == delimiter) )
            {
                if (startOfWordFound)
                {
                    tempstring += shortstring;
                }
                else
                {
                    tempstring += shortstring;
                    startOfWordFound = true;
                }
                i++;
                continue;
            }
            else
            {
                if (!startOfWordFound)
                {
                    i++;
                    continue;
                }
                else
                {
                    startOfWordFound = false;
                    stringVec.push_back(tempstring);
                    tempstring = "";
                }
            }
            i++;
        }
        if (startOfWordFound)
            stringVec.push_back(tempstring);
        return stringVec;
}
*/

string PCGeneralIO::stripLeadingAndTrailingDelimiter ( const string& _s, const string& _delimiter )
{
    // find first non-space character in _s
    int lengthOfS = _s.size();
    int firstNonDelChar = 0;
    int lastNonDelChar = 0;
    for (int i=0; i<lengthOfS; i++)
    {
        if (_s.substr(i,1) != _delimiter)
        {
            firstNonDelChar = i;
            break;
        }
    }
    for (int i=lengthOfS-1; i>=0; i--)
    {
        if (_s.substr(i,1) != _delimiter)
        {
            lastNonDelChar = i;
            break;
        }
    }
//    cout << "firstNonSpaceChar= " << firstNonSpaceChar << endl;
//    cout << "lastNonSpaceChar= " << lastNonSpaceChar << endl;
    int length = (lastNonDelChar - firstNonDelChar) + 1;
//    cout << "length= " << length << endl;
    string newstring = "";
    if (length > 0)
    {
        newstring = _s.substr(firstNonDelChar,length);
    }
    return newstring;
}

string PCGeneralIO::stripLeadingAndTrailingSpaces ( const string& _s )
{
    // find first non-space character in _s
    int lengthOfS = _s.size();
    int firstNonSpaceChar = 0;
    int lastNonSpaceChar = 0;
    for (int i=0; i<lengthOfS; i++)
    {
        if (_s.substr(i,1) != " ")
        {
            firstNonSpaceChar = i;
            break;
        }
    }
    for (int i=lengthOfS-1; i>=0; i--)
    {
        if (_s.substr(i,1) != " ")
        {
            lastNonSpaceChar = i;
            break;
        }
    }
//    cout << "firstNonSpaceChar= " << firstNonSpaceChar << endl;
//    cout << "lastNonSpaceChar= " << lastNonSpaceChar << endl;
    int length = (lastNonSpaceChar - firstNonSpaceChar) + 1;
//    cout << "length= " << length << endl;
    string newstring = "";
    if (length > 0)
    {
        newstring = _s.substr(firstNonSpaceChar,length);
    }
    return newstring;
}

string PCGeneralIO::removeAllWhitespace( const string& _s)
{
    int lengthOfS = _s.size();
    string newstring = "";
    for (int i=0; i<lengthOfS; i++)
    {
        if (_s.substr(i,1) != "\t" && _s.substr(i,1) != "\n" && _s.substr(i,1) != " ")
        {
            newstring += _s.substr(i,1);
        }
    }
    return newstring;
}

string PCGeneralIO::stripQuotationMarks ( const string& _s )
{
    int lengthOfS = _s.size();
    string newstring = "";
    for (int i=0; i<lengthOfS; i++)
    {
        if (_s.substr(i,1) != "\"" && _s.substr(i,1) != "\'")
        {
            newstring += _s.substr(i,1);
        }
    }
    return newstring;
}

PCReal PCGeneralIO::stringToReal ( const string& _s )
{

    PCReal theReal = 0.0;
    if (isNumeric(_s))
    {
        sscanf(_s.c_str(), "%lf", &theReal);
    }
    else
    {
        string func = "PCGeneralIO::stringToReal";
        string err = "Unable to convert string to a real: " + _s;;
        throw xIOFailure(func,err);
    }
    return theReal;
}

int PCGeneralIO::stringToInt ( const string& _s )
{
    // this code causes the following memory error:
    //MallocDebug: free: target application attempted to free pointer that is not pointing to a malloc block: 0x1500140
    //MallocDebug: Call stack: (find symbols with /usr/bin/atos)
    //MallocDebug: Put a breakpoint at malloc_printf to diagnose.
    //stack backtrace: 0x0024be0c 0x0024bef8 0x0024bfe4 0x002476dc 0x0022e0dc 0x00218c78 0x0000b320 0x000030bc 0x00002a94 0x8fe1a558
    //MallocDebug: The address is not in memory used by the heap.
    /*
    istringstream i(_s);
    int x;
    if (i >> x)
        return x;
    cout << "Error reported from PCReal stringToInt(string& _s)" << endl;
    cout << "Unable to convert string to an int: " <<  _s << endl;
    return 0;
    */
    int theInt = 0;
    if (isNumeric(_s))
    {
        sscanf(_s.c_str(), "%i", &theInt);
    }
    else
    {
//        cout << "Error reported from PCReal stringToInt(string& _s)" << endl;
//        cout << "Unable to convert string to an int: " <<  _s << endl;
        string func = "PCGeneralIO::stringToInt";
        string err = "Unable to convert string to an int: " + _s;
        throw xIOFailure(func,err);
    }
    return theInt;
}

bool PCGeneralIO::stringToBool ( const string& _s )
{
    string s = stringToLower(_s);
    if (s == "true" || s == "t" || s=="y" || s=="yes")
        return true;
    if (s == "false" || s == "f" || s=="n" || s == "no")
        return false;
    string func = "PCGeneralIO::stringToBool";
    string err = "Unable to convert string to a bool: " + _s;
    throw xUnparseable(func,err);
}

bool PCGeneralIO::isNumeric ( const string& _s )
{
    string tempstring = "";
    for (unsigned int i=0; i<_s.size(); i++)
    {
        if (_s.substr(i,1) != " ")
        {
            tempstring += _s.substr(i,1);
        }
    }

    for (unsigned int i=0; i< tempstring.size(); i++)
    {
        string sub = tempstring.substr(i,1);
        if ( sub != "0" &&
            sub != "1" &&
            sub != "2" &&
            sub != "3" &&
            sub != "4" &&
            sub != "5" &&
            sub != "6" &&
            sub != "7" &&
            sub != "8" &&
            sub != "9" &&
            sub != "." &&
            sub != "e" &&
            sub != "-" &&
            sub != "+")
        {    return false;
        }
    }
    return true;
}

vector<unsigned int> PCGeneralIO::findAllInstancesInString ( const string& _bigString,
                                              const string& _searchString )
{
    unsigned int bigSize = _bigString.size();
    unsigned int smallSize = _searchString.size();
    if (smallSize > bigSize)
    {
        cerr << "Error reported from findAllInstancesInString" << endl;
        cerr << "long string to be searched should be first argument" << endl;
    }
    vector<unsigned int> theIndices;
    unsigned int currentStartIndex = 0;
    while ( (currentStartIndex + smallSize - 1) < bigSize)
    {
        if (_bigString.substr(currentStartIndex,smallSize) == _searchString)
        {
            theIndices.push_back(currentStartIndex);
            currentStartIndex += smallSize;
        }
        else
        {
            currentStartIndex++;
        }
    }
    return theIndices;
}

bool PCGeneralIO::matchSubstring ( const string& _bigstring,
                 const string& _searchstring )
{
    unsigned int lengthOfLong = _bigstring.length();
    unsigned int lengthOfShort = _searchstring.length();
    if (lengthOfShort > lengthOfLong)
        return false;

    if (lengthOfShort == lengthOfLong)
        if (_searchstring == _bigstring)
            return true;

    for (unsigned int i=0; i< lengthOfLong - lengthOfShort + 1; i++)
    {
		//cout << "searching for /'" << _searchstring << "/' in " << _bigstring.substr(i,lengthOfShort) << endl;
        if (_searchstring == _bigstring.substr(i,lengthOfShort) )
            return true;
    }
    return false;
}

bool PCGeneralIO::matchRegex ( const string& _bigstring,
                 const string& _regexstring )
{
    // NOTE: this is not working yet - it turned out to be unnecessary for charmm

    //    the CHARMM data file Regular expression wildcards are defined as follows:
    //    * - any number of characters or no character
    //    % - any character
    //        + - any number of characters

    unsigned int lengthOfLong = _bigstring.length();
    unsigned int lengthOfRegex = _regexstring.length();

    cout << "in matchRegex comparing : " << _bigstring << " to " << _regexstring << endl;
    string asterisk = "*";

    if (lengthOfRegex > lengthOfLong && !matchSubstring(_bigstring,asterisk))
        return false;
    unsigned int c1 = 0;
    unsigned int c2 = 0;
    //bool tempreturnval = true;
    while (c1 < lengthOfLong && c2 < lengthOfRegex)
    {
        string b1 = _bigstring.substr(c1,1);
        string r1 = _regexstring.substr(c2,1);
        cout << c1 << "\t" << c2 << "\t" << b1 << "\t" << r1 << "\t";
        if (b1 == r1)
        {
            cout << "equal 1" << endl;
            c1++; c2++;
        }
        else if (r1 == "%")
        {
            cout << "equal 2" << endl;
            c1++; c2++;
        }
        else if (r1 == "+")
        {
            // there must be more characters in bigstring
            if (c1 < lengthOfLong-1)
            {
                cout << "equal 3" << endl;
                c1++;
            }
        }
        else if (r1 == "*")
        {
            cout << "equal 4" << endl;
            c1++;
        }
        else
        {
            cout << "false" << endl;
            return false;
        }
    }
    cout << "true" << endl;
    return true;
}

#define WAIT_MSG "press enter to continue..."

#define WAIT_MSG "press enter to continue..."

void PCGeneralIO::user_wait ( )
{
  int c;
  cout << WAIT_MSG << endl;
  /* eat up characters until a newline or eof */
  do
  {
    c = getchar();
    if(c == EOF) break;
  } while(c != '\n');
}

string PCGeneralIO::stringToUpper ( const string& _original )
{
	string fixed;
    for (unsigned int i=0; i<_original.length(); i++)
    {
        fixed += toupper(_original[i]);
    }
    return fixed;
}

string PCGeneralIO::stringToLower ( const string& _original )
{
	string fixed;
    for (unsigned int i=0; i<_original.length(); i++)
    {
        fixed += tolower(_original[i]);
    }
    return fixed;
}

