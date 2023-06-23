#include <iostream>
#include "DataSource.hpp"
#include <string>

using namespace std;

#include "Cmd.h"
#include "CommandImpl.h"

FindAccountCommand findAccountCommand;
HelpCommand helpCommand;

void init() {
    importCommand(&findAccountCommand);
    importCommand(&helpCommand);
    string names[] = {"jack", "tom", "tony", "gray", "pip", "nick"};
    int ages[] = {18, 25, 33, 24, 90, 24};
    for (int i = 0; i < 6; i++) {
        newAccount(names[i].c_str(), ages[i]);
    }
}


int main() {
    init();
    string cmd;
    getline(std::cin, cmd);
    cout << runCMD(cmd.c_str(), false);
    return 0;
}
