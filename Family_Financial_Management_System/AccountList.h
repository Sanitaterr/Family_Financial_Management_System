#pragma once
#include "Account.h"
class AccountList :
    public Account
{
private:
    vector<Account> list;
    
    double sum;
public:
    AccountList() { this->sum = 0.0; }
    virtual ~AccountList(){}

    void showall()const noexcept;//展示所有账户

    void addinfo();//添加账户
    void addinfo(string time, string usefor, double money);//添加账户

    void deleteinfo();//删除账户

    int find_time(string time)const noexcept;//寻找time的下标

    int num_of_info()const noexcept;//返回大小

    string file_get_time(int index)const noexcept;
    string file_get_usefor(int index)const noexcept;
    double file_get_money(int index)const noexcept;
    double file_get_sum()const noexcept;
};

