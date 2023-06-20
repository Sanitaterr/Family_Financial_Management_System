//
// Created by abstergo on 2023/6/20.
//

#ifndef HOME_MONEY_COMMANDIMPL_H
#define HOME_MONEY_COMMANDIMPL_H


#include "Cmd.h"

class FindAccountCommand:public IOnCommand
{
public:
    CommandEnum onCommand(const Param *params, const int &size) override;

    void commandName(char *des, const int &size) override;

    void help(char *des, const int &size) override;

    bool isAcceptParam(const char *cmd) override;
};


#endif //HOME_MONEY_COMMANDIMPL_H