#include "text_to_bin.h"
#include "binary_tree.h"
#include "splay_tree.h"
#include <iostream>


int main(int argc, char** argv)
{
	TextToBin ttb{};
	ttb.readTxtFile("text_resource.txt", "rec_bin");
	ttb.searcRec("rec_bin", 112233445566U);
	ttb.addRec("rec_bin", ttb.genRec(112233445567U, "asdasdasdasd", "TItlse and Title 2"));
	ttb.searcRec("rec_bin", 112233445566U);
	ttb.searcRec("rec_bin", 112233445567U);
	ttb.displayRecByAddr("rec_bin", 10);
	
	BinaryTree tree{"rec_bin"};
	tree.buildBinTree("rec_bin");
	tree.printBinTree();

	SplayTree sTree{};
	sTree.buildBinTree("rec_bin");
	return 0;
}
