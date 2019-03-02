#include <bits/stdc++.h>
#include <iostream>
#include <vector>
using namespace std;

class SegmentTree{
	private:
		std::vector<int> A; // Original array
		std::vector<int> st; // segement tree array
		int n;

		int left_index(int p){ return p<<1; }
		int right_index(int p){return (p<<1) + 1; }

		void build(int index, int left, int right);
		void update(int index, int left, int right, int & k);
		int rmq(int index,int left, int right,int & i,int & j);

	public:
		int rmq(int i,int j);
		void update(int k, int val);
		SegmentTree(std::vector<int> & x);
};


void SegmentTree::build(int index, int left, int right) // O(n)
{
	if(left == right){							// as left == right, either one is fine
		st[index] = left;						// store the index
	}	
	else{										// recursively compute the values
		int mid = (left+right)>>1;		
		build(left_index(index),left,mid);
		build(right_index(index),mid+1,right);
		int p1 = st[left_index(index)],p2 = st[right_index(index)];
		st[index] = (A[p1] <= A[p2]) ? p1 : p2;
	}
}

int SegmentTree::rmq(int index,int left, int right,int & i,int & j) // O(log n)
{
	if(j < left ||  i > right )						// current segment outside query range
		return -1;
	if (left >= i && right <= j) 
		return st[index]; 							// inside query range

	int mid = (left+right)>>1;
	int p1 = rmq(left_index(index),left,mid,i,j);
	int p2 = rmq(right_index(index),mid+1,right,i,j);

	if(p1 == -1)									// if we try to access segment outside query 
		return p2;
	if(p2 == -1)
		return p1;
	return (A[p1] <= A[p2]) ? p1 : p2;				// same as above as in build routine
}

void SegmentTree::update(int index, int left, int right, int & k)
{
	int mid = (left + right) >> 1;
	if(left == right)
		return;
	if(mid >= k){
		update(left_index(index),left,mid,k);
	}
	else{
		update(right_index(index),mid+1,right,k);
	}
	int p1 = st[left_index(index)],p2 = st[right_index(index)];
	st[index] = (A[p1] < A[p2]) ? p1 : p2;
}

SegmentTree::SegmentTree(std::vector<int> & x)
{
	A = x;
	n = A.size();
	st.resize(4*n,0);
	build(1,0,n-1);
}

void SegmentTree::update(int k, int val)
{
	A[k] = val;
	update(1,0,n-1,k);
}

int SegmentTree::rmq(int i, int j)
{
	return A[rmq(1,0,n-1,i,j)];  						// overloading
}

int main()
{
	/*int arr[] = { 18, 17, 13, 19, 15, 11, 20 }; // the original array
	std::vector<int> A(arr, arr + 7);
	SegmentTree st(A);
	printf("RMQ(1, 3) = %d\n", st.rmq(1, 3)); // answer = index 2
	printf("RMQ(4, 6) = %d\n", st.rmq(4, 6)); // answer = index 5
	st.update(4,10);
	printf("RMQ(4, 6) = %d\n", st.rmq(4, 6)); // answer = index 4
	*/
	vector<int> A;
	int n,q;
	cin>>n>>q;
	A.resize(n);
	for(int i=0;i<n;i++){
		cin>>A[i];
	}
	SegmentTree st(A);
	for(int i=0;i<q;i++){
		int a,b,c;
		cin>>a>>b>>c;
		if(a==1){
			cout<<st.rmq(b,c)<<"\n";
		}
		else{
			st.update(b,c);
		}
	}
}