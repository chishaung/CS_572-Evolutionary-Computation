// What does temp does? -> a parameter which can lead system goes "bad"

#include <iostream>
#include "rand.h"
#include "func.h"
#include <stdlib.h>
#define Trial 100
#define Epoch 10
#define EVA 100000


using namespace std;



/*
x is mutated by adding a sample from the uniform 
random number generator with in the range [−0.1, 0.1]

If the new x is outside the acceptable range for x 
then another random number is drawn (generally one must be careful 
with this approach that this isn’t too frequent an event). 
y will be mutated by a second sample from the same generator.
*/

void Uniform_Mutation(float x, float y, float &mutated_x, float &mutated_y) {

	double val;
	do {
	val = randPMUnit() / 10;
	mutated_x = x + (float)val;
	} while (mutated_x < -100 || mutated_x > 100);

	do {
	val = randPMUnit() / 10;
	//cout << "Val y: " << val << endl;
	mutated_y = y + (float)val;
	} while (mutated_y < -100 || mutated_y > 100);

	if (mutated_x > 100)
		cout << ">>>>" << endl;

	if (mutated_x < -100)
		cout << "<<<<" << endl;


}	

void Normal_Mutation(float x, float y, float &mutated_x, float &mutated_y) {

	
	

	double val;
	do {
	val = randNorm(0.1);
	mutated_x = x + (float)val;
	} while (mutated_x < -100 || mutated_x > 100);

	do {
	val = randNorm(0.1);
	//cout << "Val y: " << val << endl;
	mutated_y = y + (float)val;
	} while (mutated_y < -100 || mutated_y > 100);

	if (mutated_x > 100)
		cout << ">>>>" << endl;

	if (mutated_x < -100)
		cout << "<<<<" << endl;


	//cout << "Val: " << val << endl;

	
}

void Cauchy_Mutation(float x, float y, float &mutated_x, float &mutated_y) {
	

	double val;
	do {
	val = randCauchy(0, 0.1);
	mutated_x = x + (float)val;
	} while (mutated_x < -100 || mutated_x > 100);

	do {
	val = randCauchy(0, 0.1);
	//cout << "Val y: " << val << endl;
	mutated_y = y + (float)val;
	} while (mutated_y < -100 || mutated_y > 100);

	if (mutated_x > 100)
		cout << ">>>>" << endl;

	if (mutated_x < -100)
		cout << "<<<<" << endl;


}
void Mutation_Selector(int choice, float x, float y, float &mutated_x, float &mutated_y) {

	

	switch (choice) {

		case 0:
			Uniform_Mutation(x, y, mutated_x, mutated_y); 
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
bool accept(float newf, float f, float temp)
{
	return (newf>=f) || (randUnit()<exp((newf-f)/temp));
}

int main(int argc, char* argv[]) {

	float x, y, fitness; 

	float best_x, best_y, best_fitness = -100;

	float mutated_x, mutated_y, mutated_Fitness;

	int epochImproves, numEvalsIsInEpoch = 0;
	int choice;
	int best_location = 0;
	int total_improve = 0;

	float rate;
	float temp, cooling;



	if (argc != 4) {
		cout << "Error! need 3 arguments for this program. " << endl;
		return -1;
	}

	else {
		choice = atoi(argv[1]);
		temp = (float)atof(argv[2]);
		cooling = (float)atof(argv[3]);

		if (choice < 0 || choice >2) {
			cout << "Error! invalid mutation choice. " << endl;
			return -1;
		}
		if (cooling < 0 || cooling > 1) {
			cout << "Error! invalid cooling constant. " << endl;
			return -1;
		}

	}
	

	initRand();


	for (int i = 0; i < Trial; i++) {

		x = randPMUnit() * 100;
		y = randPMUnit() * 100;

		cout << "X: " << x << endl << "Y: " << y << endl;
		best_x = x;
		best_y = y;

		for (int j = 0; j < EVA; j++) {

			epochImproves = 0;
			numEvalsIsInEpoch = 0;
			for (int i = 0; i < Epoch; i++) {


				numEvalsIsInEpoch++;
				Mutation_Selector(choice, x, y, mutated_x, mutated_y);
				fitness = fr(x, y);
				mutated_Fitness = fr(mutated_x, mutated_y);
				if (accept(mutated_Fitness, fitness, temp)) {
					epochImproves++;
					total_improve++;

					x = mutated_x;
					y = mutated_y;
					fitness = mutated_Fitness;

					//cout << "Fitness: " << fitness << endl;

					if (fitness > best_fitness) {
						best_x = x; 
						best_y = y;
						best_fitness = fitness;
						best_location = j;
					}
				}
			}


			//cout << "Temp: " << temp << endl;
			rate = (float)epochImproves/(float)numEvalsIsInEpoch;
			//cout << "Rate: " << rate << endl;


			if (cooling < 1) {

				if (EVA % 200 == 0) {
					// cooler
					if (rate > 0.9)
						temp *= cooling;
					// hotter
					if (rate < 0.1)
						temp /= cooling;
				}
			}

		}
		// cout << "Accept times: " << epochImproves << endl;
		// report results.
	//}

		cout << best_location << " " << total_improve << " " 
		     << best_x << " " << best_y << " " << best_fitness 
		     << endl;
	}

	return 0;
}