#include "Person.h"
#include <algorithm>
using namespace std;

int LinkList::getLength() const noexcept
{
	cout << "The number of users is : " << length << endl;
	return length;
}

int LinkList::getLength_of_user(string name)const noexcept//��ȡ�û���Ϣ����
{
	Node* cur = head->next;
	while (cur) {
		if (cur->name == name) {
			return cur->account.num_of_info();
		}
		cur = cur->next;
	}
}

bool LinkList::search(string name) const noexcept //�Ƿ���name�û�
{
	Node* temp = head->next;
	while (temp) {
		if (temp->name == name)return true;
		temp = temp->next;
	}
	return false;
}

void LinkList::create(int n, vector<FileTemp>vf) //����������Ϊn������
{
	Node* pre = head;
	length = n;
	int i = 1;
	while (i <= n) {
		//cout << "�������" << i << "���������ݣ�";
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

void LinkList::print() const noexcept //��ӡ�����û��˻�
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

struct Data
{
	string name;
	AccountList list;
	double sum;
};

class SortDeal : public LinkList::IDeal
{
private:
	vector<Data> ls;
public:
	virtual int deal(const AccountList& l, const string& name, int index)
	{
		Data d;
		d.name = name;
		d.list = l;
		d.sum = 0;
		for (int i = 0; i < l.num_of_info(); i++)
		{
			d.sum += l.file_get_money(i);
		}
		ls.push_back(d);
		return LinkList::STATUS_RUN;
	}

	vector<Data> getResult()
	{
		sort(ls.begin(), ls.end(), [](const Data& l, const Data& r) {
			return l.sum > r.sum ;
			});
		return ls;
	}
};
void LinkList::LinkList_sort()noexcept //�򵥵�һ������
{
	SortDeal s;
	this->foreachc(s);
	for (Data& d : s.getResult())
	{
		d.list.showall();
	}
}


class SearchDeal :public LinkList::IDeal
{


private:
	int idx = -1;
	AccountList _data;
	string _name;
	int findStatus = LinkList::STATUS_STOP;
public:
	SearchDeal(const string& n) :_name(n)
	{

	}
	void reset(string n)
	{
		idx = -1;
		_name = n;
	}


	void setFIND_STATUS(int s)
	{
		this->findStatus = s;
	}

	const	AccountList* getResult()const noexcept
	{
		if (idx >= 0)
			return &_data;
		return nullptr;
	}

	virtual int deal(const AccountList& l, const string& name, int index)
	{
		if (_name.compare(name) == 0)
		{
			idx = index;
			_data = l;
			return findStatus;
		}
		return LinkList::STATUS_RUN;
	}
};

void LinkList::print(string name) const noexcept //��ӡָ���û�������
{

	SearchDeal s(name);

	this->foreachc(s);
	if (s.getResult() == nullptr) {
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
		cout << "����Ϊ��~" << endl;
		return;
	}
	cout << "lenovoy:~# ";
	cout << "����Ϊ��" << "��";
	this->getLength();
}

//int LinkList::search(int index) const noexcept//��Ϊ������1��ʼ
//{
//	if (index < 1 || index > length)
//		cout << "�����������" << endl;
//	else {
//		Node* temp = head->next;
//		int i = 1;
//		while (temp) {
//			if (i == index) {
//				cout << "����������Ϊ" << index << "������Ϊ" << temp->name << endl;
//				return temp->data;
//			}
//			else {
//				++i;
//				temp = temp->next;
//			}
//		}
//	}
//	return -1;//�ٶ������в����븺��
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
//	cout << elem << "���������У�" << endl;
//	return -1;
//}

void LinkList::insertBeforeIndex(int index, string name) noexcept//��index֮ǰ��������Ϊdata�Ľ��
{
	if (index < 1 || index > length) {
		cout << "����λ�ò��Ϸ�" << endl;
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
		cout << "����ɹ���" << endl;
	}
}

void LinkList::addtoHead(string name) noexcept//ͷ��
{
	Node* cur = head;
	Node* temp = new Node;
	temp->name = name;
	temp->next = cur->next;
	cur->next = temp;

	++length;
}

void LinkList::insertBeheadIndex(int index, string name) noexcept//��index֮���������Ϊdata�Ľ��
{
	if (index < 1 || index > length) {
		cout << "����λ�ò��Ϸ�" << endl;
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
		cout << "����ɹ���" << endl;
	}
}

void LinkList::add_account(string name)noexcept//���ָ���û��˻���Ϣ
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

void LinkList::delete_account(string name)noexcept//ɾ��ָ���û��˻���Ϣ
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

void LinkList::deleteByIndex(int index) noexcept //ɾ������Ϊindex�Ľ��
{
	if (index < 1 || index > length) {
		cout << "�����������" << endl;
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
		cout << "ɾ���ɹ�!" << endl;
	}
}

void LinkList::deleteByIndex(string name) noexcept //ɾ������Ϊname�Ľ��
{
	SearchDeal ser(name);
	ser.setFIND_STATUS(STATUS_DELETE);
	this->foreach(ser);

	if (ser.getResult() == nullptr) {
		cout << "The user does not exist" << endl;
		return;
	}
	cout << "Successfully delete" << endl;
	return;
}

int LinkList::foreach(IDeal& f)
{
	Node* cur = head->next;
	int i = 0;
	int status = STATUS_RUN;
	Node* last = head;
	while (cur && status == STATUS_RUN) {

		status = f.deal(cur->account, cur->name, i++);
		if (status == STATUS_DELETE)
		{
			auto dl = cur;
			last->next = dl->next;
			delete dl;
			cur = last->next;
			length--;
			continue;
		}
		last = cur;
		cur = cur->next;
	}
	return i;
}

int LinkList::foreachc(IDeal& f) const
{
	Node* cur = head->next;
	int i = 0;
	int status = STATUS_RUN;
	Node* last = head;
	while (cur && status == STATUS_RUN) {

		status = f.deal(cur->account, cur->name, i++);
		last = cur;
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