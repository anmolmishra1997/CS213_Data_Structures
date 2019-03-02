#include <iostream>
#include <mystack.h>
using namespace std;
int main()
{
	int n;
	cin >>n;
	int arr[n];
	int nextarr[n];
	int indexarr[n];
	for (int i=0; i<n; i++)
	{
		cin >> arr[i];
		nextarr[i] = -1;
		indexarr[i] = -1;
	}
	Stack st;
	Stack stindex;
	st.push(arr[0]);
	stindex.push(0);
	for (int i=1; i<n; i++)
	{	
		if (arr[i]<st.top())
		{
			st.push(arr[i]);
			stindex.push(i);
		}
		else
		{
			while ( !st.empty() && arr[i]>=st.top())
			{
				int a= stindex.pop();
				nextarr[a] = arr[i];
				indexarr[a] = i;
				int b =st.pop();
			}
			st.push(arr[i]);
			stindex.push(i);
		}
	}

	//-----------------------------------------
	int waterstored = 0;
	for (int i=1; i<n;i++)
	{	
		int maxbefore = arr[i];
		int maxafter = nextarr[i];
		if (maxafter==-1)
			continue;
		int j =i-1;
		while (j>=0)
		{
			if (arr[j] > maxbefore)
			{
				maxbefore = arr[j];
				break;
			}
			j--;
		}
		int smaller = maxbefore;
		if (maxafter<maxbefore)
			smaller = maxafter;
		waterstored = waterstored + ((smaller-arr[i])*(indexarr[i]-j-1)); 
	}
	for (int i=0; i<n;i++)
		cout << arr[i] << " ";
	cout << endl;
	cout << waterstored;
}
