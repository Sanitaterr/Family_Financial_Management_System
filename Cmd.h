//
// Created by abstergo on 2023/6/20.
//

#ifndef HOME_MONEY_CMD_H
#define HOME_MONEY_CMD_H


enum CommandEnum {
    ERROR, OK, EXSIST, NOT_FOUND,UN_SUPPORT_PARAM
};

struct Param {
    char key[50];
    char value[500];
    bool enable=false;
};


class IOnCommand {
public:
    virtual CommandEnum onCommand(const Param *params, const int &size) = 0;

    virtual void commandName(char *des, const int &size) = 0;

    virtual void help(char *des, const int &size) = 0;

    virtual bool isAcceptParam(const char *cmd) = 0;
};

struct CommandSerachObject
{
    char* name;
    char* paramName;
};


CommandEnum importCommand(IOnCommand *cmd);

CommandEnum removeCommand(const char *name);

CommandEnum runCMD(const char *cmd);

CommandEnum help(const char *cmdName,char* des,int size);

int find(const CommandSerachObject& q,char* cmds[50],int size);

#endif //HOME_MONEY_CMD_H
