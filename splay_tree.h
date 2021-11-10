#pragma once
#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H

#include <stdio.h>
#include <string.h>
#include <iostream>

struct STreeNode
{
    unsigned long long key;
    std::size_t addr;
    STreeNode* parent;
    STreeNode* left;
    STreeNode* right;

    STreeNode(unsigned long long key)
    {
        this->key = key;
        this->addr = 0;
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
    STreeNode* find(unsigned long long);
    void insert(unsigned long long);
    void deleteElem(unsigned long long);
    void printBinTree();
    void buildBinTree(const char*);
    void inOrderPrint(bool brackets);
};

#endif //SPLAY_TREE_H