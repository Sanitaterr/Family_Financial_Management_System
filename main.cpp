#include <iostream>
#include "DataSource.hpp"
#include <string>
#include "StringUtils.h"

using namespace std;
Account temps[100];
#include "Cmd.h"
#include "CommandImpl.h"

FindAccountCommand findAccountCommand;
void init() {
    importCommand(&findAccountCommand);
    string names[] = {"jack", "tom", "tony", "gray", "pip", "nick"};
    int ages[] = {18, 25, 33, 24, 90, 24};
    for (int i = 0; i < 6; i++) {
        newAccount(names[i].c_str(), ages[i]);
    }
}



int main() {
    init();
    string cmd="find -name jack";
    char helptext[500];
    help("find",helptext,500);
    cout<<helptext;

    return 0;
}
