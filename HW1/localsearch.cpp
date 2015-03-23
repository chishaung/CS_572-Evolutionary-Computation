#include "bitHelpers.h"
#include "rand.h"
#include <bitset>
#include <iostream>
#define EVO 10000

using namespace std;

double Scale_X(double x) {

	double scale;
	scale = ((x/1024) * 10);
	return scale;
}

double Scale_Y(double y) {

	double scale;
	scale = (y/1024) * 20 + (-10);
	return scale;
}


float Fitness(float x , float y) {

	float result;
	result = 1 / ((x-1)*(x-1) + (y-3)*(y-3) + 1);

	return result;
}

double RandomJump_Gray(Bit64 input, double fitness) {

	/*
	input = 3331;
	Bit64 Gray;
	cout << "INT: " << input << endl;
	cout << "BIN:  " << (bitset<16>) input << endl;
	Gray = bitGray(input);
	cout << "Gray: " << (bitset<16>) Gray << endl;
	Gray = bitDeGray(Gray);
	cout << "Gray: " << (bitset<16>) Gray << endl;
	*/

	int count = 0;
	int position = 1;
	int best_position;
	double Best_Fit;
	Best_Fit = fitness;
	Bit64 chromosome;
	Bit64 chromosome_mutated;
	chromosome = input & 0xfffff; 
	double x, y, mx, my;

	for (int i = 0; i < EVO; i++) {

		chromosome_mutated = randULL();		
		x = chromosome & 0x3ff;			// Original x
		y = (chromosome >> 10) & 0x3ff;	// Original y
		mx = chromosome_mutated & 0x3ff;			// Mutated x
		my = (chromosome_mutated >> 10) & 0x3ff;	// Mutated y
		//mx = bitDeGray((Bit64)mx);
		//my = bitDeGray((Bit64)my);
		position++;
		
		if ( Fitness(Scale_X(mx), Scale_Y(my)) > Fitness(Scale_X(x),Scale_Y(y)) ) {
			Best_Fit = Fitness(Scale_X(mx), Scale_Y(my));
			chromosome = chromosome_mutated;
			count++;
			best_position = position;
		}

	}
	double finalx, finaly;
	finalx = chromosome & 0x3ff;
	finaly = (chromosome >> 10) & 0x3ff;

	// The number of fitness evaluations when it found the best fitness it found in the number of evaluations allowed. •
	cout << best_position  << " "
	// The number of improving moves made.
	     << count << " "
	// The x and y that gave that fitness.
		 << Scale_X(finalx) << " " << Scale_Y(finaly) << " "
	// The best fitness found.
	     << Best_Fit << endl;
	

	     return Best_Fit;
}

double RandomJump_Binary(Bit64 input, double fitness) {

	int count = 0;
	int position = 1;
	int best_position;
	double Best_Fit;
	Best_Fit = fitness;
	Bit64 chromosome;
	Bit64 chromosome_mutated;
	chromosome = input & 0xfffff; 
	double x, y, mx, my;


	for (int i = 0; i < EVO; i++) {

		chromosome_mutated = randULL();		
		x = chromosome & 0x3ff;			// Original x
		y = (chromosome >> 10) & 0x3ff;	// Original y
		mx = chromosome_mutated & 0x3ff;			// Mutated x
		my = (chromosome_mutated >> 10) & 0x3ff;	// Mutated y
		position++;
		
		if ( Fitness(Scale_X(mx), Scale_Y(my)) > Fitness(Scale_X(x),Scale_Y(y)) ) {
			Best_Fit = Fitness(Scale_X(mx), Scale_Y(my));
			chromosome = chromosome_mutated;
			count++;
			best_position = position;
		}

	}
	double finalx, finaly;
	finalx = chromosome & 0x3ff;
	finaly = (chromosome >> 10) & 0x3ff;

	// The number of fitness evaluations when it found the best fitness it found in the number of evaluations allowed. •
	cout << best_position  << " "
	// The number of improving moves made.
	     << count << " "
	// The x and y that gave that fitness.
		 << Scale_X(finalx) << " " << Scale_Y(finaly) << " "
	// The best fitness found.
	     << Best_Fit << endl;
	
	return Best_Fit;
}



