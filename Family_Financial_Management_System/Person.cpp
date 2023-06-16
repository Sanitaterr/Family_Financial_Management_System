#include "Person.h"
#include <algorithm>
using namespace std;

int LinkList::getLength() const noexcept
{
	cout << "The number of users is : " << length << endl;
	return length;
}

int LinkList::getLength_of_user(string name)const noexcept//获取用户信息长度
{
	Node* cur = head->next;
	while (cur) {
		if (cur->name == name) {
			return cur->account.num_of_info();
		}
		cur = cur->next;
	}
}

bool LinkList::search(string name) const noexcept //是否有name用户
{
	Node* temp = head->next;
	while (temp) {
		if (temp->name == name)return true;
		temp = temp->next;
	}
	return false;
}

void LinkList::create(int n, vector<FileTemp>vf) //创建结点个数为n的链表
{
	Node* pre = head;
	length = n;
	int i = 1;
	while (i <= n) {
		//cout << "请输入第" << i << "个结点的数据：";
		Node* cur = new Node;
		cur->name = vf[i - 1].name;
		//cout << vf[i - 1].name << endl;
		for (int j = 0; j < vf[i - 1].so.size(); j++) {
			cur->account.addinfo(vf[i - 1].so[j].time, vf[i - 1].so[j].usefor, vf[i - 1].so[j].money);
			//cout << vf[i - 1].so[j].time << " " << vf[i - 1].so[j].usefor << " " << vf[i - 1].so[j].money << endl;
		}

		++i;
		pre->next = cur;
		pre = cur;
		cur->next = nullptr;
	}
}

bool cmp(FileTemp f1, FileTemp f2)
{
	return f1.sum < f2.sum;
}

void LinkList::LinkList_sort()noexcept //简单的一个排序
{
	vector<FileTemp> vf;
	int length_prime = length;
	Node* cur = head->next;
	int index = 0;
	while (cur) {
		double all = 0.0;

		vector<So>fs;
		for (int i = 0; i < cur->account.num_of_info(); i++) {
			fs.push_back({ cur->account.file_get_time(i), cur->account.file_get_usefor(i), cur->account.file_get_money(i) });
			all += cur->account.file_get_money(i);
		}
		vf.push_back({ cur->name, fs });
		vf[index].sum += all;
		index++;

		cur = cur->next;
	}
	vector<FileTemp> vf_prime = vf;
	sort(vf_prime.begin(), vf_prime.end(), cmp);
	clear_inf();
	length = length_prime;
	create(length, vf_prime);
}

void LinkList::clear_inf()
{
	Node* cur = head->next;
	while (cur) {
		Node* temp = cur;
		cur = temp->next;
		delete temp;
	}
	head = new Node;
	head->next = nullptr;
	length = 0;
}

void LinkList::print() const noexcept //打印所有用户账户
{
	Node* cur = head->next;
	if (length < 1) {
		cout << "No user information exists in the system" << endl;
		return;
	}
	cout << "All user information:" << endl;
	int index = 1;
	while (cur) {
		cout << index++ << "." << " ";
		cout << cur->name << endl;
		cur->account.showall();
		cout << endl;
		cur = cur->next;
	}
}

class SearchDeal :public LinkList::IDealC
{


private:
	int idx = -1;
	AccountList _data;
	string _name;
public:
	SearchDeal(const string& n) :_name(n)
	{

	}
	void reset(string n)
	{
		idx = -1;
		_name = n;
	}

	const	AccountList* getResult()const noexcept
	{
		if (idx >= 0)
			return &_data;
		return nullptr;
	}

	virtual int deal(const AccountList& l, const string& name, int index)
	{
		if (_name.compare(name)==0)
		{
			idx = index;
			_data = l;
			return 0;
		}
		return 1;
	}
};

void LinkList::print(string name) const noexcept //打印指定用户的数据
{

	SearchDeal s(name);

	this->foreach(s);
	if(s.getResult()==nullptr) {
		cout << "The user does not exist" << endl;
		return;
	}
	cout << name << " :" << endl;
	s.getResult()->showall();
	cout << endl;
}

void LinkList::isEmpty() const noexcept
{
	if (!length) {
		cout << "lenovoy:~# ";
		cout << "链表为空~" << endl;
		return;
	}
	cout << "lenovoy:~# ";
	cout << "链表不为空" << "，";
	this->getLength();
}

//int LinkList::search(int index) const noexcept//认为索引从1开始
//{
//	if (index < 1 || index > length)
//		cout << "索引输入错误！" << endl;
//	else {
//		Node* temp = head->next;
//		int i = 1;
//		while (temp) {
//			if (i == index) {
//				cout << "链表中索引为" << index << "的数据为" << temp->name << endl;
//				return temp->data;
//			}
//			else {
//				++i;
//				temp = temp->next;
//			}
//		}
//	}
//	return -1;//假定链表中不存入负数
//}



