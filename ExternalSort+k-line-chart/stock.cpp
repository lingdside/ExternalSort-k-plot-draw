#include "stock.h"
#include "func.h"

#include<QString>
#include<string>
#include<iostream>
#include<sstream>
using namespace std;

Stock::Stock(){}
Stock::Stock(string t,string s,double a,double b,double c,double d,double e,string re):
    Symb(s),Open(a),High(b),Low(c),Close(d),Vol(e),rec(re)
{
    QString str=QString::fromStdString(t);
    Dat=QDate::fromString(str,"yyyy-MM-dd");
}

double Stock::getLow()
{
    return Low;
}
double Stock::getHigh()
{
    return High;
}
double Stock::getOpen()
{
    return Open;
}
double Stock::getClose()
{
    return Close;
}
double Stock::getVol()
{
    return Vol;
}

double calc_riseamount(Stock yest,Stock tod)//计算涨跌额
{
    return tod.Close-yest.Close;
}

double calc_riseextent(Stock yest,Stock tod)//计算涨跌幅
{

    return (tod.Close-yest.Close)/yest.Close;
}

bool issamest(Stock A,Stock B)//判断两条记录的股票代码是否相同
{
    return A.Symb==B.Symb;
}

bool issameyr(Stock A,Stock B)
{
    return A.Dat.year()==B.Dat.year();
}

simstock::simstock(){}
simstock::simstock(string A,float x,float y,string B)
{
    s=A;a=x;b=y;
    QString str=QString::fromStdString(B);
    t=QDate::fromString(str,"yyyy-MM-dd");
}

bool simstock::operator > (simstock A) const
{
    if(t>A.t) return 1;
    if(A.t>t) return 0;
    if(b>=A.b) return 1;
    return 0;
}
