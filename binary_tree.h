#pragma once
#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <iostream>
#include <string>
#include "text_to_bin.h"

struct Node
{
	unsigned long long key = 0;
	std::size_t addr = 0;
	Node *left, *right;
};

class BinaryTree
{
public:
	BinaryTree();
	~BinaryTree();
	void insert(unsigned long long, std::size_t);
	Node* search(unsigned long long);
	void deleteElem(unsigned long long);
	void buildBinTree(const char*);
	void printBinTree();
private:
	Node* root;
	Node* minValueNode(Node*);
	void insert(unsigned long long, std::size_t, Node*);
	Node* search(unsigned long long, Node*);
	Node* deleteElem(unsigned long long, Node*);
	void printBinTree(const std::string&, const Node*, bool);
	void printBinTree(const Node*);
};
#endif //BINARY_TREE_H