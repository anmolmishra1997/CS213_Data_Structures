#include <iostream>
#include <cstdio>
#include <utility>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <set>
#include <map>
using namespace std;

#define iterMaptoSet map<int,set<string> >::iterator
#define iterSet set<string>::iterator


class Account{

	map<string,int> book;
	map<int, set<string> > bal;

	public:
		int count;
		Account()
		{
			count = 0;
		}

		void open(const string & s)
		{
			if(!(book.count(s)))
			{
				book[s] = 0;
				bal[0].insert(s);
			}
			else 
				count++;
			return;
		}
		void close(const string & s)
		{
			if(book.count(s) && book[s] == 0)
			{
				book.erase(s);
				bal[0].erase(s);
				if(bal[0].empty())
					bal.erase(0);

			}
			else
				count++;
			return;
		}
		void withdraw(const string & s, int amount)
		{

			if(book.count(s))
			{
				int val = book[s];
				
				if(val >= amount){
					int p = val - amount;
					book[s] = p;
					bal[val].erase(s);
					
					if(bal[val].empty())
						bal.erase(val);
					
					bal[p].insert(s);
				}
				else
					count++;	
			}
			else 
				count++;
			return;
		}
		void deposit(const string & s, int amount)
		{
			if(book.count(s))
			{
				int val = book[s];
				int p = amount + val;
				book[s] = p;
				bal[val].erase(s);
				if(bal[val].empty())
						bal.erase(val);
				bal[p].insert(s);
			}
			else
				count++;
			return;
		}
		void print(int low , int high)
		{
			iterMaptoSet itLow, itHigh,it;
			itLow  = bal.lower_bound (low);
			itHigh = bal.upper_bound(high);

			for( it = itLow; it != itHigh; it++)
			{
				cout << it->first;
				for(iterSet it1 = it->second.begin();it1 != it->second.end();it1++)
				{
					cout <<" " << *it1 ;
				}
				cout <<"\n";
			}
			return;
		}
};

int main()
{
	Account bank;
	char c;
	int low=0,high=0,amount=0;
	string s;
	while(true)
	{
		cin >>c;
		if(c == 'O'){
			cin>>s;
			bank.open(s);
		}
		else if(c == 'C'){
			cin >> s;
			bank.close(s);
		}
		else if(c == 'D'){
			cin>> s >> amount;
			bank.deposit(s,amount); 
		}
		else if(c == 'W'){
			cin >> s >> amount;
			bank.withdraw(s,amount);
		}
		else if(c == 'P'){
			cin >>low >>high;
			bank.print(low,high);
		}
		else if(c == 'E'){
			break;
		}
	}
	cout << bank.count << "\n";
	return 0;
}
