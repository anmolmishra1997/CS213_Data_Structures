#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <queue>
#include <vector>
#include <string>
#include <set>
using namespace std;

#define pb push_back

struct data{
	int count; //it is the frequency of this word in documents
	unordered_set<int> docs; //set of documents in which this word is present
	data(){
		count=0;
	}
};

struct wordct{
	string w;
	int ct;
};

inline bool operator< (const wordct& lhs, const wordct& rhs){ /* do actual comparison */ return lhs.ct<rhs.ct;}

void getMostfreq(unordered_map<string,data> &H,int m){
	priority_queue<wordct> heap;
	unordered_map<string,data>::iterator it;
	int size=0;
	wordct tmp;
	for(it=H.begin();it!=H.end();it++)
	{
		tmp.ct=(-1)*(it->second.count);
		tmp.w=it->first;
		int c=tmp.ct;
		if(size!=m){
			heap.push(tmp);
			size++;
		}
		else{
			if(size==m){
				if(c<heap.top().ct){
					heap.pop();
					heap.push(tmp);
				}
			}
		}
	}
	
	vector<string> v;
	while(!heap.empty()){
		v.pb(heap.top().w);
		heap.pop();
	}
	size=v.size();
	for(int i=size-1;i>=0;i--){
		cout << H[v[i]].count << " " <<  v[i] << endl;
	}
	for(int i=0;i<m-size;i++){
		cout << "0 -1"<< endl;
	}
	cout<< "$" << endl;
}

unordered_set<int> Union(unordered_set<int> &H1,unordered_set<int> &H2){
	unordered_set<int> res;
	unordered_set<int>::iterator it;
	for(it=H1.begin();it!=H1.end();it++){
		res.insert(*it);
	}
	for(it=H2.begin();it!=H2.end();it++){
		res.insert(*it);
	}
	return res;
}

unordered_set<int> Intersection(unordered_set<int> &H1,unordered_set<int> &H2){
	unordered_set<int> res;
	unordered_set<int>::iterator it,it2;
	for(it=H1.begin();it!=H1.end();it++){
		it2=H2.find(*it);
		if(it2!=H2.end()){
			res.insert(*it);
		}
	}
	return res;
}

unordered_set<int> Except(unordered_set<int> &H1,unordered_set<int> &H2){
	unordered_set<int> res;
	unordered_set<int>::iterator it,it2;
	for(it=H1.begin();it!=H1.end();it++){
		it2=H2.find(*it);
		if(it2==H2.end()){
			res.insert(*it);
		}
	}
	return res;
}

void printHash(unordered_set<int> H1){
	set<int> H(H1.begin(), H1.end());
	set<int>::iterator it;
	for(it=H.begin();it!=H.end();it++){
		cout<<*it<<" ";
	}
	cout<< endl << "$" <<endl;
}

int main(){
	int k,q,m;
	string query;
	cin>>k>>q>>m;
	unordered_map<string,data> H;

	for(int i=0;i<k;i++){
		string filename,s;
		getline(cin,filename);
		cin >> filename;
		ifstream infile(filename);
		while(infile>>s){
			H[s].count++;
			H[s].docs.insert(i);
		}
		cin >> filename;
		// to remove the excess $
	}
	cin.ignore(); 
	getMostfreq(H,m);
	for (int i = 0; i < q; ++i)
	{
		getline(cin,query);
		istringstream iss(query);
		vector<string> tokens;
		copy(istream_iterator<string>(iss),
		     istream_iterator<string>(),
		     back_inserter(tokens));
		if(tokens[1] == "ONLY")
			printHash(H[tokens[0]].docs);
		else if (tokens[1] == "AND")
			printHash(Intersection(H[tokens[0]].docs,H[tokens[2]].docs));
		else if (tokens[1] == "OR")
			printHash(Union(H[tokens[0]].docs,H[tokens[2]].docs));
		else if(tokens[1] == "EXCEPT")
			printHash(Except(H[tokens[0]].docs,H[tokens[2]].docs));
	}
	return 0;
}