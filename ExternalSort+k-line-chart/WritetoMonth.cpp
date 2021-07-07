#include "Readin.h"
#include "stock.h"
#include "func.h"
#include "global.h"
#include "SplitString.h"

#include<fstream>
#include<iostream>
#include<sstream>
#include<string>
#include<map>
#include<vector>
using namespace std;
map<string,int> P;

vector<string> WritetoMonth(string filename)
{
    ifstream fin(filename+TAIL);
    string s;
    vector<string> ret_list;
    getline(fin,s);

    while(readoneline(fin,s)==1)
    {
        string subname=yrmth(s);
        ofstream subin(subname+TAIL,ios::app);
        if(P.find(subname)==P.end())
        {
            P[subname]=1;
            ret_list.push_back(subname);
        }
        subin<<s<<endl;
        subin.close();
    }
    return ret_list;
}
