#ifndef ARRAY_BINARY_TREE
#define ARRAY_BINARY_TREE

#include "binary_tree.hpp"
#include <vector>

template <typename T>
class ArrayBinaryTree : public BinaryTree<T> {
public:
    class Query;
protected:
    struct Node;
typedef typename BinaryTree<T>::Query QueryBase;

public:
    ArrayBinaryTree();
    ArrayBinaryTree(const T &n);
    virtual std::unique_ptr<QueryBase> query() override;
    virtual ~ArrayBinaryTree() override;

    class Query: public QueryBase {
        friend class ArrayBinaryTree;
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
        Query(ArrayBinaryTree *_bt);
        Query(std::vector<Node> *_data, size_t _index);
    private:
        size_t parent_index() const;
        size_t left_index() const;
        size_t right_index() const;
        std::vector<Node> *data;
        size_t index;
    };
protected:
    struct Node
    {
        Node(): data(T()), occupied(false) { }
        Node(const T &n): data(n), occupied(true) { }
        Node(const Node &node) {
            data = node.data;
            occupied = node.occupied;
        }
        Node &operator=(const Node &node) {
            data = node.data;
            occupied = node.occupied;
            return *this;
        }
        T& get() {
            return data;
        }
        void set(const T &n) {
            data = T(n);
            occupied = true;
        }
        bool is_set() {
            return occupied;
        }
        void clear() {
            data = T();
            occupied = false;
        }
    private:
        T data;
        bool occupied;
    };
    
    std::vector<Node> data;
};

template <typename T>
ArrayBinaryTree<T>::ArrayBinaryTree(): data(0) {
    data.push_back(Node(T()));
}

template <typename T>
ArrayBinaryTree<T>::ArrayBinaryTree(const T &n): data(0) { 
    data.push_back(Node(n));
}

template <typename T>
std::unique_ptr<typename BinaryTree<T>::Query> ArrayBinaryTree<T>::query() {
    return std::unique_ptr<typename BinaryTree<T>::Query>(new Query(this));
}

template <typename T>
ArrayBinaryTree<T>::~ArrayBinaryTree() { }

template <typename T>
bool ArrayBinaryTree<T>::Query::is_root() const {
    return index == 0;
}

template <typename T>
bool ArrayBinaryTree<T>::Query::has_left() const {
    if(this->invalid) throw "Invalid Query!";
    size_t idx = left_index();
    return idx < data->size() && data->at(idx).is_set();
}

template <typename T>
bool ArrayBinaryTree<T>::Query::has_right() const {
    if(this->invalid) throw "Invalid Query!";
    size_t idx = right_index();
    return idx < data->size() && data->at(idx).is_set();
}

template <typename T>
bool ArrayBinaryTree<T>::Query::operator==(const typename BinaryTree<T>::Query &other) const {
    if(this->invalid) throw "Invalid Query!";
    try {
        const Query &casted_other = dynamic_cast<const Query&>(other);
        return casted_other.data == this->data && casted_other.index == this->index;
    } catch (std::bad_cast const &) {
        return false;
    }
}

template <typename T>
std::unique_ptr<typename BinaryTree<T>::Query> ArrayBinaryTree<T>::Query::parent() {
    if(this->invalid) throw "Invalid Query!";
    if(is_root()) {
        throw "No parent found!";
    } else {
        return std::unique_ptr<typename BinaryTree<T>::Query>(new Query(data, parent_index()));
    }
}

template <typename T>
std::unique_ptr<typename BinaryTree<T>::Query> ArrayBinaryTree<T>::Query::left() {
    if(this->invalid) throw "Invalid Query!";
    if(has_left())
        return std::unique_ptr<typename BinaryTree<T>::Query>(new Query(data, left_index()));
    else
        throw "No left child found!";
}

template <typename T>
std::unique_ptr<typename BinaryTree<T>::Query> ArrayBinaryTree<T>::Query::right() {
    if(this->invalid) throw "Invalid Query!";
    if(has_right())
        return std::unique_ptr<typename BinaryTree<T>::Query>(new Query(data, right_index()));
    else
        throw "No right child found!";
}

template <typename T>
T& ArrayBinaryTree<T>::Query::get() {
    if(this->invalid) throw "Invalid Query!";
    return data->at(index).get();
}

template <typename T>
bool ArrayBinaryTree<T>::Query::set(const T& n) {
    get() = n;
    return true;
}

template <typename T>
bool ArrayBinaryTree<T>::Query::remove() {
    if(this->invalid) throw "Invalid Query!";
    if(has_left()) left()->remove();
    if(has_right()) right()->remove();
    data->at(index).clear();
    this->invalid = true;
    return true;
}

template <typename T>
bool ArrayBinaryTree<T>::Query::set_left(const T& n) {
    if(this->invalid) throw "Invalid Query!";
    if(!has_left() && left_index() >= data->size()) data->resize(left_index() + 1);
    data->at(left_index()).set(n);
    return true;
}

template <typename T>
bool ArrayBinaryTree<T>::Query::set_right(const T& n) {
    if(this->invalid) throw "Invalid Query!";
    if(!has_right() && right_index() >= data->size()) data->resize(right_index() + 1);
    data->at(right_index()).set(n);
    return true;
}

template <typename T>
ArrayBinaryTree<T>::Query::Query(ArrayBinaryTree *_bt) : data(&(_bt->data)), index(0) { }

template <typename T>
ArrayBinaryTree<T>::Query::Query(std::vector<Node> *_data, size_t _index) : data(_data), index(_index) { }

template <typename T>
size_t ArrayBinaryTree<T>::Query::parent_index() const {
    return (index - 1) >> 1;
}

template <typename T>
size_t ArrayBinaryTree<T>::Query::left_index() const {
    return (index << 1) + 1;
}

template <typename T>
size_t ArrayBinaryTree<T>::Query::right_index() const {
    return (index << 1) + 2;
}

#endif