//
// Created by tongj on 2023/6/18.
//

#include "DataSource.hpp"

#include "base.hpp"
#include <string>
#include <cstring>


LinkList<Account> accountSource;
using namespace  std;

void newAccount(const char *name, int age) {
    Account account;
    account.age=age;
    strcpy(account.name,name);
    accountSource.insert(account);
}

bool getAccount(const char *name,Account* des) {
    auto  iter=accountSource.get();
    while (iter.hasNext())
    {
        iter.next();
        if(std::strcmp(name,iter.value().name)==0)
        {
            *des=iter.value();
            return true;
        }
    }

    return false;
}

void deleteAccout(const char *name) {
    auto  iter=accountSource.get();
    while (iter.hasNext())
    {
        iter.next();
        if(std::strcmp(name,iter.value().name)==0)
        {
            iter.remove();
            break;
        }
    }
}

int findByAge(int min, int max, Account *res, int size) {
    auto  iter=accountSource.get();
    int cnt=0;
    while (iter.hasNext()&&size>0)
    {
        iter.next();
        if(iter.value().age>=min&&iter.value().age<=max)
        {
            res[cnt]=iter.value();
            --size;
            ++cnt;
        }
    }
    return cnt;
}
