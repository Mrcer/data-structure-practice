#pragma once

#include <cstddef>
#include <string>
#include <vector>
#include <iostream>

// declear---------------------------------------------
template <typename T>
class Tree {
public:
    class Query;
    class Iterator;
protected:
    struct Node;

public:
    Tree();
    Query query();
    void clear();
    void print() const;
    ~Tree();

    class Query {
        friend class Tree;
    public:
        bool is_leaf() const;
        bool is_root() const;

        Query parent();
        Iterator child();
        T& get();
        bool remove();
        bool remove_child(const size_t index);
        bool insert_child(const size_t index, const T& data);
        bool append_child(const T& data);
    protected:
        Query(Node *node);
    private:
        Node *sub_tree;
    };

    class Iterator {
        friend class Tree;
    public:
        void next();
        bool has_next() const;
        T& get_data();
        Query get_state();
    protected:
        Iterator(Query q);
    private:
        Query state;
        std::vector<Node *>::iterator it;
    };

protected:
    struct Node {
        Node(T n, Node *p=nullptr): data(n), parent(p) {}
        T data;
        Node * parent;
        std::vector<Node *> children;
    };

private:
    Node *root;
    void print_helper(std::string prefix_head, std::string prefix_tail, Query q) const;
};

// implementation-----------------------------------------

template <typename T>
Tree<T>::Tree() {
    root = new Node(T());
}

template <typename T>
Tree<T>::Query Tree<T>::query() {
    return Query(root);
}

template <typename T>
void Tree<T>::clear() {
    Query(root).remove();
    root = new Node(T());
}

template <typename T>
Tree<T>::~Tree() {
    clear();
    delete root;
}

template <typename T>
bool Tree<T>::Query::is_leaf() const {
    return sub_tree->children.empty();
}

template <typename T>
bool Tree<T>::Query::is_root() const {
    return sub_tree->parent == nullptr;
}

template <typename T>
Tree<T>::Query Tree<T>::Query::parent() {
    return Query(sub_tree->parent);
}

template <typename T>
Tree<T>::Iterator Tree<T>::Query::child() {
    return Iterator(*this);
}

template <typename T>
T& Tree<T>::Query::get() {
    return sub_tree->data;
}

template <typename T>
bool Tree<T>::Query::remove() {
    if(is_leaf()) {
        delete sub_tree;
        return true;
    } else {
        for(Node *node: sub_tree->children)
            Query(node).remove();
        delete sub_tree;
        return true;
    }
}

template <typename T>
bool Tree<T>::Query::remove_child(const size_t index) {
    Query(sub_tree->children[index]).remove();
    return true;
}

template <typename T>
bool Tree<T>::Query::insert_child(const size_t index, const T &data) {
    auto pos = sub_tree->children.begin() + index;
    sub_tree->children.insert(pos, new Node(data, sub_tree));
    return true;
}

template <typename T>
bool Tree<T>::Query::append_child(const T& data) {
    return insert_child(sub_tree->children.size(), data);
}

template <typename T>
Tree<T>::Query::Query(Node *node) : sub_tree(node) { }

template <typename T>
Tree<T>::Iterator::Iterator(Query q): state(q), it(q.sub_tree->children.begin()) { }

template <typename T>
void Tree<T>::Iterator::next() {
    ++it;
}

template <typename T>
bool Tree<T>::Iterator::has_next() const {
    return it < state.sub_tree->children.end();
}

template <typename T>
T& Tree<T>::Iterator::get_data() {
    return (*it)->data;
}

template <typename T>
Tree<T>::Query Tree<T>::Iterator::get_state() {
    return Query(*it);
}

template <typename T>
void Tree<T>::print() const{
    print_helper("", "", Query(root));
}

template <typename T>
void Tree<T>::print_helper(std::string prefix_head, std::string prefix_tail, Query q) const{
    std::cout << prefix_head << q.get() << std::endl;
    if(q.is_leaf()) return;
    auto it = q.sub_tree->children.begin();
    auto end = q.sub_tree->children.end();
    while(it < end - 1) {
        print_helper(prefix_tail + "|- ", prefix_tail + "|  ", Query(*it));
        it++;
    }
    if(it != end) print_helper(prefix_tail + "|- ", prefix_tail + "   ", Query(*it));
}