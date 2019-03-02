#include <iostream>

template <class T>
class BST
{
    // Internal class which stores only Node related information.
    struct BSTNode
    {
        T data;
        BSTNode * left;
        BSTNode * right;

        BSTNode(T val):data(val),left(NULL),right(NULL){}
    };
    //added by rishabh
    BSTNode* root;
    void print(BSTNode*) const;
    void freeMemory(BSTNode*);
    void insertLeaf(BSTNode* , T);
    BSTNode* remove(BSTNode*, T);
    BSTNode* minValueNode(BSTNode*) const;
    bool find(BSTNode*, T) const;
    BSTNode* createBST(T arr[],int,int);
    //added by mohit
    BSTNode* balance(T,BSTNode*);
    void printpre(BSTNode*) const;

public:
    //added by rishabh
    BST();
    ~BST();
    bool search(T) const;
    void insert(T);
    void remove(T);
    void print() const;
    //added by mohit
    void rebalance(T);
    void printpre() const; 
    void printroot() const; 
};
