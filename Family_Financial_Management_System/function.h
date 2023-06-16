#pragma once

constexpr auto filename = "Person.txt";

#include "Person.h"
#include "FileTemp.h"
#include <fstream>
using namespace std;

void show();
void get_help();
void file_operate_in(LinkList& linkList);
void file_operate_out(LinkList& linkList);
void _FAMILY_FINANCIAL_MANAGEMENT_SYSTEM_(LinkList& linkList);

void show()
{
	cout << "Welcome to Family financial management system" << endl << endl;
	cout << " * Starting ..." << endl;
	cout << " * Ready" << endl << endl;
}

void get_help()
{
	cout << "Use `" << "\033[34m" << "cat" << "\033[0m" << "' to displays information about all users." << endl;
	cout << "Use `" << "\033[34m" << "cat user" << "\033[0m" << "' to displays information about the specified user." << endl;
	cout << "Use `" << "\033[34m" << "add user" << "\033[0m" << "' to displays information about all users." << endl;
	cout << "Use `" << "\033[34m" << "delete" << "\033[0m" << "' to delete user information." << endl;
	cout << "Use `" << "\033[34m" << "add account" << "\033[0m" << "' to add the specified user account information." << endl;
	cout << "Use `" << "\033[34m" << "delete account" << "\033[0m" << "' to delete the specified user account information." << endl;
	cout << "Use `" << "\033[34m" << "clear" << "\033[0m" << "' to clear all data." << endl;
	cout << "Use `" << "\033[34m" << "sort" << "\033[0m" << "' to sort all the data." << endl;
}

void file_operate_in(LinkList& linkList)
{
	vector< FileTemp>vf;

	fstream fin;
	fin.open(filename, ios::in);

	if (fin.is_open() == false) {
		cout << "Failed to open file "<<filename << endl;
		return;
	}
	string buffer;

	int index = 0;
	string name;
	vector<string>time;
	vector<string>usefor;
	vector<double>money;

	string name_temp;

	int cishu = 0;
	vector<So>fs;

	while (getline(fin, buffer)) {
		string temp = buffer.substr(0, 5);
		if (temp == "name:") {
			if (cishu) {
				
				for (int i = 0; i < time.size(); i++) {
					fs.push_back({ time[i],usefor[i],money[i] });
				}
				vf.push_back({ name_temp,fs });
				fs.clear();
				time.clear();
				usefor.clear();
				money.clear();
			}

			name_temp = buffer.substr(5, buffer.length() - 5);
			string name = buffer.substr(5, buffer.length() - 5);

			index++; cishu++;
		}
		else {
			int num = 0;
			int l = 0;
			string strmid;
			for (int i = 0; i < buffer.size(); i++) {
				if (buffer[i] == ' ') {
					strmid.assign(buffer, l, i - l);
					l = i + 1;

					switch (num)
					{
					case 0: {
						time.push_back(strmid);
						break;
					}
					case 1: {
						usefor.push_back(strmid);
						break;
					}
						  /*default:
							  break;*/
					}

					num++;
				}

			}
			strmid.assign(buffer, l, buffer.size());
			money.push_back(stoi(strmid));
		}
	}
	for (int i = 0; i < time.size(); i++) {
		fs.push_back({ time[i],usefor[i],money[i] });
	}
	vf.push_back({ name_temp,fs });


	linkList.create(vf.size(), vf);
}

void file_operate_out(LinkList& linkList)
{
	fstream fout;
	fout.open(filename, ios::out | ios::trunc);

	if (fout.is_open() == false) {
		cout << "Failed to open file " << filename << endl;
		//return;
	}

	vector<string> vs_name = linkList.file_out_name();
	for (auto it : vs_name) {
		string name = it;
		fout << "name:" << name << endl;
		//cout << "name:" << name << endl;
		int len = linkList.getLength_of_user(name);
		for (int i = 0; i < len; i++) {
			string time = linkList.file_out_account_time(name, i);
			string usefor = linkList.file_out_account_usefor(name, i);
			double money = linkList.file_out_account_money(name, i);
			//cout << time << " " << usefor << " " << money << endl;
			fout << time << " " << usefor << " " << money << endl;
		}
	}
	fout.close();

}

void _FAMILY_FINANCIAL_MANAGEMENT_SYSTEM_(LinkList &linkList)
{
	bool flag = 0;
	bool prime = 0;
	while (true) {
		cout << "\033[32m" << "lenovoy:~# " << "\033[m";

		string order;
		getline(cin, order);
		if (order.size() == 0)continue;

		if (order == "help") {
			get_help();
		}
		else if (order == "cat") {
			linkList.print();
			linkList.getLength();
		}
		else if (order == "cat user") {
			cout << "Please enter the name of the user you want to query:";
			string name;
			getline(cin, name);
			linkList.print(name);
		}
		else if (order == "add user") {
			cout << "Please enter the name of the user you want to add:";
			string name;
			getline(cin, name);
			linkList.addtoHead(name);
			flag = 0;
			prime = 0;
		}
		/*else if (choose == 3) {
			cout << "请输入需要插入结点前的位置索引和名字：";
			int pos; string name;
			cin >> pos; op = getchar(); getline(cin, name);
			linkList.insertBeforeIndex(pos,name);
		}
		else if (choose == 4) {
			cout << "请输入需要插入结点后的位置索引和名字：";
			int pos; string name;
			cin >> pos; op = getchar(); getline(cin, name);
			linkList.insertBeheadIndex(pos,name);
		}*/
		else if (order == "delete") {
			cout << "Please enter the name of the user you want to delete:";
			string name;
			getline(cin, name);
			linkList.deleteByIndex(name);
			flag = 0;
			prime = 0;
		}
		/*else if (choose == 6) {
			continue;
			cout << "请输入需要查询的索引位置：";
			int index;
			cin >> index;
			linklist.search(index);
		}*/
		else if (order == "add account") {
			cout << "Please enter the name of the user whose account information you want to add:";
			string name;
			getline(cin, name);
			linkList.add_account(name);
			flag = 0;
		}
		else if (order == "delete account") {
			cout << "Please enter the name of the user whose account information you want to delete:";
			string name;
			getline(cin, name);
			linkList.delete_account(name);
			flag = 0;
			prime = 0;
		}
		else if (order == "exit") {
			cout << "Bye" << endl;
			break;
		}
		else if (order == "git status") {
			if (prime) {
				cout << "nothing added to commit" << endl;
			}
			else if (!flag) {
				cout << "Untracked files:" << endl;
				cout << "  (use 'git add' to include in what will be committed)" << endl;
				cout << "\033[31m" << "        " << filename << "\033[0m" << endl;
				cout << endl;
				cout << "nothing added to commit but untracked files present (use 'git add' to track)" << endl;
			}
			else {
				cout << "Changes to be committed:" << endl;
				cout << "\033[32m" << "        " << filename << "\033[0m" << endl;
				cout << endl;
				cout << "Untracked files:" << endl;
				cout << "  (use 'git add' to include in what will be committed)" << endl;
				cout << endl;
			}
		}
		else if (order == "git add") {
			flag = 1;
		}
		else if (order == "git commit") {
			file_operate_out(linkList);
			flag = 0;
			prime = 1;
		}
		else if (order == "clear") {
			linkList.clear_inf();
			cout << "has all cleared" << endl;
		}
		else if (order == "sort") {
			linkList.LinkList_sort();
		}
		else {
			cout << order << ": command not found" << endl;
			cout << "Try 'help' for more information." << endl;
		}
	}
	return;
}