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

    void showall()const noexcept;//չʾ�����˻�

    void addinfo();//����˻�
    void addinfo(string time, string usefor, double money);//����˻�

    void deleteinfo();//ɾ���˻�

    int find_time(string time)const noexcept;//Ѱ��time���±�

    int num_of_info()const noexcept;//���ش�С

    string file_get_time(int index)const noexcept;
    string file_get_usefor(int index)const noexcept;
    double file_get_money(int index)const noexcept;
    double file_get_sum()const noexcept;
};

