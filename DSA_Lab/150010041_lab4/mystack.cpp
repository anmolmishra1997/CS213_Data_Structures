#include <iostream>
#include <mystack.h>
using namespace std;

Stack::Stack()
{
	head = NULL;
	size = 0;
}
Stack::~Stack()
{
}

void Stack::push(int a)
{
	node *temp = new node;
	temp -> data = a;
	temp -> next = NULL;
	if (head == NULL)
	{
		head = temp;
		size=1;
	}
	else
	{
		temp -> next = head;
		head = temp;
		size= size + 1;
	}
}
int Stack::top()
{
	return head->data;
}
int Stack::pop()
{
	int a = head->data;
	node * temp = head ->next;
	delete head;
	head = temp;
	size = size - 1;
	return a;
}
bool Stack::empty()
{
	if ( size == 0)
		return true;
	else
		return false;
}
