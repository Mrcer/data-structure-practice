#include "Tree/huffman_tree.hpp"
#include <cstring>
#include <algorithm>
#include <queue>
#include <memory>
#include <vector>
#include <iostream>

HuffmanTree::HuffmanTree(std::string sample) {
    struct Node
    {
        Node() = default;
        Node(int w, char c): w(w), tree(new ArrayBinaryTree<char>(c)) {}
        int w;
        std::shared_ptr<ArrayBinaryTree<char>> tree;
    };
    struct cmp {
        bool operator()(const Node &a, const Node &b) const {
            return a.w > b.w;
        }
    };
    std::priority_queue<Node, std::vector<Node>, cmp> q;  
    int w[256];
    memset(w, 0, sizeof(w));
    for(char c: sample) {
        w[int(c)]++;
    }
    for(int i = 'a' ; i < 'z' ; ++i) {
        q.push(Node(w[i], i));
        _table.push_back(std::string(""));
    }
    while(q.size() != 1) {
        std::shared_ptr<ArrayBinaryTree<char>> tt(new ArrayBinaryTree<char>('0'));
        Node left = q.top();
        q.pop();
        tt->query()->set_left(left.tree->query());
        Node right = q.top();
        q.pop();
        tt->query()->set_right(right.tree->query());
        Node tn;
        tn.w = left.w + right.w;
        tn.tree = tt;
        q.push(tn);
    }
    _decoder = q.top().tree;
    compile_tree(q.top().tree->query(), ArrayList<char>());
}

void HuffmanTree::compile_tree(const std::unique_ptr<BinaryTree<char>::Query> query, ArrayList<char> code) {
    if(query->is_leaf()) {
        char c = query->get();
        for(size_t i = 0 ; i < code.size() ; ++i) {
            _table[c - 'a'].push_back(code[i]);
        }
    } else {
        if(query->has_left()) {
            ArrayList<char> t(code);
            t.push_back('0');
            compile_tree(query->left(), t);
        }
        if(query->has_right()) {
            ArrayList<char> t(code);
            t.push_back('1');
            compile_tree(query->right(), t);
        }
    }
}

std::string HuffmanTree::encode(std::string str) {
    std::string res;
    for(char c: str) {
        if(c < 'a' or c > 'z') throw "HuffmanTree can only process lowercase letter!";
        res += _table[c - 'a'];
    }
    return res;
}

std::string HuffmanTree::decode(const std::string &content) {
    std::string res;
    auto query = _decoder->query();
    for(char c: content) {
        if(c == '0') {
            if(query->has_left())
                query = query->left();
            else
                throw "Unexpected token!";
        } else {
            if(query->has_right())
                query = query->right();
            else
                throw "Unexpected token!";
        }
        if(query->is_leaf()) {
            res += query->get();
            query = _decoder->query();
        }
    }
    return res;
}

void HuffmanTree::print_tree() {
    _decoder->print();
}

void HuffmanTree::print_code() {
    for(size_t i = 0 ; i < _table.size() ; ++i) {
        std::cout << char(i + 'a') << ": " << _table[i] << std::endl;
    }
}