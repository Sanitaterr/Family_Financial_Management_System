#include "Person.h"

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

void LinkList::create(int n,vector<FileTemp>vf) //����������Ϊn������
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

void LinkList::print(string name) const noexcept //��ӡָ���û�������
{
	if (!search(name)) {
		cout << "The user does not exist" << endl;
		return;
	}
	Node* cur = head->next;
	while (cur) {
		if (cur->name == name)break;
		cur = cur->next;
	}
	if (cur == nullptr)return;
	cout << cur->name <<" :" << endl;
	cur->account.showall();
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

void LinkList::insertBeforeIndex(int index,string name) noexcept//��index֮ǰ��������Ϊdata�Ľ��
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

void LinkList::insertBeheadIndex(int index,string name) noexcept//��index֮���������Ϊdata�Ľ��
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






vector<string> LinkList::file_out_name()
{
	Node* cur = head->next;
	vector<string> vs;
	while (cur){
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