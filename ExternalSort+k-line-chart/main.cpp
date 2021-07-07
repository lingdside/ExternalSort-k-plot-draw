#include "qcustomplotwin.h"

#include <QApplication>

#include "Readin.h"
#include "global.h"
#include "func.h"
#include "stock.h"
#include "KwayMerge.h"
#include "WriteMaxk.h"
#include "PrintGragh.h"
#include "maxkinput.h"

#include<iostream>
#include<sstream>
#include<fstream>
#include<vector>
#include<string>
#include<QVector>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    string US_filename="input";
    Stock * tmp=new Stock;
    int run_size=50*(1<<20)/sizeof(*tmp);

    //读入文件，并将其输出至前缀"new_"+原文件名的新文件。同时完成外排序子文件的切割和内部排序。
    vector<string> filenamelist=US_calcrise(US_filename,run_size);
    cout<<"Rise extent has been calculated and the result was saved in \"new_input.csv\".\n";

    //外排序K路归并
    int K=10;
    int ans_num=Merge(filenamelist,K);
    cout<<"External sort has been done and the result was saved in \"subfile"<<ans_num<<"\".csv.\n";

    //过渡子文件使用完成后及时删除
    for(vector<string>::iterator i=filenamelist.begin();i!=filenamelist.end();i++)
        remove((*i+TAIL).c_str());
    for(int i=1;i<ans_num;i++)
    {
        stringstream ss;
        ss<<i;
        string t;
        ss>>t;
        remove(("subfile"+t+TAIL).c_str());
    }

    //计算夏普比率
    US_filename="new_"+US_filename;
    US_calcsharpe(US_filename);
    cout<<"Sharpe ratio has been calculated.\n";

    //按月份切割源数据，输出某年某月涨跌幅绝对值最大的k条记录.
    vector<string> mthfilelist=WritetoMonth(US_filename);

    cout<<"Please input the month you need to find the k records of highest rise-extent's absolute value:(such as 2020-06)"<<endl;
    string mthfilename;
    cin>>mthfilename;
    cout<<"Please input the number(k) of data you need:"<<endl;
    int datanum;
    cin>>datanum;
    WriteMaxk(mthfilename,datanum);

    //记录某年夏普比率最大的N只股票，并读取当年该股票的记录保存到Rec数组中.
    int N=10;
    QVector<Stock> Rec[N];
    string syr;
    cout<<"Please input the year you need to find the 10 stocks of highest sharpe ratio:(such as 2020)\n";
    cin>>syr;
    PrintGragh(syr,N,Rec);

    //绘制K线图，保存到以股票名称命名的png中
    for(int k=0;k<N;k++)
    {
        QVector<Stock> & NOW=Rec[k];
        QCustomPlotWin w(NOW);
        QPixmap p=w.grab();
        QImage im=p.toImage();
        im.save((NOW[0].Symb+".png").c_str());
        cout<<NOW[0].Symb<<"'s candlestick chart has been printed.\n";
    }

    //删除以月份命名的数据文件
    for(vector<string>::iterator i=mthfilelist.begin();i!=mthfilelist.end();i++)
        remove((*i+TAIL).c_str());
    return 0;
}
