//
// Created by abstergo on 2023/6/20.
//

#include "CommandImpl.h"
#include "StringUtils.h"
#include "DataSource.hpp"
#include <iostream>

const char *FIND_ACCOUNT_CMD = "find";
const char *FIND_ACCOUNT_HELP = "find -name {名字}";
const char *FINDACCOUNT_PARAMS[] = {"-name"};

Account temp;

void write(Account account) {
    std::cout << "account:" << account.name << ",age:" << account.age << std::endl;
}

CommandEnum FindAccountCommand::onCommand(const Param *params, const int &size) {
    using namespace StringUtils;
    for (int i = 0; i < size; i++) {
        if (equal(params[i].key, FINDACCOUNT_PARAMS[0])) {
            if (getAccount(params[i].value, &temp)) {
                write(temp);
                return OK;
            }
        }
    }
    return ERROR;
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
