#include <iostream>
#include "bst.h"

BST::BST():root(NULL){}


BST::~BST()
{
    freeMemory(root);
}

BST::BSTNode* BST::createBST(int arr[], int start,int end)
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



/*BST::BST(int arr[], int size)
{
	root = createBST(arr,0,size-1);
}*/


void BST::freeMemory(BST::BSTNode* node)
{
    if (node==NULL)
        return;
    freeMemory(node->left);
    freeMemory(node->right);
    delete node;
}


bool BST::find(BSTNode* curr, int val) const
{
	if(curr == NULL)
		return false;
	else{
		int curr_value = curr->data;
		if(curr_value > val)
			return find(curr->left, val);
		else if(curr_value < val)
			return find(curr->right,val);
		else
			return true;
	}
}


bool BST::search(int val) const
{
	return find(root,val);
}


void BST::insertLeaf(BSTNode* leaf , int val)
{

	BSTNode* curr = new BSTNode(val); // Node to be inserted 
	if(leaf == NULL)
		root = curr;
	
	else{

		int leafVal = leaf->data;
		if(leafVal > val)
			leaf->left = curr;
		else if(leafVal < val)
			leaf->right = curr;
	}
}


void BST::insert(int val)
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


typename BST::BSTNode* BST::minValueNode(BSTNode* node) const
{
	BSTNode* current = node;
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;
    return current;
}


typename BST::BSTNode* BST::remove(BSTNode* root , int val)
{
	// base case
    if (root == NULL) return NULL;
 
 	int currVal = root->data;
    
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


void BST::remove(int val)
{
	root = remove(root,val);
}

/////////////////////////////////////////////////////////////////////////////////////////added code here

typename BST::BSTNode* BST::balance(int v,BSTNode* curr)//rebalances the subtree given by curr
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


void BST::rebalance(int v)//rebalances along node with value v and update root
{
	if(root == NULL){//tree is empty
		return;
	}
	if(find(root,v)==false){// v is not in tree
		return;
	}
	root=balance(v,root);
}


void BST::printpre(BSTNode* root) const
{
    if (root == NULL)
        return;
    std::cout << root->data << " ";
    print(root->left);
    print(root->right);
}


void BST::printpre() const
{
    printpre(root);
    std::cout << std::endl;
}


void BST::printroot() const
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


void BST::print(BSTNode* root) const
{
    if (root == NULL)
        return;
    print(root->left);
    std::cout << root->data << " ";
    print(root->right);
}


void BST::print() const
{
    print(root);
    std::cout << std::endl;
}


