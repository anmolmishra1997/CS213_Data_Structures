#include <vector>
#include <functional>
#include <unordered_set>
#include <iostream>
// using namespace std;

// Input format 
// No of test cases
// contains num_bits followed by  number of hash functions to use
// i 5 1 2 3 4 5 // insert 5 elements
// d 3 4 2 1     // delete 3 elements
// l 4           // look up data item 4
// r             // report false positives and false negatives

struct myhash 
{ 
   // hash for object x, i th hash function, m-sized bit array of filter
   std::size_t operator()(int const& x, int const& i, int const& m) const 
   { 
       std::size_t h = std::hash<int>{}(x+i);
       h =  h % m;
       // std::cout << "Hash used is " << h << std::endl; 
	   return h;// (h should be between 0 and m-1)
   }
};

class BloomFilter{

private:
	std::vector<bool> m_bits;
	int m_numHashes;
	myhash m_myhash;

public:
	BloomFilter(int size,int numHashes);
	void insert(const int item);
	bool lookup( const int item) const;
	// delete is a reserved keyword in C++. Renamed the function to remove.
	void remove(const int item);
};

BloomFilter::BloomFilter(int size, int numHashes)
{
	m_bits.resize(size,false);
	m_numHashes = numHashes;
}

void BloomFilter::insert(const int item)
{
	int m = m_bits.size();
	for (int i = 0; i < m_numHashes; ++i)
	{
		m_bits[m_myhash(item,i,m)] = true;
	}
}

void BloomFilter::remove(const int item)
{
	int m = m_bits.size();
	for (int i = 0; i < m_numHashes; ++i)
	{
		m_bits[m_myhash(item,i,m)] = false;
	}
}

bool BloomFilter::lookup(const int item) const
{
	int m = m_bits.size();
	bool item_present = true;
	for (int i = 0; i < m_numHashes; ++i)
	{
		item_present &= m_bits[m_myhash(item,i,m)];
		if(!item_present)
			break;
	}
	return item_present;
}

int main()
{
	int t; // no of test cases
	std::cin >> t;

	char func_char;
	int x,y; // to store temporary integers

	std::unordered_set<int> mymap; // non-bloom data structure to maintain stats
	int false_positive,false_negative;
	int m_numInsert,m_numDelete;

	for (int i = 0; i < t; ++i)
	{
		std::cin >> x >> y;
		BloomFilter myfilter(x,y);
		false_negative = false_positive = 0;
		m_numDelete = m_numInsert = 0;

		while(true)
		{
			std::cin >> func_char;
			if(func_char == 'e')
				break;

			switch(func_char)
			{
				case 'd':
					std::cin >> x;
					for(int j=0; j< x; j++)
					{
						std::cin >> y;
						myfilter.remove(y);
						if(mymap.count(y))
							mymap.erase(y);
					}
					m_numDelete += x;
					break;

				case 'l':
					std::cin >> x;
					y = myfilter.lookup(x);
					if(mymap.count(x) != y)
					{
						if(y)
							false_positive++;
						else
							false_negative++;
					}
					std::cout << 'l' << " " << x << " " << y << std::endl;
					break;

				case 'r':
					std::cout << 'r' << " " << false_positive << " " << false_negative 
						 <<  " " << m_numInsert << " " << m_numDelete << std::endl;
					break;

				case 'i':
					std::cin >> x;
					for(int j=0; j< x; j++)
					{
						std::cin >> y;
						myfilter.insert(y);
						mymap.insert(y);
					}
					m_numInsert += x;
					break;
			}
		}
	}
	return 0;
}
