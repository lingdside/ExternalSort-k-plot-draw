#include "stock.h"
#include "Readin.h"
#include "func.h"
#include "global.h"
#include "SplitString.h"

#include<fstream>
#include<sstream>
#include<iostream>

#include<string>
#include<vector>
#include<cmath>
using namespace std;

float calc(vector<float> list)
{
    float sum=0;
    for(vector<float>::iterator i=list.begin();i!=list.end();i++)
        sum+=*i;
    float ave=sum/(list.size()),ans=0;
    for(vector<float>::iterator i=list.begin();i!=list.end();i++)
        ans+=(*i-ave)*(*i-ave);
    if(ans==0) return 0;
    return sqrt(ans/list.size());
}

void US_calcsharpe(string filename)
{
    ifstream fin(filename+TAIL);
    ofstream fout("sharpe_ratio"+TAIL);
    fout<<"Symbol,year,sharpe rate\n";

    string s;
    Stock LAST;
    vector<float> riextentlist;
    bool b=0;
    while(readoneline(fin,s)==1)
    {
        Stock NOW=US_Split2(s);
        if(issamest(LAST,NOW))//如果当前数据和上一条数据是同一个股票
        {
            if(issameyr(LAST,NOW))//如果当前数据和上一条数据属同一年
            {
                riextentlist.push_back(NOW.riextent);
            }
            else {
                fout<<LAST.Dat.year()<<","<<LAST.Symb<<','<<calc(riextentlist)<<endl;
                riextentlist.clear();
            }
        }
        else if(b){
            fout<<LAST.Dat.year()<<","<<LAST.Symb<<','<<calc(riextentlist)<<endl;
            riextentlist.clear();
        }

        LAST=NOW;
        b=1;
    }
    fout<<LAST.Dat.year()<<","<<LAST.Symb<<','<<calc(riextentlist)<<endl;
    fin.close();
    fout.close();
}
