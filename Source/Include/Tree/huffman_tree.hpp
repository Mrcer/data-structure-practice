#ifndef HUFFMAN_TREE
#define HUFFMAN_TREE

#include <string>
#include <memory>
#include "include.h"

// 仅做实例，不具备压缩能力（懒得写bitstream）
// 由于优化问题，仅支持小写字母
class HuffmanTree {
public:
    HuffmanTree(std::string sample);
    std::string encode(std::string);
    std::string decode(const std::string &content);
    void print_tree();
    void print_code();
    
private:
    void compile_tree(const std::unique_ptr<BinaryTree<char>::Query> query, ArrayList<char> code);
    ArrayList<std::string> _table;
    std::shared_ptr<ArrayBinaryTree<char>> _decoder;
};

#endif