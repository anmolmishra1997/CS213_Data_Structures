#include "myArray.h"

myArray::myArray(void){
	arrLimit=0;
	lastIndex=-1;
}

myArray::myArray(int n){
	arrLimit=n;
	arr=new int[n];
	lastIndex=-1;
}

myArray::myArray(int *a, int n){
	arrLimit=n;
	lastIndex=n-1;
	arr=new int[n];
	for(int i=0;i<n;i++)  arr[i]=a[i];
}

void myArray::addToArray(int a){
	if(lastIndex<arrLimit-1){
		arr[++lastIndex]=a;
	}
	
}

void myArray::addToArray(int *a,int k){
	int i=0;
	while(lastIndex < arrLimit-1 && i<k){
		arr[++lastIndex]=a[i++];
	}
}

void myArray::printArray(){
	for(int i=0;i<=lastIndex;i++){
		cout<<arr[i]<<" ";
	}
	cout << endl;
}

bool myArray::isSorted(){
	int i;
	for(i=1;i<=lastIndex;i++){
		if(arr[i]< arr[i-1]) return false;
	}
	return true;
}

void myArray::setArrayLimit(int k){
	arrLimit=k;
	arr=new int[k];
}

void myArray::deleteFromArray(){
	if(lastIndex>-1)
		lastIndex--;
}

void myArray::deleteFromArray(int k){
	for(int i=0;i<k && lastIndex>-1;i++,lastIndex--);
}

bool myArray::binarySearch(int a){
	if(isSorted()){
		int i=0;
		int j=lastIndex;
		while(i<=j){
			int mid=(i+j)/2;
			if (arr[mid]==a) return true;
			else if(arr[mid]>a) j=mid-1;
			else i=mid+1;
		}
		return false;
	}
	return false;
}

int myArray::getValue(int index){
	if(index<=lastIndex)
		return arr[index];
	else{
		cout<<"INDEX OUT OF BOUND";
		return -1;
	}
}

int myArray::size(){
	return lastIndex+1;
}

bool myArray::isEqual(myArray A){
	if(lastIndex!=A.size()-1){
		return false;
	}
	for(int i=0;i<=lastIndex;i++){
		if(arr[i]!=A.getValue(i)) return false;
	}
	return true;
}

myArray myArray::operator+(myArray& B){
	
	int n=B.size();
	//cout<<B.getValue(1);
	if(this->size()!=B.size()){
		return B;
	}
	myArray C(n);
	for(int i=0;i<n;i++){
		C.addToArray(this->arr[i]+B.getValue(i));
	}
	return C;
}

myArray::~myArray(void){
	delete(this->arr);
}

