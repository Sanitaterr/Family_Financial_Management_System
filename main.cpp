#include <iostream>
#include "DataSource.hpp"
#include <string>
using namespace std;
Account temps[100];

void makeData()
{
    string names[]={"jack","tom","tony","gray","pip","nick"};
    int ages[]={18,25,33,24,90,24};
    for(int i=0;i<6;i++)
    {
        newAccount(names[i].c_str(),ages[i]);
    }
}

void write(Account account)
{
    cout<<"account:"<<account.name<<",age:"<<account.age<<endl;
}


void findByName()
{
    cout<<"输入你要查询的名称"<<endl;
    string  name;
    cin>>name;
    Account temp;
    getAccount(name.c_str(),&temp);
    write(temp);
}
void findByAge()
{
    int min,max;
    cout<<"输入最小最大年龄"<<endl;
    cin>>min>>max;

    int cnt= findByAge(min,max,temps,10);
    for(int i=0;i<cnt;i++)
    {
        write(temps[i]);
    }

}
int main() {
    makeData();
    findByAge();
    return 0;
}
