#ifndef BINARY_TREE
#define BINARY_TREE

#include <cstddef>
#include <string>
#include <iostream>
#include <memory>

template <typename T>
class BinaryTree {
public:
    class Query;

public:
    virtual std::unique_ptr<Query> query() = 0;
    bool pre_order(bool (*func)(T &));
    bool in_order(bool (*func)(T &));
    bool post_order(bool (*func)(T &));
    void print();
    void clear();
    virtual ~BinaryTree() {};

    class Query {
        friend class BinaryTree;
    public:
        bool is_leaf() const;
        virtual bool is_root() const = 0;
        bool is_left() const;
        bool is_right() const;
        virtual bool has_left() const = 0;
        virtual bool has_right() const = 0;
        virtual bool operator==(const Query &other) const = 0;
        virtual std::unique_ptr<Query> parent() = 0;
        virtual std::unique_ptr<Query> left() = 0;
        virtual std::unique_ptr<Query> right() = 0;

        virtual T& get() = 0;
        virtual bool remove() = 0;
        virtual bool set(const T& n) = 0;
        virtual bool set_left(const T& n) = 0;
        virtual bool set_right(const T& n) = 0;
        bool set(const std::shared_ptr<BinaryTree<T>> bt);
        bool set_left(const std::shared_ptr<BinaryTree<T>> bt);
        bool set_right(const std::shared_ptr<BinaryTree<T>> bt);
    protected:
        Query() { };
        bool invalid = false;
    };

protected:
    bool pre_order_helper(bool (*func)(T &), std::unique_ptr<Query> q);
    bool in_order_helper(bool (*func)(T &), std::unique_ptr<Query> q);
    bool post_order_helper(bool (*func)(T &), std::unique_ptr<Query> q);
    void print_helper(std::string prefix_head, std::string prefix_tail, std::unique_ptr<Query> q) const;
};

template <typename T>
bool BinaryTree<T>::pre_order(bool (*func)(T &)) {
    return this->pre_order_helper(func, query());
}

template <typename T>
bool BinaryTree<T>::in_order(bool (*func)(T &)) {
    return this->in_order_helper(func, query());
}

template <typename T>
bool BinaryTree<T>::post_order(bool (*func)(T &)) {
    return this->post_order_helper(func, query());
}

template <typename T>
void BinaryTree<T>::print() {
    this->print_helper("", "", query());
}

template <typename T>
void BinaryTree<T>::clear() {
    auto root = query();
    if(root->has_left()) root->left()->remove();
    if(root->has_right()) root->right()->remove();
    root->get() = T();
}

template <typename T>
bool BinaryTree<T>::pre_order_helper(bool (*func)(T &), std::unique_ptr<Query> q) {
    if(func(q->get())) return true;
    if(q->has_left()) {
        if(pre_order_helper(func, q->left())) return true;
    }
    if(q->has_right()) {
        if(pre_order_helper(func, q->right())) return true;
    }
    return false;    
}

template <typename T>
bool BinaryTree<T>::in_order_helper(bool (*func)(T &), std::unique_ptr<Query> q) {
    if(q->has_left()) {
        if(in_order_helper(func, q->left())) return true;
    }
    if(func(q->get())) return true;
    if(q->has_right()) {
        if(in_order_helper(func, q->right())) return true;
    }
    return false;    
}

template <typename T>
bool BinaryTree<T>::post_order_helper(bool (*func)(T &), std::unique_ptr<Query> q) {
    if(q->has_left()) {
        if(post_order_helper(func, q->left())) return true;
    }
    if(q->has_right()) {
        if(post_order_helper(func, q->right())) return true;
    }
    if(func(q->get())) return true;
    return false;    
}

template <typename T>
void BinaryTree<T>::print_helper(std::string prefix_head, std::string prefix_tail, std::unique_ptr<Query> q) const{
    std::cout << prefix_head << q->get() << std::endl;
    if(q->has_left()) print_helper(prefix_tail + "|- ", prefix_tail + "|  ", q->left());
    if(q->has_right()) print_helper(prefix_tail + "|- ", prefix_tail + "   ", q->right());
}

template <typename T>
bool BinaryTree<T>::Query::is_leaf() const{
    return !has_left() && !has_right();
}

template <typename T>
bool BinaryTree<T>::Query::is_left() const{
    if(is_root()) {
        return false;
    } else {
        std::unique_ptr<Query> p = parent();
        return p->has_left() && p->left() == *this;
    }
}

template <typename T>
bool BinaryTree<T>::Query::is_right() const{
    if(is_root()) {
        return false;
    } else {
        std::unique_ptr<Query> p = parent();
        return p->has_right() && p->right() == *this;
    }
}

template <typename T>
bool BinaryTree<T>::Query::set(const std::shared_ptr<BinaryTree<T>> bt) {
    auto query = bt->query();
    if(! this->set(query->get())) return false;
    if(query->has_left()) {
        if(! this->set_left(query->left()->get()))
            return false;
    } else {
        if(this->has_left()) this->left()->remove();
    }
    if(query->has_right()) {
        if(! this->set_right(query->right()->get()))
            return false;
    } else {
        if(this->has_right()) this->right()->remove();
    }
    return true;
}

template <typename T>
bool BinaryTree<T>::Query::set_left(const std::shared_ptr<BinaryTree<T>> bt) {
    if(!has_left()) {
        if(!set_left(T()))
            return false;
    }
    return this->left()->set(bt);
}

template <typename T>
bool BinaryTree<T>::Query::set_right(const std::shared_ptr<BinaryTree<T>> bt) {
    if(!has_right()) {
        if(!set_right(T()))
            return false;
    }
    return this->right()->set(bt);
}

#endif