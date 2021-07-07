#include "stock.h"
#include "func.h"
#include "global.h"
#include "SplitString.h"
#include "PrintGragh.h"
#include "qcustomplotwin.h"

#include<string>
#include<iostream>
#include<fstream>
#include<sstream>
#include<queue>
#include<QVector>
using namespace std;
typedef pair<double,string> pds;
const string mth[12]={"01","02","03","04","05","06","07","08","09","10","11","12"};

void PrintGragh(string syr,int & N,QVector<Stock> Rec[])
{
    ifstream fin("sharpe_ratio"+TAIL);
    priority_queue<pds> pq;

    string t;
    getline(fin,t);
    while(readoneline(fin,t))
    {
        string sym;
        double shar;
        if(!Splitsharpe(t,syr,sym,shar))continue;
        pq.push(make_pair(shar,sym));//把当年的股票代码和夏普比率存入优先队列，优先队列前10条就是夏普比率最大的10条股票
    }
    fin.close();
    if(pq.size()<N)
    {
        cout<<"There are less than 10 stocks' record in this year.\n";
        N=pq.size();
    }
    cout<<N<<" stock symbols have been prepared.\n";

    for(int k=0;k<N;k++)
    {
        string sym=pq.top().second;
        pq.pop();
        for(int i=0;i<12;i++)
        {
            string filename=syr+"-"+mth[i],s;
            ifstream finmth(filename+TAIL);
            while(readoneline(finmth,s))
            {
                Stock NOW=US_Split2(s);
                if(NOW.Symb==sym)Rec[k].append(NOW);
            }
            finmth.close();
        }
    }
}
