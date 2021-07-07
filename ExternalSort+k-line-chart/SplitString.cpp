#include "stock.h"
#include "SplitString.h"
#include<string>
#include<iostream>
#include<cstring>
#include<sstream>
#include<vector>

using namespace std;

Stock US_Split0(string s)
{
    stringstream sstream(s);
    string s1,s2;
    vector<double> f;

    getline(sstream,s1,',');
    getline(sstream,s2,',');
    string t;

    while(getline(sstream,t,','))
    {
        stringstream tt(t);//cout<<tt.str()<<" "<<f[i]<<endl;
        double tmp;
        tt>>tmp;
        f.push_back(tmp);
        t.clear();
    }
    Stock ret(s1,s2,f[0],f[1],f[2],f[3],f[5],s);
    return ret;
}

simstock US_Split1(string s)
{
    stringstream sstream(s);
    string s1,s2;
    vector<double> f;

    getline(sstream,s1,',');
    getline(sstream,s2,',');
    string t;

    while(getline(sstream,t,','))
    {
        stringstream tt(t);//cout<<tt.str()<<" "<<f[i]<<endl;
        double tmp;
        tt>>tmp;
        f.push_back(tmp);
        t.clear();
    }
    int len=f.size();
    if(len==8)
    {
        simstock ret(s,f[6],f[7],s1);
        return ret;
    }
    else
    {
        simstock ret(s,f[7],f[8],s1);
        return ret;
    }
}

Stock US_Split2(string s)
{
    stringstream sstream(s);
    string s1,s2;
    vector<double> f;

    getline(sstream,s1,',');
    getline(sstream,s2,',');
    string t;

    while(getline(sstream,t,','))
    {
        stringstream tt(t);//cout<<tt.str()<<" "<<f[i]<<endl;
        double tmp;
        tt>>tmp;
        f.push_back(tmp);
        t.clear();
    }
    int len=f.size();
    if(len==8)
    {
        Stock ret(s1,s2,f[0],f[1],f[2],f[3],f[5],s);
        return ret;
    }
    else
    {
        Stock ret(s1,s2,f[0],f[1],f[2],f[3],f[4],s);
        return ret;
    }
}

string yrmth(string s)
{
    stringstream sstream(s);
    string s1,s2;
    getline(sstream,s1,'-');
    getline(sstream,s2,'-');
    return s1+"-"+s2;
}

bool Splitsharpe(string s,string yr,string & sym,double & ext)
{
    stringstream sstream(s),ss;
    string t;
    getline(sstream,t,',');
    if(yr!=t) return 0;

    getline(sstream,sym,',');

    t.clear();
    getline(sstream,t);
    ss.clear();ss.str("");
    ss<<t;ss>>ext;
    return 1;
}
