#include "Account.h"

string Account::get_time() const noexcept { return time; }

string Account::get_usefor() const noexcept { return usefor; }

double Account::get_money() const noexcept { return money; }

Account::Account(string time, string usefor, double money)noexcept
{
	this->time = time;
	this->usefor = usefor;
	this->money = money;
}

void Account::init(string time, string usefor, double money)noexcept
{
	this->time = time;
	this->usefor = usefor;
	this->money = money;
}