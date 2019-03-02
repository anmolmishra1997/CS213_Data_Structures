#include <iostream>
#include <myqueue.h>
using namespace std;
myqueue::node* myqueue::addnode(int a)
{
	node* temp = new node;
	temp -> data = a;
	temp -> next = NULL;
	return temp;
}

myqueue::node* myqueue::addelem(int a, node* temp)
{
	if (temp == NULL)
		temp = addnode(a);
	else
		temp->next = addelem(a, temp->next);
	return temp;
}
myqueue::myqueue()
{
	head = NULL;
	size = 0;
}
myqueue::~myqueue()
{		

	node * temp = head;
	while (temp!=NULL)
	{
		head = temp;
		temp = temp -> next;
		delete head;	
	}
}
bool myqueue::enqueue(int a)
{
	if (head == NULL)
		head = addnode(a);
	else
		head = addelem(a,head);
	size +=1;
	return true;
}
int myqueue::dequeue()
{
	if (head == NULL)
		return -1;
	else
	{
		node * temp = head->next;
		int a = head ->data;
		delete head;
		head = temp;
		size -= 1;
		return a;
	}
}
void myqueue::print()
{
	node * temp = head;
	if (temp == NULL)
		cout << "null";
	while (temp!=NULL)
	{
		cout << temp -> data << " ";
		temp = temp -> next;
	}
	cout << endl;
}
int main()
{
	myqueue queue;
	char ch;
	int n;
	cin >> ch;
	while (ch != 'q')
	{
		if ( ch == 'e')
		{	
			int a;
			cin >> n;
			for (int i=0; i<n ; i++)
			{
				cin >> a;
				bool b = queue.enqueue(a);
			}
		}
		if ( ch == 'p')
			queue.print();
		if ( ch == 'd')
		{
			cin >> n;
			for ( int i=0; i<n ; i++)
				int m = queue.dequeue();
		}
		cin >> ch;
	}
}