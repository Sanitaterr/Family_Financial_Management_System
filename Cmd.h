//
// Created by abstergo on 2023/6/20.
//

#ifndef HOME_MONEY_CMD_H
#define HOME_MONEY_CMD_H

/**
 * 命令运行结果枚举
 */
enum CommandEnum {
    //通用出错
    ERROR,
    //成功
    OK,
    //存在
    EXSIST,
    //不存在
    NOT_FOUND,
    //不支持的参数
    UN_SUPPORT_PARAM
};

/**
 * 参数结构体
 */
struct Param {
    /**
     * 参数名
     */
    char key[50]{};
    /**
     * 参数值
     */
    char value[500]{};
    /**
     * 是否有效
     */
    bool enable=false;
};

/**
 * 命令执行基类
 */
class IOnCommand {
public:
    /**
     * 执行命令
     * @param params 命令参数
     * @param size 命令参数的个数
     * @return 命令执行情况
     */
    virtual CommandEnum onCommand(const Param *params, const int &size) = 0;
    /**
     * 获取命令名称
     * @param des 目标指针
     * @param size 指针长度
     */

    virtual void commandName(char *des, const int &size) = 0;
    /**
     * 获取命令帮助文本
     * @param des
     * @param size
     */

    virtual void help(char *des, const int &size) = 0;
    /**
     * 是否接受的参数
     * @param cmd 参数名
     * @return
     */

    virtual bool isAcceptParam(const char *cmd) = 0;
};
/**
 * 命令查询数据，null不过滤，非null根据值和字段过滤
 */
struct CommandSerachObject
{
    char* name;
    char* paramName;
};

/**
 * 导入命令，cmd需要长期存在
 * @param cmd
 * @return
 */

CommandEnum importCommand(IOnCommand *cmd);

/**
 * 移除命令
 * @param name
 * @return
 */
CommandEnum removeCommand(const char *name);
/**
 * 执行命令
 * @param cmd
 * @return
 */
CommandEnum runCMD(const char *cmd);

/**
 * 获取命令帮助提示文本
 * @param cmdName 命令名
 * @param des
 * @param size
 * @return
 */
CommandEnum help(const char *cmdName,char* des,int size);

/**
 * 查找命令名，根据命令查询数据
 * @param q
 * @param cmds
 * @param size
 * @return
 */
int find(const CommandSerachObject& q,char* cmds[50],int size);

#endif //HOME_MONEY_CMD_H