double BitFlip_Gray(Bit64 input, double fitness) {

	int count = 0;
	int position = 1;
	int best_position;
	int index;
	double Best_Fit;
	Best_Fit = fitness;
	Bit64 chromosome;
	Bit64 chromosome_mutated;
	chromosome = input & 0xfffff; 
	//chromosome = bitDeGray(chromosome);
	double x, y, mx, my;

	for (int i = 0; i < EVO; i++) {

		index = randMod(20);
		chromosome_mutated = (chromosome^(1 << index));		
		x = chromosome & 0x3ff;			// Original x
		y = (chromosome >> 10) & 0x3ff;	// Original y
		x = bitDeGray((Bit64)x);
		y = bitDeGray((Bit64)y);
		mx = chromosome_mutated & 0x3ff;			// Mutated x
		my = (chromosome_mutated >> 10) & 0x3ff;	// Mutated y
		mx = bitDeGray((Bit64)mx);
		my = bitDeGray((Bit64)my);

		position++;
		
		if ( Fitness(Scale_X(mx), Scale_Y(my)) > Fitness(Scale_X(x),Scale_Y(y)) ) {
			Best_Fit = Fitness(Scale_X(mx), Scale_Y(my));
			chromosome = chromosome_mutated;
			count++;
			best_position = position;
		}

	}
	double finalx, finaly;
	finalx = chromosome & 0x3ff;
	finaly = (chromosome >> 10) & 0x3ff;
	finalx = bitDeGray((Bit64)finalx);
	finaly = bitDeGray((Bit64)finaly);

	// The number of fitness evaluations when it found the best fitness it found in the number of evaluations allowed. •
	cout << best_position  << " "
	// The number of improving moves made.
	     << count << " "
	// The x and y that gave that fitness.
		 << Scale_X(finalx) << " " << Scale_Y(finaly) << " "
	// The best fitness found.
	     << Best_Fit << endl;

	     return Best_Fit;
}


double BitFlip_Binary(Bit64 input, double fitness) {

	int count = 0;
	int position = 1;
	int best_position;
	int index;
	double Best_Fit;
	Best_Fit = fitness;
	Bit64 chromosome;
	Bit64 chromosome_mutated;
	chromosome = input & 0xfffff; 
	double x, y, mx, my;

	for (int i = 0; i < EVO; i++) {

		index = randMod(20);
		chromosome_mutated = (chromosome^(1 << index));		
		x = chromosome & 0x3ff;			// Original x
		y = (chromosome >> 10) & 0x3ff;	// Original y
		mx = chromosome_mutated & 0x3ff;			// Mutated x
		my = (chromosome_mutated >> 10) & 0x3ff;	// Mutated y
		position++;
		
		if ( Fitness(Scale_X(mx), Scale_Y(my)) > Fitness(Scale_X(x),Scale_Y(y)) ) {
			Best_Fit = Fitness(Scale_X(mx), Scale_Y(my));
			chromosome = chromosome_mutated;
			count++;
			best_position = position;
		}

	}
	double finalx, finaly;
	finalx = chromosome & 0x3ff;
	finaly = (chromosome >> 10) & 0x3ff;

	// The number of fitness evaluations when it found the best fitness it found in the number of evaluations allowed. •
	cout << best_position  << " "
	// The number of improving moves made.
	     << count << " "
	// The x and y that gave that fitness.
		 << Scale_X(finalx) << " " << Scale_Y(finaly) << " "
	// The best fitness found.
	     << Best_Fit << endl;

	 return Best_Fit;
}


double Single_Dimension_Gray(Bit64 input, double fitness) {

	// First, Decide which should be mutated: x or y 
	int count = 0;
	int position = 0;
	int best_position;
	int choice;
	Bit64 chromosome;
	Bit64 chromosome_mutated;
	double x, y, mx, my;
	double Best_Fit;

	chromosome = input & 0xfffff;
	//chromosome = bitDeGray(chromosome);

	for (int i = 0; i < EVO; i++) {

		
		x = chromosome & 0x3ff;			// Original x
		y = (chromosome >> 10) & 0x3ff;	// Original y
		//x = bitDeGray((Bit64)x);
		//y = bitDeGray((Bit64)y);

		// Mutate X:
		if (randCoinToss()!=0) {

			// X + 1
			if (randCoinToss()!=0) {
				mx = x + 1;
				my = y;
				//mx = bitDeGray((Bit64)mx);
				//my = bitDeGray((Bit64)my);
			}

			// X - 1
			else {
				mx = x - 1;
				my = y;
				//mx = bitDeGray((Bit64)mx);
				//my = bitDeGray((Bit64)my);
			}
		}

		// Mutate Y:
		else {
			
			// Y + 1
			if (randCoinToss()!=0) {
				mx = x;
				my = y + 1;
				//mx = bitDeGray((Bit64)mx);
				//my = bitDeGray((Bit64)my);
			}

			// Y - 1
			else {
				mx = x;
				my = y - 1;
				//mx = bitDeGray((Bit64)mx);
				//my = bitDeGray((Bit64)my);
			}
		}

		

		// Combine new X and new Y to be new chromosome
		chromosome_mutated = ((Bit64)mx & 0x3ff) | ( ((Bit64)my << 10) & (0x3ff << 10) );
		position++;

		
		x = bitDeGray((Bit64)x);
		y = bitDeGray((Bit64)y);
		mx = bitDeGray((Bit64)mx);
		my = bitDeGray((Bit64)my);


		if ( Fitness(Scale_X(mx), Scale_Y(my)) > Fitness(Scale_X(x),Scale_Y(y)) ) {
			Best_Fit = Fitness(Scale_X(mx), Scale_Y(my));
			chromosome = chromosome_mutated;
			count++;
			best_position = position;
		}

	}
	double finalx, finaly;
	finalx = chromosome & 0x3ff;
	finaly = (chromosome >> 10) & 0x3ff;
	finalx = bitDeGray((Bit64)finalx);
	finaly = bitDeGray((Bit64)finaly);

	// The number of fitness evaluations when it found the best fitness it found in the number of evaluations allowed. •
	cout << best_position  << " "
	// The number of improving moves made.
	     << count << " "
	// The x and y that gave that fitness.
		 << Scale_X(finalx) << " " << Scale_Y(finaly) << " "
	// The best fitness found.
	     << Best_Fit << endl;

	     return Best_Fit;
}


