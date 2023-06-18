//
// Created by tongj on 2023/6/18.
//

#ifndef HOME_MONEY_BASE_HPP
#define HOME_MONEY_BASE_HPP


template<class _data>
class Iter {
public:
    typedef Iter<_data> self;

    virtual bool hasNext() const noexcept = 0;

    virtual void next() noexcept = 0;

    virtual _data value() const noexcept = 0;

    virtual void update(const _data d) noexcept = 0;

    virtual void remove() noexcept = 0;

    virtual void insert(const _data &obj) noexcept = 0;

    virtual ~Iter()
    = default;
};

template<class _data>
struct LinkNode {
    LinkNode *next = nullptr;
    LinkNode *pre = nullptr;
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


template<class _data>
class LinkList {
public:
    typedef LinkNode<_data> node;


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

    LinkListIter get() {
        return LinkListIter(&head);
    }

    void insert(const _data d) {
        LinkListIter iter = get();
        iter.insert(d);
    }

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
