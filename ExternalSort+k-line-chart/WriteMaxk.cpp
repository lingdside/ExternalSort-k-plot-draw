#include "Readin.h"
#include "stock.h"
#include "func.h"
#include "global.h"
#include "SplitString.h"

#include<fstream>
#include<iostream>
#include<sstream>
#include<string>
#include<vector>
#include<queue>
using namespace std;

struct simcmp
{
    bool operator()(simstock A,simstock B)
    {
        return (abs(A.b)>abs(B.b))?0:1;
    }
};

void WriteMaxk(string filename,int datanum)
{
    priority_queue<simstock,vector<simstock>,simcmp> Forsave;
    ifstream fin(filename+TAIL);
    string s;
    while(readoneline(fin,s)==1)
        Forsave.push(US_Split1(s));
    fin.close();
    remove((filename+TAIL).c_str());
    ofstream fout(filename+TAIL);
    ofstream ansout("Max_k_data_of "+filename+TAIL);
    while(!Forsave.empty())
    {
        fout<<Forsave.top().s<<endl;
        if(datanum>0) ansout<<Forsave.top().s<<endl;
        datanum--;
        Forsave.pop();
    }
    cout<<"The max k records has been output.\n";
}
