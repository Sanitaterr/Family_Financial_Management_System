#pragma once

#include "FileTemp.h"
#include "AccountList.h"

using namespace std;

class LinkList {
private:
    class Node {
    public:
        string name;//��ͥ��Ա����
        AccountList account;//�˻�
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

    void create(int n,vector<FileTemp>vf);//��ʼ��n�����ĵ�����
    void clear_inf();

    void print() const noexcept;//��ӡ�����û�������
    void print(string name) const noexcept;//��ӡָ���û�������

    int getLength() const noexcept;//��ȡ������ĳ���
    int getLength_of_user(string name)const noexcept;//��ȡ�û���Ϣ����

    void isEmpty() const noexcept;//�жϵ������Ƿ�Ϊ��

    //int search(int index) const noexcept;//��������Ϊindex�����ݲ�����
    bool search(string name) const noexcept;//����Ϊname������

    //int find(int elem) const noexcept;//��������Ϊelem������������

    void insertBeforeIndex(int index,string name) noexcept;//������Ϊindex֮ǰ��λ�ò�������Ϊdata�Ľ��
    void insertBeheadIndex(int index,string name) noexcept;//������Ϊindex֮���λ�ò�������Ϊdata�Ľ��
    void addtoHead(string name) noexcept;//ͷ��

    //�����˻���Ϣ
    void add_account(string name)noexcept;
    void delete_account(string name)noexcept;

    void deleteByIndex(int index) noexcept;//ɾ������Ϊindex�Ľ��
    void deleteByIndex(string name) noexcept;//ɾ������Ϊname�Ľ��

    void LinkList_sort()noexcept;//�򵥵�һ������
};