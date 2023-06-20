//
// Created by abstergo on 2023/6/20.
//
#include "Cmd.h"
#include <map>
#include "StringUtils.h"
#include <string>
#include <stdexcept>


using namespace std;
using namespace StringUtils;
map<string, IOnCommand *> cmdMap;

const int tempSIZE = 500;
char tempText[tempSIZE];


struct CMD {
    string cmd;
    vector<Param> params;
};

static inline CMD read(const char *cmd) {
    CMD result;
    strArray arrs;
    splitString(cmd, " ", arrs);
    if (!arrs.empty()) {
        result.cmd = arrs[0];
        for (int i = 1; i < arrs.size(); i++) {
            if (startWith(arrs[i].c_str(), "-")) {
                Param param;
                strcpy(param.key, arrs[i].c_str());
                result.params.push_back(param);
            } else {
                unsigned long last = result.params.size() - 1;
                if (last < 0)
                    throw runtime_error("bad params");
                if (!result.params[last].enable) {
                    strcpy(result.params[last].value, arrs[i].c_str());
                    result.params[last].enable = true;
                } else {
                    throw runtime_error("bad param index");
                }
            }
        }
    } else {
        throw runtime_error("empty cmd");
    }
    return result;
}


CommandEnum test(const char *text) {
    if (cmdMap.count(text) > 0)
        return EXSIST;
    else
        return NOT_FOUND;
}

CommandEnum importCommand(IOnCommand *cmd) {
    cmd->commandName(tempText, tempSIZE);
    if (test(tempText) == EXSIST)
        return EXSIST;
    cmdMap[tempText] = cmd;
    return OK;
}

CommandEnum removeCommand(const char *name) {
    if (test(name) == EXSIST) {
        cmdMap.erase(name);
        return OK;
    }
    return NOT_FOUND;
}

CommandEnum runCMD(const char *cmd, bool onlyEnable) {
    CMD c = read(cmd);
    if (test(c.cmd.c_str()) == EXSIST) {
        IOnCommand &cmdimpl = *cmdMap[c.cmd];
        if (onlyEnable) {
            auto beg = c.params.begin();
            auto ed = c.params.end();
            while (beg < ed) {
                if (!(*beg).enable) {
                    c.params.erase(beg);
                }
                beg++;
            }
        }
        auto *params = new Param[c.params.size()];
        for (int i = 0; i < c.params.size(); i++) {
            if (cmdimpl.isAcceptParam(c.params[i].key))
                params[i] = c.params[i];
            else
                return UN_SUPPORT_PARAM;
        }
        CommandEnum result = cmdimpl.onCommand(params, c.params.size());
        delete[] params;
        return result;
    }
    return NOT_FOUND;
}

CommandEnum help(const char *cmdName, char *des, int size) {
    IOnCommand *cmd = cmdMap[cmdName];
    if (cmd != nullptr) {
        cmd->help(des, size);
        return OK;
    }
    return NOT_FOUND;
}

int find(const CommandSerachObject &q, char **cmds, int size) {
    int idx = 0;
    for (auto i: cmdMap) {
        int c = 0;
        if (q.name != nullptr) {
            if (i.first.compare(q.name) == 0) {
                c++;
            }
        } else {
            c++;
        }

        if (q.paramName != nullptr) {
            if (i.second->isAcceptParam(q.paramName)) {
                c++;
            }
        } else
            c++;

        if (c == 2) {
            i.second->commandName(cmds[idx++], 50);
        }
        if (idx >= size)
            break;
    }
    return idx;
}
