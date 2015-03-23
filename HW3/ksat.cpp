#include <iostream>
#include <vector>
#include <stdlib.h>
#include <bitset>
#include <math.h>
#include <string.h>
#include "bitHelpers.h"
#include "rand.h"

using namespace std;


void Mutation( unsigned long long int &Child1, 
			   unsigned long long int &Child2,
			   int n
			   ) {

	unsigned long long int x, y;
	x = (randULL() & randULL() & randULL() & randULL());
	y = (randULL() & randULL() & randULL() & randULL());

	//cout << "X: " << (bitset<64>) x << endl;

	Child1 ^= x;
	Child2 ^= y;
}

void Xover( unsigned long long int Parent1, 
		    unsigned long long int Parent2, 
		    unsigned long long int &Child1, 
			unsigned long long int &Child2,
			float Xover_Prob, int n
			) {
	// Do Xover
	unsigned long long int part;

	// if true, do Xover
	if (choose((double)Xover_Prob)) {

		// Uniform Xover
		part = randULL();
		Child1 = (part & Parent1) | (~part & Parent2);
		Child2 = (~part & Parent1) | (part & Parent2);
	}

	else {
		Child1 = Parent1;
		Child2 = Parent2;
	}



}

void Best_Two(int &b1, int &b2, int &worst, vector<int> Fitness1) {
	
	int one; 
	int two;
	int bad;
	int index1 = 0;
	int index2 = 0;
	int index3 = 0;
	one = -1000;
	two = -1000;
	bad = 1000000;
	

	for (int i = 0; i < Fitness1.size(); i++ ) {
		if (Fitness1[i] > one) {
			one = Fitness1[i];
			index1 = i;
		}
		if (Fitness1[i] < bad) {
			bad = Fitness1[i];
			index3 = i;
		}
	}


	Fitness1[index1] = 0;
	for (int i = 0; i < Fitness1.size(); i++ ) {
		if (Fitness1[i] > two) {
			two = Fitness1[i];
			index2 = i;
		}
	}

	b1 = index1;
	b2 = index2;
	worst = index3;


}
long long int Bit_Select(int n) {

	long long int result; 
	//result = 0ULL;
	result = (result << n)-1;

	return result;
}


void Fitness(int n, 
	vector<unsigned long long int> IN_1, 
	vector<unsigned long long int> IN_2, 
	vector<unsigned long long int> population1,  
	vector<int> &Fitness1) {

	int fit = 0;
	unsigned long long int length, answer, Temp_IN_1; 
	length = Bit_Select(n);



	for (int j = 0; j < population1.size(); j++) {
		
		//population1[j] = population1[j] & length;			// filter
		
		for (int i = 0; i < IN_1.size(); i++) {
			answer = population1[j];
			IN_1[i] = IN_1[i] & length;							// filter 
			IN_2[i] = IN_2[i] & length;							// filter 

			answer = answer ^ IN_2[i];

			Temp_IN_1 = IN_1[i] & answer;

			if (Temp_IN_1 > 0) {
				fit++;
			}	
		}
		Fitness1.push_back(fit);
		fit = 0;
	}

}

long long int convert(char* str) {

	char *ptr;
	long long int result; 
	long parsed = strtol (str, &ptr, 2);
	result = parsed; 

	return result;
}



