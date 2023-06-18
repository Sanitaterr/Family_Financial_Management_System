//
// Created by tongj on 2023/6/18.
//

#ifndef HOME_MONEY_BASEDATA_HPP
#define HOME_MONEY_BASEDATA_HPP


/**
 * 账户类
 */
struct Account {
    char name[50];
    int age;
};
/**
 * 数据单项
 */
struct DetailItem
{
    /**
     * 账户的name
     */
    char belong[50];
    /**
     * 金额
     */
    double money;
    /**
     * 备注
     */
    char remark[500];
};




#endif //HOME_MONEY_BASEDATA_HPP
