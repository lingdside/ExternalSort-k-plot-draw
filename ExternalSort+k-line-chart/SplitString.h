#ifndef SPLITSTRING_H
#define SPLITSTRING_H
#include<stock.h>
#include<string>
using namespace std;

Stock US_Split0(string s);
simstock US_Split1(string s);
Stock US_Split2(string s);
string yrmth(string s);
bool Splitsharpe(string s,string syr,string &sym,double &shar);

#endif // SPLITSTRING_H
