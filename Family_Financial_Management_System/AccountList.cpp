#include "AccountList.h"

#include <iostream>
using namespace std;
void AccountList::showall()const noexcept
{
	if (!num_of_info()) {
		cout << "   No user account information is available" << endl;
		return;
	}

	cout << "   Total amount spent: " << sum << endl;
	cout << endl;

	int index = 0;
	for (auto it : list) {
		cout << "   Time£º" << it.get_time() << endl;
		cout << "   Use for£º" << it.get_usefor() << endl;
		cout << "   Money£º" << it.get_money() << endl;
		index++;
		if (index < num_of_info())cout << endl;
	}
}

int AccountList::num_of_info()const noexcept
{
	return list.size();
}

void AccountList::addinfo()
{
	string time;
	string usefor;
	double money;
	cout << "Please enter the time:";
	getline(cin, time); 
	cout << "Please enter purpose:";
	getline(cin, usefor); 
	cout << "Please enter the amount:";
	char op; 
	cin >> money; op = getchar();
	Account account(time, usefor, money);
	list.push_back(account);
	sum += money;
	cout << "Adding information succeeded" << endl;
}
void AccountList::addinfo(string time, string usefor, double money)
{
	Account account(time, usefor, money);
	list.push_back(account);
	sum += money;
}

void AccountList::deleteinfo()
{
	cout << "Please enter the billing time:";
	string time; getline(cin, time);
	int index = find_time(time);
	sum -= list[index].get_money();
	list.erase(list.begin() + index);
	cout << "Succeeded in deleting information" << endl;
}

int AccountList::find_time(string time)const noexcept
{
	int index = -1;
	int now = 0;
	for (auto it : list ) {
		if (it.get_time() == time)index = now;
		now++;
	}
	return index;
}

string AccountList::file_get_time(int index)const noexcept
{
	return list[index].get_time();
}
string AccountList::file_get_usefor(int index)const noexcept
{
	return list[index].get_usefor();
}
double AccountList::file_get_money(int index)const noexcept
{
	return list[index].get_money();
}
double AccountList::file_get_sum()const noexcept
{
	return sum;
}