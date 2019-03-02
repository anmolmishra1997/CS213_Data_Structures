#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
using namespace std;

class minMaxHeap
{

private:
	vector<int> A;
	int heap_size;

	int leftChild(int & i){return (i << 1) + 1;}
	int rightChild(int & i){return (i << 1) + 2;}
	int parent(int & i){return (i-1) >> 1;}

	int level(int i);
	int bubbleUpMin(int & i);
	int bubbleUpMax(int & i);
	int bubbleUp(int i);

	int findMinChildIndex(int i);
	int findMaxChildIndex(int i);

	void TrickleDown(int i);
	void TrickleDownMin(int & i);
	void TrickleDownMax(int & i);

public:

	minMaxHeap();
	int insert(int key);
	int getSize();
	// all these operations assume that the heap is not empty
	int getmin();
	int getmax();
	void deletemin();
	void deletemax();
};

minMaxHeap::minMaxHeap()
{
	heap_size = 0;
}

int minMaxHeap::getSize()
{
	return heap_size;
}

int minMaxHeap::level(int i)
{
	int count = 0;
	while( i != 0){
		count++;
		i = parent(i);
	}
	return count;
}

int minMaxHeap::bubbleUpMin(int & i)
{
	int gp, p, temp;
  temp = i;
	
	while(i != 0 &&  (p = parent(i)) != 0)
	{
		gp = parent(p);
		if(A[i] < A[gp])
		{
			swap(A[i],A[gp]);
			i = gp;
		  temp = i;
		}
		else
			return i;
	}
  return temp;
}

int minMaxHeap::bubbleUpMax(int & i)
{
	int gp, p, temp;

  temp = i;

	while(i != 0 and (p = parent(i)) != 0)
	{
		gp = parent(p);
		if(A[i] > A[gp])
		{
			swap(A[i],A[gp]);
			i = gp;
    	temp = i;
		}
		else
			return i;
	}

  return temp;
}

int minMaxHeap::bubbleUp(int i)
{
	if(i != 0)
	{
		int parentNode = parent(i);

		// i is on a min level
		if(level(i) % 2 == 0)
		{
			if(A[i] > A[parentNode])
			{
				swap(A[i],A[parentNode]);
				return bubbleUpMax(parentNode);
			}
			else
			{
				return bubbleUpMin(i);
			}
		}
		// i is on a max level
		else
		{
			if(A[i] < A[parentNode])
			{
				swap(A[i],A[parentNode]);
				return bubbleUpMin(parentNode);
			}
			else
			{
				return bubbleUpMax(i);
			}
		}
	}
	return i;
}

void minMaxHeap::TrickleDown(int i)
{
	if(level(i) % 2 == 0)
		TrickleDownMin(i);
	else
		TrickleDownMax(i);
}

void minMaxHeap::TrickleDownMin(int & i)
{
	// Find the index 'm' which is the smallest of the children and grandchildren
    // of element with index 'i'
	int m = findMinChildIndex(i);
	int m_child = m;
	if( m != -1)
	{
		int r = findMinChildIndex(leftChild(i));
		if(r != -1 && A[r] < A[m])
		{
			m = r;
        	}
		
        	r = findMinChildIndex(rightChild(i));
		if(r != -1 && A[r] < A[m])
		{
		    m = r;
		}

		if(A[m] < A[i])
		{
			swap(A[m],A[i]);

			// m is a grandchild of 'i'
			if(m != m_child)
			{
				if(A[m] > A[parent(m)])
				{
					swap(A[m],A[parent(m)]);
				}
				TrickleDownMin(m);
			}
		}
	}
}

void minMaxHeap::TrickleDownMax(int & i)
{
	// Find the index 'm' which is the largest of the children and grandchildren
    // of element with index 'i'
	int m = findMaxChildIndex(i);
	int m_child = m;
	if( m != -1)
	{
		int r = findMaxChildIndex(leftChild(i));
		if(r != -1 && A[r] > A[m])
		{
			m = r;
        	}
		
	        r = findMaxChildIndex(rightChild(i));
		if(r != -1 && A[r] > A[m])
		{
			m = r;
		}

		if(A[m] > A[i])
		{
			swap(A[i],A[m]);
			// m is a granchild of i
			if(m != m_child)
			{
				if(A[m] < A[parent(m)])
				{
					swap(A[m],A[parent(m)]);
				}
				TrickleDownMax(m);
			}
		}
	}
}

int minMaxHeap::findMinChildIndex(int i)
{
	int minIndex = -1;
	int child  = leftChild(i);
	if(child < heap_size)
	{
		minIndex = child;
		child = rightChild(i);
		if(child < heap_size)
		{
			if(A[minIndex] > A[child])
				minIndex = child;
		}
	}
	return minIndex;
}

int minMaxHeap::findMaxChildIndex(int i)
{
	int maxIndex = -1;
	int child  = leftChild(i);
	if(child < heap_size)
	{
		maxIndex = child;
		child = rightChild(i);
		if(child < heap_size)
		{
			if(A[maxIndex] < A[child])
				maxIndex = child;
		}
	}
	return maxIndex;
}

int minMaxHeap::insert(int key)
{
	if(heap_size < A.size())
	{
		A[heap_size] = key;
	}
	else
	{
		A.push_back(key);
	}
	heap_size++;
	return bubbleUp(heap_size - 1);
}

int minMaxHeap::getmin()
{
	if(heap_size > 0)
	{
		return A[0];
	}
	else
		return 0;
}

int minMaxHeap::getmax()
{
	if(heap_size >= 3)
	{
		return (A[1] > A[2])? A[1] : A[2];
	}
	else if (heap_size > 0)
	{
		return A[heap_size - 1];
	}
	else
		return 0;
}

void minMaxHeap::deletemin()
{
	// i = 0 is the node with minimum value
	int i = 0;
	// Delete 'i' and replace it with last element of the heap
	if (heap_size>0){
		swap(A[i],A[--heap_size]);
		TrickleDown(i);
	}
}

void minMaxHeap::deletemax()
{
	if(heap_size > 2)
	{
		// i is the node with maximum value
	 	int i = (A[1] > A[2])? 1 : 2;
	 	// Delete 'i' and replace it with last element of the heap
	 	swap(A[i],A[--heap_size]);
	 	TrickleDown(i);
	}
	else if (heap_size > 0)
		// decrement heap size by 1
		heap_size--;
}

int main()
{
	minMaxHeap A;
	char ch;
	int elem;

	while (true)
	{
        cin >> ch;
		switch (ch)
		{
			case 'i':   // insert
			        cin >> elem;
					cout << elem << " " << A.insert(elem) << endl;
					break;
			case 'm':   // getmin
					cout << A.getmin() << endl;
					break;
			case 'M':   // getmax
					cout << A.getmax() << endl;
					break;
			case 'd':   // deletemin
					A.deletemin();
					cout << A.getmin() << endl;
					break;
			case 'D':   // deletemax
					A.deletemax();
					cout << A.getmax() << endl;
					break;
			case 'e':
				return 0;
		}
	}
	return 0;
}
