#include "binary_tree.h"

BinaryTree::BinaryTree(const char * _binFileName) : root(nullptr), binFileName(_binFileName) { std::cout << "\nBTree constr called" << std::endl; }

BinaryTree::BinaryTree() : root(nullptr) {}

BinaryTree::~BinaryTree()
{
}

void BinaryTree::insert(unsigned long long key, Node* leaf)
{
	if (key < leaf->key)
	{
		if (leaf->left != nullptr)
		{
			insert(key, leaf->left);
		}
		else
		{
			leaf->left = new Node;
			leaf->left->key = key;
			leaf->left->left = nullptr;
			leaf->left->right = nullptr;
		}
	}
	else
	{
		if (key >= leaf->key)
		{
			if (leaf->right != nullptr)
			{
				insert(key, leaf->right);
			}
			else {
				leaf->right = new Node;
				leaf->right->key = key;
				leaf->right->right = nullptr;
				leaf->right->left = nullptr;
			}
		}
	}
}

void BinaryTree::insert(unsigned long long key)
{
	if (root != nullptr)
	{
		insert(key, root);
	}
	else
	{
		root = new Node;
		root->key = key;
		root->left = nullptr;
		root->right = nullptr;
	}
}

Node* BinaryTree::search(unsigned long long key, Node * leaf)
{
	if (leaf != nullptr)
	{
		if (key == leaf->key)
		{
			return leaf;
		}
		if (key < leaf->key)
		{
			return search(key, leaf->left);
		}
		else
		{
			return search(key, leaf->right);
		}
	}
	else
	{
		return nullptr;
	}
}

Node* BinaryTree::search(unsigned long long key)
{
	return search(key, root);
}

Node* BinaryTree::minValueNode(Node* node) {
	Node* current = node;
	while (current && current->left != nullptr)
		current = current->left;
	return current;
}

void BinaryTree::deleteElem(unsigned long long key)
{
	root = deleteElem(key, root);
}

void BinaryTree::buildBinTree(const char* binFileName)
{
	if (binFileName != "")
	{
		setlocale(LC_ALL, "Russian");
		FILE* binFile;
		Record rec{};
		std::size_t rec_size = sizeof(rec);
		if (!fopen_s(&binFile, binFileName, "rb"))
		{
			std::cout << "\nbin file was opened" << std::endl;
			while ((fread(&rec, rec_size, 1, binFile)) == 1)
			{
				this->insert(rec.ISBN);
				std::cout << "new rec inserted = " << rec.ISBN << std::endl;
			}
			return;
			fclose(binFile);
		}
		else
		{
			std::cout << "\nBin File was not found" << std::endl;
			return;
		}
	}
}

void BinaryTree::printBinTree(const std::string& prefix, const Node* node, bool isLeft)
{
	if (node != nullptr)
	{
		std::cout << prefix;

		std::cout << (isLeft ? "|--" : "'--");

		// print the value of the node
		std::cout << node->key << std::endl;

		// enter the next tree level - left and right branch
		printBinTree(prefix + (isLeft ? "|   " : "    "), node->left, true);
		printBinTree(prefix + (isLeft ? "|   " : "    "), node->right, false);
	}
}

void BinaryTree::printBinTree(const Node* node)
{
	printBinTree("", node, false);
}

void BinaryTree::printBinTree()
{
	printBinTree(root);
}

Node* BinaryTree::deleteElem(unsigned long long key, Node* root) {
	if (root == nullptr) return root;
	if (key < root->key)
		root->left = deleteElem(key, root->left);
	else if (key > root->key)
		root->right = deleteElem(key, root->right);
	else {
		if (root->left == nullptr) {
			Node* temp = root->right;
			delete root;
			return temp;
		}
		else if (root->right == nullptr) {
			Node* temp = root->left;
			delete root;
			return temp;
		}
		Node* temp = minValueNode(root->right);
		root->key = temp->key;
		root->right = deleteElem(temp->key, root->right);
	}
	return root;
}