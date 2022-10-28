#ifndef LINKED_BINARY_TREE
#define LINKED_BINARY_TREE

/*
TODO:
1. fix copy error caused by illegal pointer copy
2. separate Query data from tree in case tree is deleted
3. add invalid error
*/
#include "binary_tree.hpp"
#include <memory>

template <typename T>
class LinkedBinaryTree: public BinaryTree<T> {
public:
    class Query;
protected:
    struct Node;
typedef typename BinaryTree<T>::Query QueryBase;

public:
    LinkedBinaryTree();
    LinkedBinaryTree(const T &n);
    virtual std::unique_ptr<QueryBase> query() override;
    virtual ~LinkedBinaryTree() override;

    class Query: public QueryBase {
        friend class LinkedBinaryTree;
    public:
        virtual bool is_root() const override;
        virtual bool has_left() const override;
        virtual bool has_right() const override;
        virtual bool operator==(const QueryBase &other) const override;

        virtual std::unique_ptr<QueryBase> parent() override;
        virtual std::unique_ptr<QueryBase> left() override;
        virtual std::unique_ptr<QueryBase> right() override;

        virtual T& get() override;
        virtual bool remove() override;
        virtual bool set(const T& n) override;
        virtual bool set_left(const T& n) override;
        virtual bool set_right(const T& n) override;
    protected:
        Query(LinkedBinaryTree *bt);
    private:
        Query(Node *sbt);
        Node *sub_tree;
    };
protected:
    struct Node
    {
        Node(T n, Node *p=nullptr) : data(n), parent(p) { }
        T data;
        Node *parent;
        Node *left = nullptr;
        Node *right = nullptr;
    };
    
private:
    Node *root;
};

template <typename T>
LinkedBinaryTree<T>::LinkedBinaryTree() : root(new Node(T())) { }

template <typename T>
LinkedBinaryTree<T>::LinkedBinaryTree(const T &n) : root(new Node(T(n))) { }

template <typename T>
std::unique_ptr<typename BinaryTree<T>::Query> LinkedBinaryTree<T>::query() {
    return std::unique_ptr<typename BinaryTree<T>::Query>(new Query(this));
}

template <typename T>
LinkedBinaryTree<T>::~LinkedBinaryTree() {
    this->clear();
    delete root;
}

template <typename T>
LinkedBinaryTree<T>::Query::Query(LinkedBinaryTree *bt) : sub_tree(bt->root) {}

template <typename T>
LinkedBinaryTree<T>::Query::Query(Node *sbt) : sub_tree(sbt) {}

template <typename T>
bool LinkedBinaryTree<T>::Query::is_root() const {
    return sub_tree->parent == nullptr;
}

template <typename T>
bool LinkedBinaryTree<T>::Query::has_left() const {
    return sub_tree->left != nullptr;
}

template <typename T>
bool LinkedBinaryTree<T>::Query::has_right() const {
    return sub_tree->right != nullptr;
}

template <typename T>
bool LinkedBinaryTree<T>::Query::operator==(const typename BinaryTree<T>::Query &other) const {
    try {
        const Query &casted_other = dynamic_cast<const Query&>(other);
        return casted_other.sub_tree == this->sub_tree;
    } catch (std::bad_cast const &) {
        return false;
    }
}

template <typename T>
std::unique_ptr<typename BinaryTree<T>::Query> LinkedBinaryTree<T>::Query::parent() {
    if(is_root()) {
        throw "No parent found!";
    } else {
        return std::unique_ptr<typename BinaryTree<T>::Query>(new Query(sub_tree->parent));
    }
}

template <typename T>
std::unique_ptr<typename BinaryTree<T>::Query> LinkedBinaryTree<T>::Query::left() {
    if(has_left())
        return std::unique_ptr<typename BinaryTree<T>::Query>(new Query(sub_tree->left));
    else
        throw "No left child found!";
}

template <typename T>
std::unique_ptr<typename BinaryTree<T>::Query> LinkedBinaryTree<T>::Query::right() {
    if(has_right())
        return std::unique_ptr<typename BinaryTree<T>::Query>(new Query(sub_tree->right));
    else
        throw "No right child found!";
}

template <typename T>
T& LinkedBinaryTree<T>::Query::get() {
    return sub_tree->data;
}

template <typename T>
bool LinkedBinaryTree<T>::Query::remove() {
    if(has_left()) left()->remove();
    if(has_right()) right()->remove();
    delete sub_tree;
    return true;
}

template <typename T>
bool LinkedBinaryTree<T>::Query::set(const T& n) {
    get() = n;
    return true;
}

template <typename T>
bool LinkedBinaryTree<T>::Query::set_left(const T& n) {
    if(has_left()) {
        sub_tree->left->data = n;
    } else {
        sub_tree->left = new Node(T(n), sub_tree);
    }
    return true;
}

template <typename T>
bool LinkedBinaryTree<T>::Query::set_right(const T& n) {
    if(has_right()) {
        sub_tree->right->data = n;
    } else {
        sub_tree->right = new Node(T(n), sub_tree);
    }
    return false;
}

#endif