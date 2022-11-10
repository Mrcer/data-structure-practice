#include "./Include/include.h"
#include <string>
#include <iostream>
using namespace std;

void linked_binary_tree_test() {
    try {
        ArrayBinaryTree<int> tree;
        auto root = tree.query();
        cout << root->has_left() << endl;;
        root->set_left(1);
        root->set_right(2);
        auto left = root->left();
        left->set_right(3);
        auto right = root->right();
        right->set_left(4);
        right->set_right(5);
        tree.pre_order([](int &n) {
            cout << n;
            return false;
        });
        cout << endl;
        tree.print();
    } catch (const char *str) {
        cerr << str << endl;
    }
}

void array_binary_tree_test() {
    try {
        ArrayBinaryTree<int> tree;
        auto root = tree.query();
        cout << root->has_left() << endl;;
        root->set_left(1);
        root->set_right(2);
        auto left = root->left();
        left->set_right(3);
        auto right = root->right();
        right->set_left(4);
        right->set_right(5);
        tree.pre_order([](int &n) {
            cout << n;
            return false;
        });
        cout << endl;
        tree.print();
    } catch (const char *str) {
        cerr << str << endl;
    }
}

void tree_test() {
    Tree<std::string> tree;
    auto root = tree.query();
    root.append_child("a");
    root.append_child("b");
    root.append_child("asd");
    auto child = root.child();
    child.next();
    child.get_state().append_child("gf");
    child.next();
    child.get_state().append_child("we");
    child.get_state().append_child("vf");
    child.get_state().append_child("bv");    
    tree.print();
}

void linked_list_test() {
    LinkedList<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	list.erase(1);
	list.insert(1, 4);
	list.insert(0, 5);
	list.insert(2, 6);
	cout << list.pop_back() << endl;
	cout << list.pop_back() << endl;
}

void array_list_test() {
    ArrayList<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	list.erase(1);
	list.insert(1, 4);
	list.insert(0, 5);
	list.insert(2, 6);
	cout << list.pop_back() << endl;
	cout << list.pop_back() << endl;
}

void huffman_tree_test() {
        HuffmanTree hf("hello world");
        cout << "tree:" << endl;
        hf.print_tree();
        cout << "code table:" << endl;
        hf.print_code();
        cout << hf.encode("hello") << endl;
        cout << hf.decode(hf.encode("hello")) << endl;
}

void test_all() {
    cout << "Running LinkedList Test" << endl;
    linked_list_test();
    cout << "Running Tree Test" << endl;
    tree_test();
    cout << "Running ArrayBinaryTree Test" << endl;
    array_binary_tree_test();
    cout << "Running LinkedBinaryTree Test" << endl;
    linked_binary_tree_test();
    cout << "Running ArrayList Test" << endl;
    array_list_test();
    cout << "Running HuffmanTree Test" << endl;
    huffman_tree_test();
}