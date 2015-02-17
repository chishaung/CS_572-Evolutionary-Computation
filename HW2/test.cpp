#include <iostream>
#include "rand.h"
#include "func.h"
using namespace std;

int main () {
	
	double x = 0.998822;
	double y = -3.97946;
	double fitness;

	fitness = fr(x,y);
	cout << "Fitness: " << fitness << endl;

}