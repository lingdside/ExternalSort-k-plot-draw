#ifndef STOCK_H
#define STOCK_H

#include "func.h"
#include<string>
#include "qcustomplot.h"

using namespace std;

//simstock是一个简化存储stock的类，由于本实验大部分操作仅围绕日期、涨跌幅、涨跌额展开，故在simstock中仅单独存放部分数据
class simstock
{
public:
    string s;//存放完整数据条
    double a,b;//分别存放涨跌额和涨跌幅
    QDate t;//存放日期
    bool operator > (simstock A) const;//重载>运算符
    simstock();
    simstock(string A,float x,float y,string B);
};

class Stock
{
public:
    Stock();
    Stock(string t,string s,double a,double b,double c,double d,double e,string re);
    friend double calc_riseamount(Stock a,Stock b);//计算涨跌额
    friend double calc_riseextent(Stock a,Stock b);//计算涨跌幅

    void show();
    double getHigh();
    double getLow();
    double getClose();
    double getOpen();
    double getVol();

    QDate Dat;
    double riextent;
    string Symb;
    string rec;
protected:
    double Open,High,Low,Close,riamount,Vol;
    //分别表示开盘价、最高价、最低价、收盘价、涨跌额
};
/*
class US_stock: public Stock
{
public:
    US_stock();
    US_stock(string t,string s,double a,double b,double c,double d);
    US_stock(string t,string s,double f[]);
    void update(double a,double b);
    void show();
};
*/
bool issamest(Stock a,Stock b);//判断两条记录的股票代码是否相同
bool issameyr(Stock a,Stock b);//判断两条记录的年份是否相同

#endif // STOCK_H
