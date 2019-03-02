#include <iostream>
#include <cstdlib>
using namespace std;
#include <myArray.h>
myArray::myArray(void)
{
	lastIndex = -1;
}
myArray::myArray(int n)
{
	arrLimit = n;
	lastIndex = -1;
	arr = new int[n];
}
myArray::myArray(int *a, int n)
{
	arr = new int[n];
	arrLimit = n;
	lastIndex = -1;
	for (int i=0; i<n;i++)
	{
		arr[++lastIndex] = *a;
		a++;
	}
}
void myArray::setArrayLimit(int n)
{
	arrLimit = n;
	arr = new int[n];
}
void myArray::addToArray(int n)
{
	if (arrLimit - lastIndex != 1)
		arr[++lastIndex] = n;
}
void myArray::addToArray(int *a,int k)
{	
	int i =0;
	while (arrLimit - lastIndex != 1 && i<k)
		arr[++lastIndex] = *a;
		a++;
		i++;
}
void myArray::printArray()
{
	for (int i =0; i<=lastIndex ; i++)
		cout << arr[i] << " ";
	cout << endl;
}
void myArray::deleteFromArray()
{
	if (lastIndex!=-1)
		lastIndex--;
}
void myArray::deleteFromArray(int k)
{
	int i = 0;
	while (lastIndex!=-1 && i<k)
	{
		lastIndex--;
		i++;
	}
}
bool myArray::isSorted()
{
	for ( int i =0; i<lastIndex ; i++)
	{
		if (arr[i]>arr[i+1])
			return false;
	}
	return true;
}
bool myArray::binarySearch(int a)
{
	int l=0, u=lastIndex;
	int m = (l+u)/2;
	while (l<=u)
	{
		m = (l+u)/2;
		if (arr[m] == a)
			return true;
		else if (arr[m] > a)
			u=m-1;
		else if (arr[m] < a)
			l = m+1;
	}
	return false;
}
bool myArray::isEqual(myArray A)
{
	if (size() != A.size())
		return false;
	for (int i=0; i<=lastIndex; i++)
		if (A.getValue(i) != arr[i])
			return false;
	return true;
}
int myArray::getValue(int index)
{
	if (index <= lastIndex)
		return arr[index];
	else
		cout << "INDEX OUT OF BOUND";
	return -1;
}
int myArray::size()
{
	return lastIndex+1;
}
myArray myArray::operator+(myArray& sample)
{
	myArray answer(arrLimit);
	for (int i=0; i<=lastIndex; i++)
	{
		int add = arr[i] + sample.getValue(i);
		answer.addToArray(add);
	}
	return answer; 
}
myArray::~myArray()
{
	delete[] arr;
}