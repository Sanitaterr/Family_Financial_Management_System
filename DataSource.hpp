//
// Created by tongj on 2023/6/18.
//

#ifndef HOME_MONEY_DATASOURCE_HPP
#define HOME_MONEY_DATASOURCE_HPP

#include "baseData.hpp"


void newAccount(const char* name,int age);

/**
 * 根据名称获取账户
 * @param name 名字
 * @param des 查到时存的地方
 * @return true 查到,false 不存在
 */
bool getAccount(const char *name,Account* des);


void deleteAccout(const char* name);

/**
 * 根据年龄范围查询
 * @param min 最小年龄
 * @param max 最大年龄
 * @param res 存的地方
 * @param size 存的地方最大的尺寸
 * @return 查到的数量
 */
int findByAge(int min,int max,Account* res,int size);


#endif //HOME_MONEY_DATASOURCE_HPP
