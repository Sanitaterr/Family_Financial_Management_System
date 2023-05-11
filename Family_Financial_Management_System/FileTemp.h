#pragma once
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

struct So {
	string time;
	string usefor;
	double money;
};

struct FileTemp
{
	string name;
	vector<So> so;
};

