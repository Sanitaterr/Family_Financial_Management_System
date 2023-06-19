//
// Created by abstergo on 2023/6/19.
//

#ifndef HOME_MONEY_LISTIMPL_H
#define HOME_MONEY_LISTIMPL_H

#include "base.hpp"
#include "IterImpl.hpp"


/**
 * 链表类
 * @tparam _data
 */

template<class _data>
class LinkList : public BaseList<_data, LinkListIter<_data>> {
public:
    typedef LinkNode<_data> node;
    typedef LinkListIter<_data> _iter;

    _iter get() noexcept override {
        return _iter(&head);
    }

    void insert(const _data &d) noexcept override {
        _iter iter = get();
        iter.insert(d);
    }

    int count() noexcept override {
        _iter iter = get();
        int cnt = 0;
        while (iter.hasNext()) {
            cnt++;
            iter.next();
        }
        return cnt;
    }

private:
    node head;
};


/**
 * 定长数组列表
 * @tparam _data 数据类型
 * @tparam _SIZE 数组长度
 */
template<class _data, int _SIZE>
class FixedArrayList : public BaseList<_data, ArrayIter<_data>> {
public:
    ArrayIter<_data> get() noexcept override {
        return ArrayIter<_data>(source, &cnt);
    }

    void insert(const _data &d) noexcept override {
        get().insert(d);
    }

    int count() noexcept override {
        return cnt;
    }

private:
    _data source[_SIZE];
    int cnt = 0;
};

#endif //HOME_MONEY_LISTIMPL_H
