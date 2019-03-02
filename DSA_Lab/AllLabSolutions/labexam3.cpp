// #include <bits/stdc++.h>

#include <vector>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <map>

using namespace std;
#define LLONG_MAX 2000000000000000000

struct poi
{
	vector<int> edgesto;	// list of POIs which I have a edge to
	vector<long long> edgeswt;	// weight of edges
	vector<string> categories;	// my tggged categories
	bool isallowed;	// to check whether the current is tagged with a category of interest
	bool isvisited;	//to be used during DFS
	poi()
	{
		isallowed = false;
		isvisited = false;
	}
	void addEdge(int dest, long long wt)
	{
		edgesto.push_back(dest);
		edgeswt.push_back(wt);
	}
	// can do it more efficiently by sorting the categories but this works!
	void updateAllowed(vector<string> & cats)
	{
		for(size_t i = 0; i < categories.size(); i++)
			for(size_t j = 0; j < cats.size(); j++)
				if(categories[i] == cats[j])
				{
					isallowed = true;
					return;
				}
	}
};

// returns the number of POIs in connected component containing
// POIs[index]
int DFS(vector<poi> &POIs, int index)
{
	POIs[index].isvisited = true;
	int count = 1;
	for(size_t i = 0; i < POIs[index].edgesto.size(); ++i)
	{
		int child = POIs[index].edgesto[i];
		if(POIs[child].isallowed && !POIs[child].isvisited)
		{
			count += DFS(POIs, child);
		}
	}
	return count;
}

// effectively calculating the cost of the Minimum spanning tree
long long getFare(vector<poi> &POIs, int index, int ansN)
{

	long long totalFare = 0;
	vector<long long> costs(POIs.size(), LLONG_MAX);
	vector<bool> addedPOI(POIs.size(), false);
	// currently at POIs[index], only this POI present in list
	int count = 1;
	costs[index] = 0;
	int added = index;
	addedPOI[index] = true;

	while(count < ansN)
	{
		for(size_t i = 0; i < POIs[added].edgesto.size(); i++)
		{
			int child = POIs[added].edgesto[i];
			long long fare = POIs[added].edgeswt[i];
			costs[child] = min(costs[child], fare);
		}
		long long minm = LLONG_MAX;
		int minmindex = -1;
		for(size_t i = 0; i < POIs.size(); i++)
		{
			if(costs[i] < minm && POIs[i].isallowed && !addedPOI[i])
			{
				minm = costs[i];
				minmindex = i;
			}
		}
		// Just a precaution, should never happen though
		if(minmindex == -1)
			break;
		added = minmindex;
		addedPOI[minmindex] = true;
		totalFare += minm;
		count++;
	}
	return totalFare;
}

// Functions to read line by line; Reading line by line is important
// Because we are not aware of the tagged categories of each POI in advance
void readInt(int & x)
{
	string s;
	getline(cin,s);
	istringstream iss(s);
	iss >> x;
}

void readTwo(int & x, int & y)
{
	string s;
	getline(cin,s);
	istringstream iss(s);
	iss >> x >> y;
}

int main()
{
	ios::sync_with_stdio(false);
	int T, P, R;
	// if queryType == 0, print (Max No. of POIs)  (No of tours with max POIs)
	// else print (Max No. of POIs)  (Minimum Total fare possible)
	int queryType;
	readInt(T);
	while(T > 0)
	{
		map<string, int> nameMap;
		string poi1, poi2, str;
		long long fare;
		readTwo(P,R);
		// list of all POIs
		vector<poi> POIs(P);
		// denote the list of categories
		vector<string> cats;

		// read all the POIs along with their categories
		for(int i = 0; i < P; ++i)
		{
			getline(cin, str);
			istringstream iss(str);
			iss >> poi1;
			nameMap[poi1] = i;

			while(iss >> str)
			{
				POIs[i].categories.push_back(str);
			}

		}
		// read all the edges along with their weights
		for (int i = 0; i < R; ++i)
		{
			getline(cin, str);
			istringstream iss(str);
			iss>>poi1>>poi2;
			iss>>fare;
			int x = nameMap[poi1];
			int y = nameMap[poi2];
			POIs[x].addEdge(y, fare);
			POIs[y].addEdge(x, fare);
		}

		// read all the categories in which I am interested in
		getline(cin, str);
		istringstream iss(str);
		while(iss >> str)
		{
			cats.push_back(str);
		}
		for(int i = 0; i < P; i++)
		{
			POIs[i].updateAllowed(cats);
		}
		// query 0, 1
		readInt(queryType);

		// FInd the maximum size strongly connected component
		int ansN = 0, N;
		vector<int> posIndices;
		for(int i = 0; i < P; i++)
		{
			if(POIs[i].isallowed && !POIs[i].isvisited)
			{
				N = DFS(POIs, i);
				if(N > ansN)
				{
					ansN = N;
					posIndices.clear();
					posIndices.push_back(i);
				}
				else if(N == ansN)
				{
					posIndices.push_back(i);
				}
			}
		}

		if(queryType == 0){
			cout << ansN << " " << posIndices.size() << endl;
			T--;
			continue;
		}

		// find the minimum fare tour
		long long ansC = LLONG_MAX, C;
		if(ansN > 1)
		{
			for(size_t i = 0; i < posIndices.size(); i++)
			{
				C = getFare(POIs, posIndices[i], ansN);
				if(C < ansC)
					ansC = C;
			}
		}
		else
		{
			ansC = 0;
		}
		cout<< ansN << " " << ansC << endl;
		T--;
	}
	return 0;
}
