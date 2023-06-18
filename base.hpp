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
        if (before != nullptr)
        {
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
 * 链表类
 * @tparam _data
 */

template<class _data>
class LinkList {
public:
    typedef LinkNode<_data> node;
    /**
     * 链表迭代器
     */
    class LinkListIter : public Iter<_data> {
    public:
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
            if(parent== nullptr)
                return _data();
            return parent->data;
        }

        void update(const _data d) noexcept override {
            parent->data = d;
        }

        void remove() noexcept override {
            node *now = parent;
            node* last=now->pre;
            node* nxt=now->next;
            node::connect(last,nxt);
            delete now;
            parent=nxt;
        }

        void insert(const _data &obj) noexcept override {
            node *newone = new node();
            newone->data = obj;
            node* t=parent->next;
            node::connect(parent,newone);
            node::connect(newone,t);
            parent=newone->next;
        }

    private:
        inline static node *movePtr(LinkListIter &iter) {
            node *p = iter.parent;
            iter.parent = p->next;
            return p;
        }

        node *parent = nullptr;
    };
    /**
     * 获取迭代器
     * @return
     */
    LinkListIter get() {
        return LinkListIter(&head);
    }

    /**
     * 插入
     * @param d
     */
    void insert(const _data d) {
        LinkListIter iter = get();
        iter.insert(d);
    }
    /**
     * 计数总数
     * @return
     */
    int count() const {
        LinkListIter iter = get();
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


#endif //HOME_MONEY_BASE_HPP