double Single_Dimension_Binary(Bit64 input, double fitness) {

	// First, Decide which should be mutated: x or y 
	int count = 0;
	int position = 1;
	int best_position;
	int choice;
	Bit64 chromosome;
	Bit64 chromosome_mutated;
	double x, y, mx, my;
	double Best_Fit;

	chromosome = input & 0xfffff;

	for (int i = 0; i < EVO; i++) {

		
		x = chromosome & 0x3ff;			// Original x
		y = (chromosome >> 10) & 0x3ff;	// Original y

		// Mutate X:
		if (randCoinToss()!=0) {

			// X + 1
			if (randCoinToss()!=0) {
				mx = x + 1;
				my = y;
			}

			// X - 1
			else {
				mx = x - 1;
				my = y;
			}
		}

		// Mutate Y:
		else {
			
			// Y + 1
			if (randCoinToss()!=0) {
				mx = x;
				my = y + 1;
			}

			// Y - 1
			else {
				mx = x;
				my = y - 1;
			}
		}

		// Combine new X and new Y to be new chromosome
		chromosome_mutated = ( ((Bit64)my << 10) & (0x3ff << 10) ) | ((Bit64)mx & 0x3ff);
		position++;

		if ( Fitness(Scale_X(mx), Scale_Y(my)) > Fitness(Scale_X(x),Scale_Y(y)) ) {
			Best_Fit = Fitness(Scale_X(mx), Scale_Y(my));
			chromosome = chromosome_mutated;
			count++;
			best_position = position;
		}

	}
	double finalx, finaly;
	finalx = chromosome & 0x3ff;
	finaly = (chromosome >> 10) & 0x3ff;

	// The number of fitness evaluations when it found the best fitness it found in the number of evaluations allowed. •
	cout << best_position  << " "
	// The number of improving moves made.
	     << count << " "
	// The x and y that gave that fitness.
		 << Scale_X(finalx) << " " << Scale_Y(finaly) << " "
	// The best fitness found.
	     << Best_Fit << endl;

	return Best_Fit;
}

int main (int argc, char* argv[]) {

	char opt1;
	char opt2;
	opt1 = argv[1][0];
	opt2 = argv[2][0];
	Bit64 input;
	double x, y;
	float a, b; 
	initRand();
	double fitness;				// Original fitness
	double total_fitness = 0;
	double total_x;
	double total_y;

for (int i = 0 ; i < 1000; i++) {

	input = randULL(); 			// randomly 64 bit int
	x = input & 0x3ff;			// Original x
	y = (input >> 10) & 0x3ff;	// Original y
	fitness = Fitness(Scale_X(x),Scale_Y(y));
	


	//cout << "Original X: " << x << endl;
	//cout << "Scaled X: " << Scale_X(x) << endl;
	//cout << "Original Y: " << y << endl;
	//cout << "Scaled Y: " << Scale_Y(y) << endl;
	//cout << "Original Fitness: " << fitness << endl;

	if (argc != 3) {
		cout << "Error! need 2 arguments for this program. " << endl;
		return 0;
	}

	else {
		switch (opt1) {
			case '0': // Plain Mapping

				switch (opt2) {
					case '0':
						total_fitness = total_fitness + RandomJump_Binary(input, fitness);
					break;

					case '1':
						total_fitness = total_fitness + BitFlip_Binary(input, fitness);
					break;

					case '2':
						total_fitness = total_fitness + Single_Dimension_Binary(input, fitness);
					break;

					default:
						cout << "Error option." << endl;
						return -1;
					break;

				}


			break;

			
			case '1': // Gray Code mapping
			

				switch (opt2) {
					case '0':
						total_fitness = total_fitness + RandomJump_Gray(input, fitness);
					break;

					case '1':
						total_fitness = total_fitness + BitFlip_Gray(input, fitness);
					break;

					case '2':
						total_fitness = total_fitness + Single_Dimension_Gray(input, fitness);
					break;

					default:
						cout << "Error option." << endl;
						return -1;
					break;

				}
		
			break;


			default:
				cout << "Error option." << endl;
				return -1;
		
			break;



		}
	}

}
	//cout << "Total_Fitness: " << total_fitness << endl;
	//cout << "Avg_Fitness: " << total_fitness/1000 << endl;

	return 0;

}