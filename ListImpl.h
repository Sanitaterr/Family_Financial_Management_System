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

    LinkListIter<_data> get() noexcept override {
        return _iter(&head);
    }

    void insert(const _data d) noexcept override {
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


#endif //HOME_MONEY_LISTIMPL_H
