#include<vector>
#include<string>
#include<iostream>
#include<map>
#ifndef HUFFMAN_COMPRESSION_HUFFMANTREE_H
#define HUFFMAN_COMPRESSION_HUFFMANTREE_H
class Word{
public:
    std::string s;
    int val;
};
class WordList{
    friend class HuffmanTree;
public:
    std::vector<Word>list;
};
class TreeNode{
    friend class HuffmanTree;
private:
    std::string s;
    int val;
    TreeNode *father,*left,*right;
public:
    explicit TreeNode(int val);
    TreeNode(std::string &s,int val);
};
class HuffmanTree{
public:
    TreeNode *root;
    std::vector<std::pair<std::string,std::string>>list;
    std::map<std::string,std::string>map;
    HuffmanTree(WordList wordlist);
    void buildList(TreeNode *node,std::string s);
    void print();
};
#endif
