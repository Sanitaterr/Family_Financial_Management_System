#pragma once

#include "FileTemp.h"
#include "AccountList.h"

using namespace std;

class LinkList {
private:
    class Node {
    public:
        string name;//家庭成员姓名
        AccountList account;//账户
        Node* next;
    };
	Node* head;
    int length = 0;
public:
    LinkList()
    {
        head = new Node;
        head->next = nullptr;
    }

    class IDeal
    {
    public:
        virtual int deal(const AccountList& l,const string& name, int index) = 0;
    };


    static const int STATUS_RUN = 1,STATUS_STOP=0,STATUS_DELETE=-1;

    virtual ~LinkList() {}
    int foreach(IDeal&);
    int foreachc(IDeal&) const;
    vector<string> file_out_name();
    string file_out_account_time(string name,int index);
    string file_out_account_usefor(string name, int index);
    double file_out_account_money(string name, int index);

    void create(int n,vector<FileTemp>vf);//初始化n个结点的单链表
    void clear_inf();

    void print() const noexcept;//打印所有用户的数据
    void print(string name) const noexcept;//打印指定用户的数据

    int getLength() const noexcept;//获取单链表的长度
    int getLength_of_user(string name)const noexcept;//获取用户信息长度

    void isEmpty() const noexcept;//判断单链表是否为空

    //int search(int index) const noexcept;//查找索引为index的数据并返回
    bool search(string name) const noexcept;//查找为name的数据

    //int find(int elem) const noexcept;//查找数据为elem的索引并返回

    void insertBeforeIndex(int index,string name) noexcept;//在索引为index之前的位置插入数据为data的结点
    void insertBeheadIndex(int index,string name) noexcept;//在索引为index之后的位置插入数据为data的结点
    void addtoHead(string name) noexcept;//头插

    //更改账户信息
    void add_account(string name)noexcept;
    void delete_account(string name)noexcept;

    void deleteByIndex(int index) noexcept;//删除索引为index的结点
    void deleteByIndex(string name) noexcept;//删除名字为name的结点

    void LinkList_sort()noexcept;//简单的一个排序
};