#pragma once

#include <bits/stdc++.h>

using namespace std;

class Account
{
private:
	string time;
	string usefor;
	double money;
public:
	Account() { money = 0.0; }
	Account(string time, string usefor, double money)noexcept;
	virtual ~Account(){}

	string get_time() const noexcept;
	string get_usefor() const noexcept;
	double get_money() const noexcept;
	void init(string time, string usefor, double money)noexcept;
};

