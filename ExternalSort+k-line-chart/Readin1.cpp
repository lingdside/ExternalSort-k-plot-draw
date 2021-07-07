#include "Readin.h"
#include "stock.h"
#include "SplitString.h"
#include "func.h"
#include "global.h"

#include<string>
#include<vector>
#include<fstream>
#include<iostream>
#include<sstream>
#include<algorithm>
using namespace std;

bool savecmp(simstock A,simstock B)
{
    return A>B;
}

string WriteToSub(int& part_sum,int& part_cnt,string filename,simstock Forsave[])
{//cout<<"cnt"<<part_cnt<<" ";
    stringstream tt;tt.clear();tt.str("");
    tt<<part_cnt;
    string t;t.clear();
    tt>>t;
    string part_filename=filename+t;
    ofstream partfout(part_filename+TAIL);//cout<<part_cnt<<" "<<part_sum<<endl;
    sort(Forsave,Forsave+part_sum,savecmp);//cout<<part_cnt<<" "<<part_sum<<endl;
    for(int i=0;i<part_sum;i++)
        partfout<<Forsave[i].s<<','<<Forsave[i].a<<','<<Forsave[i].b<<endl;
    partfout.close();
    part_cnt++;
    part_sum=0;
    cout<<"An ordinary sub_input named \""<<part_filename<<"\" has been printed.\n";
    return part_filename;
}

vector<string> US_calcrise(string US_filename,int run_size)
{
    ifstream fin(US_filename+TAIL);

    string newname="new_"+US_filename;
    ofstream fout(newname+TAIL);

    //输出多个有序子文件的准备
    int part_cnt=1;
    int part_sum=0;//part_cnt表示当前输出的子文件的序号，part_sum表示当前记录是子文件中的第part_sum条。part_sum=k时，part_sum=0,输出到下一个新的子文件。
//    string partUS_filename;
    vector<string> ret_filelist;
    ret_filelist.clear();
    simstock *Forsave=new simstock[run_size+10];

    string s;
    getline(fin,s);
    Stock LAST;
    while(readoneline(fin,s)==1)
    {
        Forsave[part_sum].s.clear();
        Forsave[part_sum].s=s;
        Stock NOW=US_Split0(s);
        Forsave[part_sum].t=NOW.Dat;
        fout<<s;
        if(issamest(LAST,NOW))//如果当前数据和上一条数据是同一个股票
        {
            Forsave[part_sum].a=calc_riseamount(LAST,NOW);//计算涨跌额
            Forsave[part_sum].b=calc_riseextent(LAST,NOW);//计算涨跌幅
        }
        else Forsave[part_sum].a=Forsave[part_sum].b=0;
        fout<<","<<Forsave[part_sum].a;
        fout<<","<<Forsave[part_sum].b;
        fout<<endl;
        LAST=NOW;
            //if(part_cnt==35)cout<<part_sum<<" ";
        part_sum++;
        if(part_sum>=run_size)//当前子文件已满k条，关闭当前子文件，打开下一个子文件
            ret_filelist.push_back(WriteToSub(part_sum,part_cnt,US_filename,Forsave));
        s.clear();
    }
    fin.close();
    fout.close();
    if(part_sum>0)
        ret_filelist.push_back(WriteToSub(part_sum,part_cnt,US_filename,Forsave));
    return ret_filelist;
}
