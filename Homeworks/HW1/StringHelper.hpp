#include <string>
#include <sstream>
#include <vector>
#include <iostream>

#ifndef STRING_HELPER
#define STRING_HELPER

using namespace std;
 
inline vector<string> split (const string &s, char delimiter) {
    vector<string> result;
    stringstream ss (s);
    string token;
    while (getline (ss, token, delimiter)) {
        result.push_back(token);
    }
    return result;
}



inline bool isNumeric ( const string& _s )
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

inline int stringToInt ( const string& _s ) {
    int theInt = 0;
    if (isNumeric(_s))
    {
        sscanf(_s.c_str(), "%i", &theInt);
    }
    else
    {
        cerr << "Error reported from PCReal stringToInt(string& _s)" << endl;
        cerr << "Unable to convert string to an int: " <<  _s << endl;
    }
    return theInt;
}

#endif
