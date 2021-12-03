#include "splay_tree.h"
#include "text_to_bin.h"

void SplayTree::zig(STreeNode* x)
{
    STreeNode* p = x->parent;
    if (p->left == x)
    {
        STreeNode* A = x->left;
        STreeNode* B = x->right;
        STreeNode* C = p->right;

        x->parent = nullptr;
        x->right = p;

        p->parent = x;
        p->left = B;

        if (B != nullptr) B->parent = p;
    }
    else
    {
        STreeNode* A = p->left;
        STreeNode* B = x->left;
        STreeNode* C = x->right;

        x->parent = nullptr;
        x->left = p;

        p->parent = x;
        p->right = B;

        if (B != nullptr) B->parent = p;
    }
    turns++;
}

void SplayTree::zig_zig(STreeNode* x)
{
    STreeNode* p = x->parent;
    STreeNode* g = p->parent;
    if (p->left == x)
    {
        STreeNode* A = x->left;
        STreeNode* B = x->right;
        STreeNode* C = p->right;
        STreeNode* D = g->right;

        x->parent = g->parent;
        x->right = p;

        p->parent = x;
        p->left = B;
        p->right = g;

        g->parent = p;
        g->left = C;


        if (x->parent != nullptr)
        {
            if (x->parent->left == g) x->parent->left = x;
            else x->parent->right = x;
        }

        if (B != nullptr) B->parent = p;

        if (C != nullptr) C->parent = g;
    }
    else
    {
        STreeNode* A = g->left;
        STreeNode* B = p->left;
        STreeNode* C = x->left;
        STreeNode* D = x->right;

        x->parent = g->parent;
        x->left = p;

        p->parent = x;
        p->left = g;
        p->right = C;

        g->parent = p;
        g->right = B;

        if (x->parent != nullptr)
        {
            if (x->parent->left == g) x->parent->left = x;
            else x->parent->right = x;
        }

        if (B != nullptr) B->parent = g;

        if (C != nullptr) C->parent = p;
    }
    turns += 2;
}

void SplayTree::zig_zag(STreeNode* x)
{
    STreeNode* p = x->parent;
    STreeNode* g = p->parent;
    if (p->right == x)
    {
        STreeNode* A = p->left;
        STreeNode* B = x->left;
        STreeNode* C = x->right;
        STreeNode* D = g->right;

        x->parent = g->parent;
        x->left = p;
        x->right = g;

        p->parent = x;
        p->right = B;

        g->parent = x;
        g->left = C;

        if (x->parent != nullptr)
        {
            if (x->parent->left == g) x->parent->left = x;
            else x->parent->right = x;
        }

        if (B != nullptr) B->parent = p;

        if (C != nullptr) C->parent = g;
    }
    else
    {
        STreeNode* A = g->left;
        STreeNode* B = x->left;
        STreeNode* C = x->right;
        STreeNode* D = p->right;

        x->parent = g->parent;
        x->left = g;
        x->right = p;

        p->parent = x;
        p->left = C;

        g->parent = x;
        g->right = B;

        if (x->parent != nullptr)
        {
            if (x->parent->left == g) x->parent->left = x;
            else x->parent->right = x;
        }

        if (B != nullptr) B->parent = g;

        if (C != nullptr) C->parent = p;
    }
    turns += 2;
}

void SplayTree::splay(STreeNode* x)
{
    while (x->parent != nullptr)
    {
        STreeNode* p = x->parent;
        STreeNode* g = p->parent;
        if (g == nullptr) zig(x);
        else if (g->left == p && p->left == x) zig_zig(x);
        else if (g->right == p && p->right == x) zig_zig(x);
        else zig_zag(x);
    }
    this->root = x;
}

SplayTree::SplayTree()
{
    this->root = nullptr;
}

SplayTree::SplayTree(STreeNode* rt)
{
    this->root = rt;
}

