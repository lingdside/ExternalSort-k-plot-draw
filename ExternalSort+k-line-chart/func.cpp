#include "stock.h"
#include "func.h"

#include<string>
#include<algorithm>
#include<fstream>
using namespace std;


bool readoneline(ifstream & fin,string & s)
{
/*    char temp_line[64+1];

    string line1="";
    temp_line[0]='\0';
    fin.getline(temp_line, 64);

    line1=temp_line;*/
    string line1;
    getline(fin,line1);
 //   do
 //   {
        trim(line1);// all trim
        s=line1;

        bool status1=true;
        if(line1=="") status1=false;
        else return 1;
  //  }while(!getline(fin,line1));
    return 0;
}
