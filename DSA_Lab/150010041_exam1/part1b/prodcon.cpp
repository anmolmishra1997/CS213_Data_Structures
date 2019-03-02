#include <iostream>
#include <prodcon.h>
using namespace std;
prodcon::node* prodcon::addnode(int a)
{
	node* temp = new node;
	temp -> data = a;
	temp -> next = NULL;
	return temp;
}

prodcon::node* prodcon::addelem(int a, node* temp)
{
	if (temp == NULL)
		temp = addnode(a);
	else
		temp->next = addelem(a, temp->next);
	return temp;
}
prodcon::prodcon()
{
	head = NULL;
	size = 0;
	current = 0;
}
prodcon::~prodcon()
{		

	node * temp = head;
	while (temp!=NULL)
	{
		head = temp;
		temp = temp -> next;
		delete head;	
	}
}
void prodcon::setsize(int a)
{
	size += a;
}
bool prodcon::enqueue(int a)
{
	if ( current == size)
		return false;
	if (head == NULL)
		head = addnode(a);
	else
		head = addelem(a,head);
	current +=1;
	return true;
}
int prodcon::dequeue()
{
	if (head == NULL)
		return -1;
	else
	{
		node * temp = head->next;
		int a = head ->data;
		delete head;
		head = temp;
		current -= 1;
		return a;
	}
}
void prodcon::print()
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
	prodcon queue;
	char ch;
	int n;
	cin >> ch;
	while (ch != 'q')
	{
		if ( ch == 'i' || ch == 'g')
		{
			cin >> n;
			queue.setsize(n);
		}
		if ( ch == 'p')
		{	
			int a;
			cin >> n;
			for (int i=0; i<n ; i++)
			{
				cin >> a;
				bool b = queue.enqueue(a);
			}
		}
		if ( ch == 'd')
			queue.print();
		if ( ch == 'c')
		{
			cin >> n;
			for ( int i=0; i<n ; i++)
				int m = queue.dequeue();
		}
		cin >> ch;
	}
}