//
// Created by abstergo on 2023/6/20.
//

#include "StringUtils.h"
#include <regex>

using namespace std;
namespace StringUtils {


    void splitString(const char *text, const char *spl, strArray &des) {
        string reg = "[" + string(spl) + "]+";
        regex(text, reg.c_str(), des);
    }
    bool startWith(const char* text,const char* pre) {
        string str(text),prefix(pre);
        if (str.length() < prefix.length()) {
            return false;
        }
        return str.substr(0, prefix.length()) == prefix;
    }

    bool equal(const char *l, const char *r) {
        return strcmp(l, r) == 0;
    }

    void regex(const char *text, const char *pattern, strArray &des) {
        std::regex regex(pattern);
        string str(text);
        std::sregex_token_iterator it(str.begin(), str.end(), regex, -1);
        std::sregex_token_iterator end;
        while (it != end) {
            des.push_back(it->str());
            ++it;
        }
    }
}