#include <sstream>
#include <iostream>

using namespace std;
 
// helper code to read line by line and word by wordfrom input file
// note that this program reads everything as strings, you may
// have to read some stuff as integers etc.

int main()
{
   string s;
   string x;

   getline(cin,s);
   istringstream iss(s);
   while (iss >> x)
      cout << x << '\n';

   return 0;
}
