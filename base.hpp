//
// Created by tongj on 2023/6/18.
//

#ifndef HOME_MONEY_BASE_HPP
#define HOME_MONEY_BASE_HPP
//数据的基础容器


/**
 * 迭代器
 * @tparam _data
 */
template<class _data>
class Iter {
public:
    typedef Iter<_data> self;

    /**
     * 是否存在下一项
     * @return
     */
    virtual bool hasNext() const noexcept = 0;

    /**
     * 移动到下一项
     */

    virtual void next() noexcept = 0;

    /**
     * 当前指针的值
     * @return
     */
    virtual _data value() const noexcept = 0;

    /**
     * 更新当前迭代中数据的值
     * @param d
     */
    virtual void update(const _data d) noexcept = 0;

    /**
     * 移除当前迭代项
     */

    virtual void remove() noexcept = 0;

    /**
     * 在当前迭代项后新增一项
     * @param obj
     */

    virtual void insert(const _data &obj) noexcept = 0;

    virtual ~Iter()
    = default;
};

/**
 * 双向链表节点
 * @tparam _data
 */
template<class _data>
struct LinkNode {
    /**
     * 尾指针
     */
    LinkNode *next = nullptr;
    /**
     * 前指针
     */
    LinkNode *pre = nullptr;
    /**
     * 数据域
     */
    _data data;

    static void connect(LinkNode<_data> *before, LinkNode<_data> *after) {
        if (before != nullptr) {
            before->next = after;
        }

        if (after != nullptr)
            after->pre = before;
    }

    static void disconnect(LinkNode<_data> *before, LinkNode<_data> *after) {
        if (before != nullptr)
            before->next = nullptr;
        if (after != nullptr)
            after->pre = nullptr;
    }
};

/**
 * 抽象列表类
 * @tparam _data 数据域类型
 * @tparam _iter 迭代器类型
 */
template<class _data, class _iter>
class BaseList {
public:
    /**
     * 获取迭代器
     * @return
     */
    virtual _iter get() noexcept = 0;

    /**
     * 插入
     * @param d
     */
    virtual void insert(const _data d) noexcept = 0;

    /**
     * 计数总数
     * @return
     */
    virtual int count() noexcept = 0;
};


#endif //HOME_MONEY_BASE_HPP
