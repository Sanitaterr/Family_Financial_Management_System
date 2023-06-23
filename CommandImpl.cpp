//
// Created by abstergo on 2023/6/20.
//

#include "CommandImpl.h"
#include "StringUtils.h"
#include "DataSource.hpp"
#include <iostream>
#include <memory>

#include <algorithm>

const char *FIND_ACCOUNT_CMD = "find";
const char *FIND_ACCOUNT_HELP = "find -name {名字}\n find -age {年龄下限},{年龄上限}\n -order 根据年龄排序";
const char *FINDACCOUNT_PARAMS[] = {"-name", "-age", "-order"};

const int FIND_FUNC_BYNAME = 0, FIND_FUNC_BYAGE = 1, FIND_FUNC_SORT = 2;

using namespace std;

Account temp[100];

void write(Account account) {
    std::cout << "account:" << account.name << ",age:" << account.age << std::endl;
}

class IInvoker {
public:
    virtual void invoke(const char *val, std::vector<Account> &res) = 0;

    virtual ~IInvoker() = default;
};

typedef unique_ptr<IInvoker> _invoker;

class FindByNameInvoker : public IInvoker {
public:
    void invoke(const char *val, std::vector<Account> &res) override {
        if (getAccount(val, temp)) {
            res.push_back(*temp);
        }
    }
};

class FindByAgeInvoker : public IInvoker {
public:
    void invoke(const char *val, std::vector<Account> &res) override {
        using namespace StringUtils;
        strArray arr;
        splitString(val, ",", arr);
        if (arr.size() == 2) {
            int m = atoi(arr[0].c_str());
            int mx = atoi(arr[1].c_str());
            int s = findByAge(m, mx, temp, 100);
            for (int i = 0; i < s; i++) {
                res.push_back(temp[i]);
            }
        }
    }
};

inline bool cmpAccountByAge(const Account &l, const Account &r) {
    return l.age > r.age;
}

class SortInvoker : public IInvoker {
public:
    void invoke(const char *val, vector<Account> &res) override {
        sort(res.begin(), res.end(), cmpAccountByAge);
    }
};

_invoker invokers[] = {_invoker(new FindByNameInvoker()), _invoker(new FindByAgeInvoker()),
                       _invoker(new SortInvoker())};


void invokeWithParam(std::vector<Account> &res, const char *key, IInvoker &invoker, const Param &param) {
    for (auto &i: FINDACCOUNT_PARAMS) {
        if (StringUtils::equal(param.key, key)) {
            invoker.invoke(param.value, res);
            break;
        }
    }
}


CommandEnum FindAccountCommand::onCommand(const Param *params, const int &size) {
    using namespace StringUtils;
    std::vector<Account> results;
    for (int i = 0; i < size; i++) {
        invokeWithParam(results, FINDACCOUNT_PARAMS[FIND_FUNC_BYNAME], *invokers[FIND_FUNC_BYNAME], params[i]);
        invokeWithParam(results, FINDACCOUNT_PARAMS[FIND_FUNC_BYAGE], *invokers[FIND_FUNC_BYAGE], params[i]);
        invokeWithParam(results, FINDACCOUNT_PARAMS[FIND_FUNC_SORT], *invokers[FIND_FUNC_SORT], params[i]);
    }
    for (auto i: results)
        write(i);
    return OK;
}

void FindAccountCommand::commandName(char *des, const int &size) {
    strcpy(des, FIND_ACCOUNT_CMD);
}

void FindAccountCommand::help(char *des, const int &size) {
    strcpy(des, FIND_ACCOUNT_HELP);
}

bool FindAccountCommand::isAcceptParam(const char *cmd) {
    for (auto &i: FINDACCOUNT_PARAMS)
        if (StringUtils::equal(cmd, i))
            return true;
    return false;
}


CommandEnum HelpCommand::onCommand(const Param *params, const int &size) {
    CommandSerachObject ser;
    char name[100][50];
    char *ptr[100];
    for (int i = 0; i < 100; i++)
        ptr[i] = name[i];
    int s = find(ser, ptr, 100);
    char text[1000];
    for (int i = 0; i < s; i++) {
        ::help(ptr[i], text, 1000);
        cout << "cmd:" << ptr[i] << " help:" << text << endl;
    }
    return OK;
}

void HelpCommand::commandName(char *des, const int &size) {
    ::strcpy(des, "help");
}

void HelpCommand::help(char *des, const int &size) {
    ::strcpy(des,"just for help");
}

bool HelpCommand::isAcceptParam(const char *cmd) {
    return false;
}
