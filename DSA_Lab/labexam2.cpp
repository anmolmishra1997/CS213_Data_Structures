#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <set>
using namespace std;
int main()
{
	map<string,int> bank;
	map<string,int>::iterator it;

	map<int,set<string> > sorter;
	map<int,set<string> >::iterator it2;

	set<string> sample;
	set<string>::iterator it3;
	sorter[0] = sample;
	
	char ch;
	string name;
	int illegalcount=0;
	int amount;
	cin >> ch;
	while (ch!='E')
	{
		if (ch == 'O')
		{
			cin >> name;
			it = bank.find(name);
			if (it != bank.end())
				illegalcount+=1;
			else
			{
				bank.insert(make_pair(name,0));
				sorter.find(0)->second.insert(name);
			}

		}
		if (ch == 'D')
		{
			cin >> name;
			cin >> amount;
			it = bank.find(name);
			if (it == bank.end())
				illegalcount+=1;
			else
			{
				sorter.find(it->second)->second.erase(name);
				it->second = it->second+amount;
				it2 = sorter.find(it->second);
				if (it2==sorter.end())
				{
					set<string> S;
					S.insert(name);
					sorter[it->second] = S;
				}
				else
					it2->second.insert(name);
			}
		}
		if (ch == 'W')
		{
			cin >> name;
			cin >> amount;
			it = bank.find(name);
			if (it == bank.end())
				illegalcount+=1;
			else if (it -> second < amount)
				illegalcount+=1;
			else
			{
				sorter.find(it->second)->second.erase(name);
				it->second = it->second-amount;
				it2 = sorter.find(it->second);
				if (it2==sorter.end())
				{
					set<string> S;
					S.insert(name);
					sorter[it->second] = S;
				}
				else
					it2->second.insert(name);
			}
		}
		if (ch == 'P')
		{
			cin >> amount;
			int end;
			cin >> end;
			for (int i = amount; i<=end; i++)
			{
				it2 = sorter.find(i);
				if (it2!=sorter.end())
				if (!(it2->second.empty()))
				{
					cout << it2->first << " ";
					for (it3 = it2->second.begin() ; it3 != it2->second.end();)
					{	
						cout << *it3;
						it3++;
						if (it3 == it2->second.end())
							break;
						cout << " ";

					}
					cout << endl;
				}
			}
		}
		if (ch == 'C')
		{
			cin >> name;
			it = bank.find(name);
			if (it == bank.end())
				illegalcount+=1;
			else if (it -> second != 0)
				illegalcount+=1;
			else
			{
				sorter.find(it->second)->second.erase(name);
				bank.erase(name);
			}
		}
		cin >> ch;
	}
	cout << illegalcount << endl;
}