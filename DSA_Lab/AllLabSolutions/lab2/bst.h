#include <iostream>

class BST
{
    // Internal class which stores only Node related information.
    struct BSTNode
    {
        int data;
        BSTNode * left;
        BSTNode * right;

        BSTNode(int val):data(val),left(NULL),right(NULL){}
    };
    //added by rishabh
    BSTNode* root;
    void print(BSTNode*) const;
    void freeMemory(BSTNode*);
    void insertLeaf(BSTNode* , int);
    BSTNode* remove(BSTNode*, int);
    BSTNode* minValueNode(BSTNode*) const;
    bool find(BSTNode*, int) const;
    BSTNode* createBST(int arr[],int,int);
    //added by mohit
    BSTNode* balance(int,BSTNode*);
    void printpre(BSTNode*) const;

public:
    //added by rishabh
    BST();
    ~BST();
   // BST(int arr[],int);
    bool search(int) const;
    void insert(int);
    void remove(int);
    void print() const;
    //added by mohit
    void rebalance(int);
    void printpre() const; 
    void printroot() const; 
};