//int LinkList::find(int elem) const noexcept
//{
//	Node* cur = head->next;
//	int index = 1;
//	while (cur) {
//		if (cur->data == elem)
//			return index;
//		else {
//			cur = cur->next;
//			++index;
//		}
//	}
//	cout << elem << "不在链表中！" << endl;
//	return -1;
//}

void LinkList::insertBeforeIndex(int index, string name) noexcept//在index之前插入数据为data的结点
{
	if (index < 1 || index > length) {
		cout << "索引位置不合法" << endl;
	}
	else {
		Node* cur = head;
		int pos = 1;
		while (pos != index) {
			cur = cur->next;
			++pos;
		}
		Node* temp = new Node;
		temp->name = name;
		temp->next = cur->next;
		cur->next = temp;
		++length;
		cout << "插入成功！" << endl;
	}
}

void LinkList::addtoHead(string name) noexcept//头插
{
	Node* cur = head;
	Node* temp = new Node;
	temp->name = name;
	temp->next = cur->next;
	cur->next = temp;

	++length;
}

void LinkList::insertBeheadIndex(int index, string name) noexcept//在index之后插入数据为data的结点
{
	if (index < 1 || index > length) {
		cout << "索引位置不合法" << endl;
	}
	else {
		Node* cur = head->next;
		int pos = 1;
		while (pos != index) {
			cur = cur->next;
			++pos;
		}
		Node* temp = new Node;
		temp->name = name;
		temp->next = cur->next;
		cur->next = temp;
		++length;
		cout << "插入成功！" << endl;
	}
}

void LinkList::add_account(string name)noexcept//添加指定用户账户信息
{
	if (!search(name)) {
		cout << "The user does not exist" << endl;
		return;
	}

	Node* temp = head->next;
	while (temp) {
		if (temp->name == name) {
			temp->account.addinfo();
			return;
		}
		else temp = temp->next;
	}
	return;
}

void LinkList::delete_account(string name)noexcept//删除指定用户账户信息
{
	if (!search(name)) {
		cout << "The user does not exist" << endl;
		return;
	}

	Node* temp = head->next;
	while (temp) {
		if (temp->name == name) {
			temp->account.deleteinfo();
			return;
		}
		else temp = temp->next;
	}
}

void LinkList::deleteByIndex(int index) noexcept //删除索引为index的结点
{
	if (index < 1 || index > length) {
		cout << "索引输入错误！" << endl;
	}
	else {
		Node* cur = head;
		int pos = 1;
		while (pos != index) {
			cur = cur->next;
			++pos;
		}
		Node* temp = cur->next;
		cur->next = temp->next;
		delete temp;
		--length;
		cout << "删除成功!" << endl;
	}
}

void LinkList::deleteByIndex(string name) noexcept //删除名字为name的结点
{
	if (!search(name)) {
		cout << "The user does not exist" << endl;
		return;
	}

	Node* cur = head;
	while (cur->next) {
		if (cur->next->name == name) {
			Node* temp = cur->next;
			cur->next = temp->next;
			delete temp;
			--length;
			cout << "Successfully delete" << endl;
			return;
		}
		cur = cur->next;
	}
}

int LinkList::foreach(IDeal& f)
{
	Node* cur = head->next;
	int i = 0;
	while (cur) {
		f.deal(cur->account, cur->name, i++);
		cur = cur->next;
	}
	return i;
}

int LinkList::foreach(IDealC& f) const
{
	Node* cur = head->next;
	int i = 0;
	while (cur) {
		f.deal(cur->account, cur->name, i++);
		cur = cur->next;
	}
	return i;
}

vector<string> LinkList::file_out_name()
{
	Node* cur = head->next;
	vector<string> vs;
	while (cur) {
		vs.push_back(cur->name);
		cur = cur->next;
	}
	return vs;
}
string LinkList::file_out_account_time(string name, int index)
{
	Node* cur = head->next;
	while (cur) {
		if (cur->name == name) {
			return cur->account.file_get_time(index);
		}
		cur = cur->next;
	}
}
string LinkList::file_out_account_usefor(string name, int index)
{
	Node* cur = head->next;
	while (cur) {
		if (cur->name == name) {
			return cur->account.file_get_usefor(index);
		}
		cur = cur->next;
	}
}
double LinkList::file_out_account_money(string name, int index)
{
	Node* cur = head->next;
	while (cur) {
		if (cur->name == name) {
			return cur->account.file_get_money(index);
		}
		cur = cur->next;
	}
}