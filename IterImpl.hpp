//
// Created by abstergo on 2023/6/19.
//

#ifndef HOME_MONEY_ITERIMPL_HPP
#define HOME_MONEY_ITERIMPL_HPP

#include "base.hpp"


/**
 * 链表迭代器
 */
template<class _data>
class LinkListIter : public Iter<_data> {
public:
    typedef LinkNode<_data> node;

    explicit LinkListIter(node *parent) : parent(parent) {
        if (parent == nullptr)
            throw "can not be null";
    }

    bool hasNext() const noexcept override {
        return parent->next != nullptr;
    }

    void next() noexcept override {
        movePtr(*this);
    }

    _data value() const noexcept override {
        if (parent == nullptr)
            return _data();
        return parent->data;
    }

    void update(const _data &d) noexcept override {
        parent->data = d;
    }

    void remove() noexcept override {
        node *now = parent;
        node *last = now->pre;
        node *nxt = now->next;
        node::connect(last, nxt);
        delete now;
        parent = nxt;
    }

    void insert(const _data &obj) noexcept override {
        node *newone = new node();
        newone->data = obj;
        node *t = parent->next;
        node::connect(parent, newone);
        node::connect(newone, t);
        parent = newone->next;
    }

private:
    inline static node *movePtr(LinkListIter &iter) {
        node *p = iter.parent;
        iter.parent = p->next;
        return p;
    }

    node *parent = nullptr;
};


template<class _data>
class ArrayIter : public Iter<_data> {
public:
    ArrayIter(_data *source,int size) : source(source),index(0),cnt(size){

    }

    bool hasNext() const noexcept override {
        return cnt>index;
    }

    void next() noexcept override {
        index++;
    }

    _data value() const noexcept override {
        if(index>=cnt)
            return _data();
        return source[index];
    }

    void update(const _data &d) noexcept override {
        source[index]=d;
    }

    void remove() noexcept override {
        for(int i=index;i<cnt-1;i++)
        {
            source[index]=source[index+1];
        }
        --cnt;
    }

    void insert(const _data &obj) noexcept override {
        for(int i=index+1;i<cnt+1;i++)
        {
            source[i]=source[i-1];
        }
        source[index]=obj;
        cnt++;
    }

private:
    _data *source;
    int index;
    int cnt;
};

#endif //HOME_MONEY_ITERIMPL_HPP