int main(int argc, char* argv[]) {

	int Generation;
	int Pop_Size;
	float Xover_Prob;
	vector<unsigned long long int> IN_1, IN_2;
	vector<unsigned long long int> population1, population2;
	vector<int> Fitness1, Fitness2;
	unsigned long long int chromosome1, chromosome2, chromosome3;

	int n, k, c;
	char  str[200];
	char * pch;
	unsigned long long int variable, condition;

	int Select_Index_1;
	int Select_Index_2;
	int Select_Index_3;
	int b1, b2, worst;
	unsigned long long int Child1, Child2, Parent1, Parent2;

	vector<int> Tour_Fit;
	vector<unsigned long long int> Tour_Pool_chrom;
	
	initRand();





	
	// ******************
	// Getting Parameters
	// ******************
	if (argc != 4) {
		cout << "Error! need 3 arguments for this program. " << endl;
		return -1;
	}

	else {
		Generation = atoi(argv[1]);
		Pop_Size = atoi(argv[2]);
		Xover_Prob = (float)atof(argv[3]);
	}






	// ***************
    // Getting N, K, C
    // ***************
	cin.get(str, 200);
	//cout << "Str1: " << str << endl;
	cin.get();

    pch = strtok (str," ,.-  ");
    //cout << pch << endl;
    n = atoi(pch);
    pch = strtok (NULL," ,.-  ");
    //cout << pch << endl;
    k = atoi(pch);
    pch = strtok (NULL," ,.-  ");
    //cout << pch << endl;
    c = atoi(pch);






    // *************************************************
    // Getting 2 Inputs and store into the IN_1 and IN_2
    // *************************************************
    for (int i = 0; i < c; i++) {

    	cin.get(str, 200);
    	pch = strtok(str," ,.-  \n");
    	variable = convert(pch);
    	IN_1.push_back(variable);
    	pch = strtok(NULL, " ,.-  \n");
    	condition = convert(pch);
    	IN_2.push_back(condition);

		cin.get();
    }




	// ***************
    // Algorithm Start
    // ***************



	// Generating populations
	for (int i = 0; i < Pop_Size; i++) {
		population1.push_back(randULL());
		population1[i] = population1[i] & Bit_Select(n);
	}

	int ctl = 0;
	// **************************
	// * Start to Do Generation *
	// **************************

	for (int k = 0; k < Generation; k++) {
		Fitness1.clear();

		// Calculating each individuals' Fitness
		Fitness(n, IN_1, IN_2, population1, Fitness1);

		Best_Two(b1, b2, worst, Fitness1);


		// Push 2 Elites into next generation
		population2.push_back(population1[b1]);
		population2.push_back(population1[b2]);



		// Randomly Select 3 individuals, and send best 1 into the Xover Pool
		randMod2(Pop_Size, Select_Index_1, Select_Index_2);
		do {
			Select_Index_3 = randMod(Pop_Size);
		} while (Select_Index_3 == Select_Index_2 && Select_Index_3 == Select_Index_2);


		// Tournament Pool
		Tour_Fit.push_back(Fitness1[Select_Index_1]);
		Tour_Fit.push_back(Fitness1[Select_Index_2]);
		Tour_Fit.push_back(Fitness1[Select_Index_3]);
		Tour_Pool_chrom.push_back(population1[Select_Index_1]);
		Tour_Pool_chrom.push_back(population1[Select_Index_2]);
		Tour_Pool_chrom.push_back(population1[Select_Index_3]);

		Best_Two(b1, b2, worst, Tour_Fit);
		Parent1 = population1[b1];
		Tour_Fit.clear();
		Tour_Pool_chrom.clear();

		// Randomly Select 3 individuals, and send best 1 into the Xover Pool
		randMod2(Pop_Size, Select_Index_1, Select_Index_2);
		do {
			Select_Index_3 = randMod(Pop_Size);
		} while (Select_Index_3 == Select_Index_2 && Select_Index_3 == Select_Index_2);


		// Tournament Pool
		Tour_Fit.push_back(Fitness1[Select_Index_1]);
		Tour_Fit.push_back(Fitness1[Select_Index_2]);
		Tour_Fit.push_back(Fitness1[Select_Index_3]);
		Tour_Pool_chrom.push_back(population1[Select_Index_1]);
		Tour_Pool_chrom.push_back(population1[Select_Index_2]);
		Tour_Pool_chrom.push_back(population1[Select_Index_3]);

		Best_Two(b1, b2, worst, Tour_Fit);
		Parent2 = population1[b1];
		Tour_Fit.clear();
		Tour_Pool_chrom.clear();




		// Xover Parents 
		Xover(Parent1, Parent2, Child1, Child2, Xover_Prob, n);
	
		// Mutate Child
		Mutation(Child1, Child2, n);

		// Store Children into next population
		population2.push_back(Child1);
		population2.push_back(Child2);

		// Fill up next population
		for(int i = 0; i < Pop_Size-4; i++) {
			population2.push_back(randULL());
		}

		// Copy and Clear original population
		population1.clear();
		population1 = population2;
		population2.clear();
		Tour_Fit.clear();
		Tour_Pool_chrom.clear();

	} // End of Generation 
	
	int ctrl = 0;

	for (int i = 0; i < population1.size(); i++) {
		if (Fitness1[i] == c) {
			cout << c << " " << (bitset<64>) population1[i] << endl;
			cout << "Satisfiable" << endl;
			break;
		}
		else {
			ctrl = 1;
		}
	}

	if (ctrl == 1) {
		cout << Fitness1[0] << " " << (bitset<64>) population1[0] << endl;
			cout << "Could not find a solution" << endl;
	}

	

	return 0;
}