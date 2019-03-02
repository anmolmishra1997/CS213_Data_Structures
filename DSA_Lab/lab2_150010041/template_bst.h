#include <iostream>

template <class T>
class BST
{
private:
    // Internal struct which stores node related information.
    struct BSTNode
    {
        T data;           // value in node is of type int
        BSTNode * left;
        BSTNode * right;
	
	//BSTNode(T val):data(val),left(NULL),right(NULL){}
    };
    BSTNode* root;
    BSTNode* newNode(T a);
    BSTNode* Insert(BSTNode* temp,T a);
    BSTNode* minimum(BSTNode* temp);
    BSTNode* Remove(BSTNode* root, T a);
    void deletetree(BSTNode *temp);
    void Print(BSTNode* temp) const;
    void Printroot(BSTNode* temp) const;
    bool Search(BSTNode* temp,T a) const;
public:
    BST();                  // the basic constructor and destructor functions
    ~BST();
    bool search(T) const; // search for a value in the tree
    void insert(T);       // insert a value/node in the tree
    void remove(T);       // remove value/node from the tree
    void rebalance(T);    // make value specified as new root, if node present

    void print() const;     // print values in sorted order
    void printroot() const; // print value of root, and its left child and 
                            // right child
};
