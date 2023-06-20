//
// Created by abstergo on 2023/6/20.
//

#ifndef HOME_MONEY_STRINGUTILS_H
#define HOME_MONEY_STRINGUTILS_H

#include <vector>


namespace StringUtils {
    typedef std::vector<std::string> strArray;

    void splitString(const char *text, const char *spl, strArray &des);

    void regex(const char *text, const char *pattern, strArray &des);

    bool equal(const char *, const char *);

    bool startWith(const char *text, const char *pre);
}
#endif //HOME_MONEY_STRINGUTILS_H
