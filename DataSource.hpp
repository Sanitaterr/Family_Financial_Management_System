//
// Created by tongj on 2023/6/18.
//

#ifndef HOME_MONEY_DATASOURCE_HPP
#define HOME_MONEY_DATASOURCE_HPP

#include "baseData.hpp"

void newAccount(const char* name,int age);

bool getAccount(const char *name,Account* des);

void deleteAccout(const char* name);

int findByAge(int min,int max,Account* res,int size);


#endif //HOME_MONEY_DATASOURCE_HPP
