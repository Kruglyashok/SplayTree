#pragma once
#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H

#include <stdio.h>
#include <string.h>
#include <iostream>

struct STreeNode
{
    unsigned long long key = 0;
    std::size_t addr = 0;
    STreeNode* parent = nullptr;
    STreeNode* left = nullptr;
    STreeNode* right = nullptr;

    STreeNode(unsigned long long key, std::size_t addr)
    {
        this->key = key;
        this->addr = addr;
        this->parent = nullptr;
        this->left = nullptr;
        this->right = nullptr;
    }
};

class SplayTree
{
    STreeNode* root;

    void zig(STreeNode*);
    void zig_zig(STreeNode*);
    void zig_zag(STreeNode*);

    void splay(STreeNode*);
    void printBinTree(const std::string&, const STreeNode*, bool);
    void printBinTree(const STreeNode*);

public:
    SplayTree();
    SplayTree(STreeNode*);
    STreeNode* search(unsigned long long);
    void insert(unsigned long long, std::size_t);
    void deleteElem(unsigned long long);
    void printBinTree();
    void buildBinTree(const char*);
};

#endif //SPLAY_TREE_H