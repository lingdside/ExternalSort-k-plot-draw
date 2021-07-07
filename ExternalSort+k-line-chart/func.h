#ifndef FUNC_H
#define FUNC_H

#include<string>
#include<algorithm>

#include "stock.h"
using namespace std;

static inline void ltrim(string &s)
{
    s.erase(s.begin(), find_if(s.begin(), s.end(),not1(ptr_fun<int, int>(isspace))));
}

static inline void rtrim(string &s)
{
    s.erase(find_if(s.rbegin(), s.rend(),not1(ptr_fun<int, int>(isspace))).base(), s.end());
}

static inline void trim(string &s)
{
    ltrim(s);
    rtrim(s);
}

bool readoneline(ifstream & fin,string & s);

#endif // FUNC_H
