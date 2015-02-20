#include <iostream>
#include <stdlib.h> 
#include "rand.h"
#include "func.h"
#include "math.h"
using namespace std;

int main () {
	
	//double x = 0.998822;
	//double y = -3.97946;
	//double x = -2.02757;
	//double y = -39.0073;
	//double fitness;

	//fitness = fr(x,y);
	//cout << "Fitness: " << fitness << endl;
	initRand();
	double min, max, val, sum, avg;
	min = 10000000;
	max = -10000000;

	for (int i = 0; i < 10000; i++) {
		//cout << "randPMUnit: " << randPMUnit() / 10 << endl;
		//val = randPMUnit() / 10;
		val = randNorm(0.1);
		//val = randCauchy(0, 0.1);
		cout << val << endl;
		if (val > max)
			max = val;
		if (val < min)
			min = val;
		sum = sum + abs(val);

	}
	avg = sum / 10000;
	cout << "Max: " << max << endl;
	cout << "Min: " << min << endl;
	cout << "Sum: " << sum << endl;
	cout << "Avg: " << avg << endl;
//cout << exp((2.2-5.3)/-50) << endl;
	return 0;
}