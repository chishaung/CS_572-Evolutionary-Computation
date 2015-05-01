#include <iostream>
#include <map>
using namespace std;
int main()
{
     multimap<float, char*> mm;
     mm.insert(pair<float, char*>(3.0f, "apple"));
     mm.insert(pair<float, char*>(3.0f, "pear"));
     mm.insert(pair<float, char*>(2.6f, "orange"));
     mm.insert(pair<float, char*>(1.8f, "banana"));
     mm.insert(pair<float, char*>(6.3f, "lichee"));
     // 遍曆打印
     multimap<float, char*>::iterator  i, iend;
     iend = mm.end();
     for (i=mm.begin(); i!=iend; ++i)
         cout << (*i).second << '    ' << (*i).first << "元/斤 \n";
 
     return 0;
 }