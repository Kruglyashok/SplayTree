#include "text_to_bin.h"
#include "binary_tree.h"
#include "splay_tree.h"
#include <iostream>


int main(int argc, char** argv)
{
	// [[ WORK WITH FILE ]]
	TextToBin ttb{};
	ttb.convertTxtToBin("text_resource.txt", "rec_bin");
	ttb.printBinFileContents("rec_bin");
	ttb.searcRec("rec_bin", 112233445565);
	ttb.displayRecByAddr("rec_bin", 3);
	ttb.addRec("rec_bin", ttb.genRec(112233445566, "F. M. Dostoeskiy ", " Some Title    "));
	ttb.printBinFileContents("rec_bin");
	
	// [[ BINARY TREE ]]
	BinaryTree bTree{};
	bTree.buildBinTree("rec_bin");
	bTree.printBinTree();
	bTree.insert(112233445567, 7);
	bTree.printBinTree();
	Node *node = bTree.search(112233445564);
	std::cout << "\nnode found with key = " << node->key << "  addr = " << node->addr << std::endl;
	bTree.deleteElem(112233445564);
	bTree.printBinTree();

	// [[ SPLAY TREE ]]
	SplayTree sTree{};
	sTree.buildBinTree("rec_bin");
	sTree.printBinTree();
	sTree.insert(112233445567, 6);
	sTree.printBinTree();
	STreeNode* sNode = sTree.search(112233445564);
	std::cout << "\nnode found with key = " << sNode->key << "  addr = "<< sNode->addr <<std::endl;
	sTree.deleteElem(112233445564);
	sTree.printBinTree();

	return 0;
}
