#include <iostream>
#include "bst.h"
using namespace std;

BST::BSTNode* BST::newNode(int a)
{
	BSTNode* newNode = new BSTNode();
	newNode->data = a;
	newNode->left = newNode->right = NULL;
	return newNode;
}

BST::BSTNode* BST::Insert(BSTNode* temp,int a)
{
	if(temp == NULL)
		temp = newNode(a); 
	else if(a <= temp->data)
		temp->left = Insert(temp->left,a);
	else
		temp->right = Insert(temp->right,a);
	return temp;
}

BST::BSTNode* BST::minimum(BSTNode* temp)
{
    BSTNode* current = temp;
    while (current->left != NULL)
        current = current->left;
 	return current;
}

BST::BSTNode* BST::Remove(BSTNode* root, int a)
{
    if (root == NULL) 
    	return root;
    if (a < root->data)
        root->left = Remove(root->left, a);
	else if (a > root->data)
        root->right = Remove(root->right, a);
    else
    {
        if (root->left == NULL)
        {
            BSTNode *temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL)
        {
            BSTNode *temp = root->left;
            delete root;
            return temp;
        }
        
        BSTNode* temp = minimum(root->right);
        root->data = temp->data;
        root->right = Remove(root->right, temp->data);
    }
    return root;
}

void BST::deletetree(BSTNode *temp)
{
  if(temp!=NULL)
  {
    deletetree(temp->left);
    deletetree(temp->right);
    delete temp;
  }
}

bool BST::Search(BSTNode* temp,int a) const
{
	if(temp == NULL)
		return false;
	else if(temp->data == a)
		return true;
	else if(a <= temp->data)
		return Search(temp->left,a);
	else
		return Search(temp->right,a);
}

void BST::Print(BSTNode* temp) const
{
	if (temp==NULL)
		return;
	Print(temp->left);
	cout << temp->data << " ";
	Print(temp->right);
}

void BST::Printroot(BSTNode* temp) const
{
	if (temp==NULL)
		return;
	cout << temp->data << " ";
	Print(temp->left);
	Print(temp->right);
}
BST::BST()
{
	root = NULL;
}
BST::~BST()
{
	deletetree(root);
}
bool BST::search(int a) const
{
	return Search(root, a);
}
void BST::insert(int a)
{
	root = Insert(root, a);
}
void BST::print() const
{
	Print(root);
	cout << endl;
}
void BST::remove(int a)
{
	root = Remove(root,a);
}
void BST::printroot() const
{
	Printroot(root);
	cout << endl;
}