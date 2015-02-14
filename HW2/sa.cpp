// What does temp does? -> a parameter which can lead system goes "bad"

#include <iostream>
#include "rand.h"
#include "func.h"
#include <stdlib.h>
#define Trial 100
#define EVO 100000
#define cooling 1.0

using namespace std;



/*
x is mutated by adding a sample from the uniform 
random number generator with in the range [−0.1, 0.1]

If the new x is outside the acceptable range for x 
then another random number is drawn (generally one must be careful 
with this approach that this isn’t too frequent an event). 
y will be mutated by a second sample from the same generator.
*/

void Uniform_Mutation(double x, double y, double &mutated_x, double &mutated_y) {

	cout << "Uniform" << endl;
}

void Normal_Mutation(double x, double y, double &mutated_x, double &mutated_y) {

	cout << "Normal" << endl;
}

void Cauchy_Mutation(double x, double y, double &mutated_x, double &mutated_y) {
	cout << "Cauchy" << endl;

}
void Mutation_Selector(int choice, double x, double y, double &mutated_x, double &mutated_y) {

	cout << "chjoice: " << choice << endl;
	switch (choice) {

		case 0:
			Uniform_Mutation(x, y, mutated_x, mutated_y); 
			cout << "123" << endl;
		break;

		case 1:
			Normal_Mutation(x, y, mutated_x, mutated_y);
		break;

		case 2:
			Cauchy_Mutation(x, y, mutated_x, mutated_y);
		break;

		default:
		break;
	}
}



// Should we travel to the neighbor?
// newf -> Fitness of new point 
// f -> current fitness
// temp -> Temperature
bool accept(double newf, double f, double temp)
{
	return (newf>=f) || (randUnit()<exp((newf-f)/temp));
}

int main(int argc, char* argv[]) {

	double x, y, fitness; 

	double best_x, best_y, best_fitness;

	double mutated_x, mutated_y, mutated_Fitness;

	int epoch, epochImproves, numEvalsIsInEpoch;
	int choice;

	double rate;
	double temp;

	if (argc != 4) {
		cout << "Error! need 2 arguments for this program. " << endl;
		return 0;
	}

	else {
		choice = atoi(argv[1]);
	}
	cout << choice << endl;

	initRand();

	for (int i = 0; i < Trial; i++) {

		x = randPMUnit() * 100;
		best_x = x;

		for (int j = 0; j < EVO; j++) {

			epochImproves = 0;
			for (int i = 0; i < epoch; i++) {

				Mutation_Selector(choice, x, y, mutated_x, mutated_y);
				mutated_Fitness = fr(mutated_x, mutated_y);
				if (accept(mutated_Fitness, fitness, temp)) {
					epochImproves++;

					x = mutated_x;
					y = mutated_y;
					fitness = mutated_Fitness;

					if (fitness > best_fitness) {
						best_x = x; 
						best_y = y;
					}
				}
			}
			rate = epochImproves/numEvalsIsInEpoch;
			if (cooling < 1) {
				if (rate > 0.9)
					temp *= cooling;
				if (rate < 0.1)
					temp /= cooling;

			}

		}
		// report results.
	}
	

	return 0;
}