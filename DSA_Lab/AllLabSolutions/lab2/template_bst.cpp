#include <iostream>
#include "template_bst.h"

template <class T>
BST<T>::BST():root(NULL){}

template <class T>
BST<T>::~BST()
{
    freeMemory(root);
}

template<class T>
typename BST<T>::BSTNode* BST<T>::createBST(T arr[], int start,int end)
{	
	if(start > end)
		return NULL;
	else if(start == end)
		return new BSTNode(arr[start]);
	int mid = (end + start)/2;
	BSTNode* node = new BSTNode(arr[mid]);
	node->left = createBST(arr,start,mid-1);
	node->right = createBST(arr,mid+1,end);
	return node;
}


template <class T>
void BST<T>::freeMemory(BST<T>::BSTNode* node)
{
    if (node==NULL)
        return;
    freeMemory(node->left);
    freeMemory(node->right);
    delete node;
}

template <class T>
bool BST<T>::find(BSTNode* curr, T val) const
{
	if(curr == NULL)
		return false;
	else{
		T curr_value = curr->data;
		if(curr_value > val)
			return find(curr->left, val);
		else if(curr_value < val)
			return find(curr->right,val);
		else
			return true;
	}
}

template <class T>
bool BST<T>::search(T val) const
{
	return find(root,val);
}

//insert a leaf node into tho tree
template <class T>
void BST<T>::insertLeaf(BSTNode* leaf , T val)
{

	BSTNode* curr = new BSTNode(val); // Node to be inserted 
	if(leaf == NULL)
		root = curr;
	
	else{

		T leafVal = leaf->data;
		if(leafVal > val)
			leaf->left = curr;
		else if(leafVal < val)
			leaf->right = curr;
	}
}

template <class T>
void BST<T>::insert(T val)
{

    BSTNode *temp,*prev;
    temp = prev = root;
    while(temp)
    {
        prev = temp;
        if (temp->data < val)
            temp = temp->right;
        else if(temp->data > val)
            temp = temp->left;
    }
    insertLeaf(prev,val);
}

template <class T>
typename BST<T>::BSTNode* BST<T>::minValueNode(BSTNode* node) const
{
	BSTNode* current = node;
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;
    return current;
}

template <class T>
typename BST<T>::BSTNode* BST<T>::remove(BSTNode* root , T val)
{
	// base case
    if (root == NULL) return NULL;
 
 	T currVal = root->data;
    
    // If the val to be deleted is smaller than the root's val,
    // then it lies in left subtree
    if (val < currVal)
        root->left = remove(root->left, val);
    
    // If the val to be deleted is greater than the root's val,
    // then it lies in right subtree
    else if (val > currVal)
        root->right = remove(root->right, val);
 
    // if val is same as root's val, then this is the node
    // to be deleted
    else
    {
    	BSTNode* temp;
    	if(root->left != NULL && root->right != NULL)
    	{
    		// node with two children: Get the inorder successor (smallest
        	// in the right subtree)
    		temp = minValueNode(root->right);
    		// Copy the inorder successor's content to this node
    		root->data = temp->data;
    		// Delete the inorder successor
    		root->right = remove(root->right, temp->data);
    	}
    	else{
			// case of 0 or 1 child
			if(root->left != NULL)
				temp = root->left;
			else
				temp = root->right;

	    	delete root;
	    	return temp;
    	}
	}
	return root;
}

template <class T>
void BST<T>::remove(T val)
{
	root = remove(root,val);
}

/////////////////////////////////////////////////////////////////////////////////////////added code here
template <class T>
typename BST<T>::BSTNode* BST<T>::balance(T v,BSTNode* curr)//rebalances the subtree given by curr
{
	if(curr->data==v){//if current node has value v, then no need to do anything
		return curr;
	}
	BSTNode* ptr;
	if(curr->data<v){//curr has less value so v is in its right subtree
		ptr = balance(v,curr->right);
		curr->right = ptr->left;
		ptr->left = curr;
 	}
 	else{//curr has greater value so v is in its left subtree
 		ptr = balance(v,curr->left);
		curr->left = ptr->right;
		ptr->right = curr;
 	}
 	return ptr;
}

template <class T>
void BST<T>::rebalance(T v)//rebalances along node with value v and update root
{
	if(root == NULL){//tree is empty
		return;
	}
	if(find(root,v)==false){// v is not in tree
		return;
	}
	root=balance(v,root);
}

template <class T>
void BST<T>::printpre(BSTNode* root) const
{
    if (root == NULL)
        return;
    std::cout << root->data << " ";
    print(root->left);
    print(root->right);
}

template <class T>
void BST<T>::printpre() const
{
    printpre(root);
    std::cout << std::endl;
}

template <class T>
void BST<T>::printroot() const
{
    if (root == NULL)
        return;
    std::cout << root->data << " ";
    if (root->left != NULL)
        std::cout << root->left->data << " ";
    if (root->right != NULL)
        std::cout << root->right->data << " ";
    std::cout << std::endl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
void BST<T>::print(BSTNode* root) const
{
    if (root == NULL)
        return;
    print(root->left);
    std::cout << root->data << " ";
    print(root->right);
}

template <class T>
void BST<T>::print() const
{
    print(root);
    std::cout << std::endl;
}

template class BST<int>;
template class BST<char>;
template class BST<float>;

