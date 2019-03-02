#include <iostream>

class BST
{
private:
    // Internal struct which stores node related information.
    struct BSTNode
    {
        int data;           // value in node is of type int
        BSTNode * left;
        BSTNode * right;
    };
    BSTNode* root;
    BSTNode* newNode(int a);
    BSTNode* Insert(BSTNode* temp,int a);
    BSTNode* minimum(BSTNode* temp);
    BSTNode* Remove(BSTNode* root, int a);
    void deletetree(BSTNode *temp);
    void Print(BSTNode* temp) const;
    void Printroot(BSTNode* temp) const;
    bool Search(BSTNode* temp,int a) const;
public:
    BST();                  // the basic constructor and destructor functions
    ~BST();  
    bool search(int) const; // search for a value in the tree
    void insert(int);       // insert a value/node in the tree
    void remove(int);       // remove value/node from the tree
    void rebalance(int);    // make value specified as new root, if node present

    void print() const;     // print values in sorted order
    void printroot() const; // print value of root, and its left child and 
                            // right child
};
