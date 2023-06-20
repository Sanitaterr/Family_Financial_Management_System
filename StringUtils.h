//
// Created by abstergo on 2023/6/20.
//

#ifndef HOME_MONEY_STRINGUTILS_H
#define HOME_MONEY_STRINGUTILS_H

#include <vector>


namespace StringUtils {
    typedef std::vector<std::string> strArray;

    /**
     * 分割字符串
     * @param text
     * @param spl
     * @param des
     */
    void splitString(const char *text, const char *spl, strArray &des);

    /**
     * 正则表达式匹配字符串
     * @param text
     * @param pattern
     * @param des
     */
    void regex(const char *text, const char *pattern, strArray &des);

    /**
     * 判断是否相同
     * @return
     */
    bool equal(const char *, const char *);

    /**
     * 字符串text的开头是否等于pre
     * @param text
     * @param pre
     * @return
     */
    bool startWith(const char *text, const char *pre);
}
#endif //HOME_MONEY_STRINGUTILS_H
