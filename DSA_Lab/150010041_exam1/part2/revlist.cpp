#include <iostream>
using namespace std;
class myqueue{

	// Internal struct which stores node related information.
    struct node
    {
        int data;           // value in node is of type int
        node * next;
    };

	node* head;             // use this pointer for start of queue
	size_t size;

	node* addelem(int a, node* temp);
	node* addnode(int a);
// add variables, functions and function keywords as needed

public:
	myqueue() ;        // constructor, desctuctor
	~myqueue();
	int getsize();
	bool enqueue(int); // add element to queue, return success/failure
	int dequeue();     // remove element from queue. return element or -1 (if not element)

	void print();      // print queue in FIFO order. print null if list empty
};
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
int myqueue::getsize()
{
	return size;
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
		if ( ch == 'i')
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
		if ( ch == 'r')
		{
			cin >> n;
			int arr[n];
			int j = queue.getsize()/n;
			for (int k =0; k< j; k++)
			{
				for (int i=0; i<n; i++)
					arr[i] = queue.dequeue();
				for (int i=n-1; i>=0 ; i--)
					queue.enqueue(arr[i]);
			}
			j = queue.getsize()%n;
			for (int i=0; i<j; i++)
				arr[i] = queue.dequeue();
			for (int i=j-1; i>=0 ; i--)
				queue.enqueue(arr[i]);
		}
		cin >> ch;
	}
}