#include <iostream>
#include <utility>
#include <vector>
using namespace std;



int main() {
	//Key and Fitness
	vector<pair<string, double> > vp;
	vp.push_back(make_pair("abcdefghijklmnopqrstuvwxyz", 0.012345));
	cout << vp[0].first << endl;
	cout << vp[0].second << endl;
	return 0;
}