#include <iostream>

class prodcon{

	// Internal struct which stores node related information.
    struct node
    {
        int data;           // value in node is of type int
        node * next;
    };

	node* head;             // use this pointer for start of queue
	size_t size;
	size_t current;

	node* addelem(int a, node* temp);
	node* addnode(int a);
// add variables, functions and function keywords as needed

public:
	prodcon() ;        // constructor, desctuctor
	~prodcon();
	void setsize(int a);
	bool enqueue(int); // add element to queue, return success/failure
	int dequeue();     // remove element from queue. return element or -1 (if not element)

	void print();      // print queue in FIFO order. print null if list empty
};
