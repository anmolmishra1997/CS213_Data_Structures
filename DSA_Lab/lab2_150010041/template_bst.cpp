#include <iostream>
#include "template_bst.h"
using namespace std;

template <class T>
typename BST<T>::BSTNode* BST<T>::newNode(T a)
{
	BSTNode* newNode = new BSTNode();
	newNode->data = a;
	newNode->left = newNode->right = NULL;
	return newNode;
}
template <class T>
typename BST<T>::BSTNode* BST<T>::Insert(BSTNode* temp,T a)
{
	if(temp == NULL)
		temp = newNode(a); 
	else if(a <= temp->data)
		temp->left = Insert(temp->left,a);
	else
		temp->right = Insert(temp->right,a);
	return temp;
}
template <class T>
typename BST<T>::BSTNode* BST<T>::minimum(BSTNode* temp)
{
    BSTNode* current = temp;
    while (current->left != NULL)
        current = current->left;
 	return current;
}
template <class T>
typename BST<T>::BSTNode* BST<T>::Remove(BSTNode* root, T a)
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
template <class T>
void BST<T>::deletetree(BSTNode *temp)
{
  if(temp!=NULL)
  {
    deletetree(temp->left);
    deletetree(temp->right);
    delete temp;
  }
}
template <class T>
bool BST<T>::Search(BSTNode* temp,T a) const
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
template <class T>
void BST<T>::Print(BSTNode* temp) const
{
	if (temp==NULL)
		return;
	Print(temp->left);
	cout << temp->data << " ";
	Print(temp->right);
}
template <class T>
void BST<T>::Printroot(BSTNode* temp) const
{
	if (temp==NULL)
		return;
	cout << temp->data << " ";
	Print(temp->left);
	Print(temp->right);
}
template <class T>
BST<T>::BST()
{
	root = NULL;
}
template <class T>
BST<T>::~BST()
{
	deletetree(root);
}
template <class T>
bool BST<T>::search(T a) const
{
	return Search(root, a);
}
template <class T>
void BST<T>::insert(T a)
{
	root = Insert(root, a);
}
template <class T>
void BST<T>::print() const
{
	Print(root);
	cout << endl;
}
template <class T>
void BST<T>::remove(T a)
{
	root = Remove(root,a);
}
template <class T>
void BST<T>::printroot() const
{
	Printroot(root);
	cout << endl;
}
template class BST<int>;
template class BST<float>;
template class BST<char>;