STreeNode* SplayTree::search(unsigned long long x)
{
    STreeNode* ret = nullptr;
    STreeNode* curr = this->root;
    STreeNode* prev = nullptr;
    while (curr != nullptr)
    {
        prev = curr;
        if (x < curr->key) curr = curr->left;
        else if (x > curr->key) curr = curr->right;
        else
        {
            ret = curr;
            break;
        }
    }
    if (ret != nullptr) splay(ret);
    else if (prev != nullptr) splay(prev);
    return ret;
}

void SplayTree::insert(unsigned long long key, std::size_t addr)
{
    if (root == nullptr)
    {
        root = new STreeNode(key, addr);
        return;
    }
    STreeNode* curr = this->root;
    while (curr != nullptr)
    {
        if (key < curr->key)
        {
            if (curr->left == nullptr)
            {
                STreeNode* newSTreeNode = new STreeNode(key, addr);
                curr->left = newSTreeNode;
                newSTreeNode->parent = curr;
                splay(newSTreeNode);
                return;
            }
            else curr = curr->left;
        }
        else if (key > curr->key)
        {
            if (curr->right == nullptr)
            {
                STreeNode* newSTreeNode = new STreeNode(key, addr);
                curr->right = newSTreeNode;
                newSTreeNode->parent = curr;
                splay(newSTreeNode);
                return;
            }
            else curr = curr->right;
        }
        else
        {
            splay(curr);
            return;
        }
    }
}

STreeNode* subtree_max(STreeNode* subRoot)
{
    STreeNode* curr = subRoot;
    while (curr->right != nullptr) curr = curr->right;
    return curr;
}

STreeNode* subtree_min(STreeNode* subRoot)
{
    STreeNode* curr = subRoot;
    while (curr->left != nullptr) curr = curr->left;
    return curr;
}

void SplayTree::deleteElem(unsigned long long x)
{
    STreeNode* del = search(x);
    if (del == nullptr)
    {
        return;
    }
    STreeNode* L = del->left;
    STreeNode* R = del->right;
    if (L == nullptr && R == nullptr)
    {
        this->root = nullptr;
    }
    else if (L == nullptr)
    {
        STreeNode* M = subtree_min(R);
        splay(M);
    }
    else if (R == nullptr)
    {
        STreeNode* M = subtree_max(L);
        splay(M);
    }
    else
    {
        STreeNode* M = subtree_max(L);
        splay(M);
        M->right = R;
        R->parent = M;
    }
    delete del;
}

void SplayTree::printBinTree(const std::string& prefix, const STreeNode* STreeNode, bool isLeft)
{
    if (STreeNode != nullptr)
    {
        std::cout << prefix;

        std::cout << (isLeft ? "|--" : "'--");

        // print the value of the STreeNode
        std::cout << STreeNode->key << std::endl;

        // enter the next tree level - left and right branch
        printBinTree(prefix + (isLeft ? "|   " : "    "), STreeNode->left, true);
        printBinTree(prefix + (isLeft ? "|   " : "    "), STreeNode->right, false);
    }
}

void SplayTree::printBinTree(const STreeNode* STreeNode)
{
    printBinTree("", STreeNode, false);
}

void SplayTree::printBinTree()
{
    printBinTree(root);
}

void SplayTree::buildBinTree(const char* binFileName)
{
    if (binFileName != "")
    {
        setlocale(LC_ALL, "Russian");
        FILE* binFile;
        Record rec{};
        std::size_t rec_size = sizeof(rec);
        std::size_t count = 0U;
        if (!fopen_s(&binFile, binFileName, "rb"))
        {
            std::cout << "\nbin file was opened" << std::endl;
            while ((fread(&rec, rec_size, 1, binFile)) == 1)
            {
                this->insert(rec.ISBN, count);
                std::cout << "new rec inserted = " << rec.ISBN << std::endl;
                count++;
                nodes++;
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

std::pair<std::size_t, std::size_t> SplayTree::getNodesTurns() const
{
    return std::pair<std::size_t, std::size_t>(nodes, turns);
}
