#include "KwayMerge.h"
#include "SplitString.h"
#include "func.h"
#include "stock.h"
#include "Readin.h"
#include "global.h"

#include<fstream>
#include<sstream>
#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<cstring>

using namespace std;
typedef pair<simstock,int> p;

struct pqcmp
{
    bool operator()(p A,p B)
    {
        return !(A.first>B.first);
    }
};

//KwayMerge函数实现K个文件的K路合并,输出的文件名为ans_namelist.csv
void KwayMerge(vector<string> Kwaylist,string ans_namelist,int K)
{
    ofstream fout(ans_namelist+TAIL);

    ifstream fin[K];
    for(int i=0;i<K;i++) fin[i].open(Kwaylist[i]+TAIL);
    priority_queue< p,vector<p>,pqcmp > Q;
    while(!Q.empty()) Q.pop();
    for(int i=0;i<K;i++)
    {
        string s;
        if(!readoneline(fin[i],s)) continue;
        simstock NOW=US_Split1(s);
        Q.push(make_pair(NOW,i));
    }
    do {
        p Min=Q.top();
        Q.pop();
        fout<<(Min.first.s)<<endl;
        string s;
        if(!readoneline(fin[Min.second],s)) continue;
        Q.push(make_pair(US_Split1(s),Min.second));
    } while(!Q.empty());
    cout<<"A merge has been done.\n";

}

//Merge函数负责分配文件，每组K个，最后一组可能小于K个。返回值为最终答案的文件序号.
int Merge(vector<string> filenamelist,int K)
{
    priority_queue<Stock,vector<Stock>,pqcmp> Q;
    vector<string> Kwaylist;
    int part_cnt=1;
    if(filenamelist.size()==1)
    {
        KwayMerge(filenamelist,"subfile1",1);
        return 1;
    }
    while(filenamelist.size()>1)
    {
        vector<string> temp;
        int j=0;
        for(vector<string>::iterator i=filenamelist.begin();i!=filenamelist.end();i++)
        {
            Kwaylist.push_back(*i);
            j++;
            if(j==K)
            {
                stringstream sstream;
                sstream<<part_cnt;
                string t; sstream>>t;
                string part_filename="subfile"+t;
                temp.push_back(part_filename);
                KwayMerge(Kwaylist,part_filename,K);
                Kwaylist.clear();
                j=0;
                part_cnt++;
            }
        }
        if(j)
        {
            stringstream ss;
            ss<<part_cnt;
            string t; ss>>t;
            string part_filename="subfile"+t;
            temp.push_back(part_filename);
            KwayMerge(Kwaylist,part_filename,j);
            part_cnt++;
        }
        Kwaylist.clear();

        filenamelist.clear();
        filenamelist=temp;
    }
    return part_cnt-1;
}
