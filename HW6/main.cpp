#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <vector>
#include "tree.h"
#include "opList.h"

#define Generation 500
// Must be even number..
#define POP_SIZE 40
#define DEPTH 4
#define XOVER_PROB 0.9
// Will Mutate 0 ~ m Ops
#define MAX_MUTATE_NODE 1

using namespace std;
int File_Length;

unsigned long long int addrToNum_(void *addr)
{
    return ((unsigned long long int)addr) & 0xffff;
}


vector<pair<long double, long double> > ReadFile() {

	vector<pair<long double, long double> > in;
	int LINE_LENGTH = 100;
	char str[LINE_LENGTH]; 
	char * pch1;
	char * pch2;

	cin.getline(str, LINE_LENGTH);
	File_Length = atoi(str);

	while( cin.getline(str, LINE_LENGTH) )
    {    
        pch1 = strtok(str," ");
        pch2 = strtok(NULL," ");
        //cout << stold(pch1) << " = " << stold(pch2) << endl;
        in.push_back( make_pair(stold(pch1), stold(pch2)) );

    }


    return in;
}


void Setup() {
    initRand();
    initOps(10);
    addOpOrTerm((char *)"+", 2, addOp);
    addOpOrTerm((char *)"-", 2, subOp);
    addOpOrTerm((char *)"*", 2, mulOp);
    addOpOrTerm((char *)"/", 2, divOp);
    addOpOrTerm((char *)"sin", 1, sinOp);
    addOpOrTerm((char *)"x", 0, xOp);
    addOpOrTerm((char *)NULL, 0, constOp);  // WARNING: null name means it is a constant!!!!
}

long double Fitness(Tree *t, vector<pair<long double, long double> > Input) {
	long double fit = 0;

	for (int i = 0; i < File_Length; i++) {
		setX(Input[i].first);
		fit = fit + pow((Input[i].second - t->eval()), 2);
	}

	return fit;
}



void Mutation(Tree* Parent1, Tree* Parent2) {


}

void Xover(Tree* Parent1, Tree* Parent2) {

	Tree *s1, *p1;
	Tree *s2, *p2;
	Side side1, side2;


	s1 = Parent1->pickNode();
	p1 = s1->up();
	side1 = s1->remove();
	s2 = Parent2->pickNode();
	p2 = s2->up();
	side2 = s2->remove();

	p1->join(side1, s2);
	p2->join(side2, s1);


	Parent1 -> check();
	Parent2 -> check();


}

int FindMinIndex( pair<Tree*, long double> *vpa, int start, int end) {
	int best = start;
	for (int i = start+1; i < end; i++) {
		if (vpa[i].second < vpa[best].second)
			best = i;
	}

	return best;
}

int FindMinIndex_Pool( pair<Tree*, long double> *vpa, int start, int end) {
	int best = start;
	for (int i = start+1; i < end; i++) {
		if (vpa[i].second < vpa[best].second)
			best = i;
	}

	return best;
}


void swap(pair<Tree*, long double> *vpa, int a, int b) {
	pair<Tree*, double> temp;
	temp = vpa[a];
	vpa[a] = vpa[b];
	vpa[b] = temp;
}




int main() {

	int Method;
	vector<pair<long double, long double> > Input;
	pair<Tree*, long double> Curr_Gen[POP_SIZE];
	pair<Tree*, long double> Next_Gen[POP_SIZE];
	pair<Tree*, long double> tour_pool[3];
	Tree *Parent1, *Parent2;
	Tree *t;
	long double eval;
	long double Fit;
	int Max_index;


	Setup();
	Input = ReadFile(); 


	// Generating First Generation Population and Fill its Fitness
	for (int i = 0; i < POP_SIZE; i++) {
		t = Tree::getRandTree(DEPTH);
		Fit = Fitness(t, Input);
		Curr_Gen[i] = make_pair(t, Fit);
		
		t->remove();

	}

	// Loop Until Generation times or find a good solution
	for (int Gen = 0; Gen < Generation; Gen++) {

		// 2 Elite
		
		int select_1;
		int select_2;
		int select_3;

		Max_index = FindMinIndex(Curr_Gen, 0, POP_SIZE);
		Next_Gen[0] = make_pair(Curr_Gen[Max_index].first, Curr_Gen[Max_index].second);
		swap(Curr_Gen, Max_index, POP_SIZE-1);
		Max_index = FindMinIndex(Curr_Gen, 0, POP_SIZE-1);
		Next_Gen[1] = make_pair(Curr_Gen[Max_index].first, Curr_Gen[Max_index].second);


			int POP = 2;
			// Algorithm Start Here:
			while (POP < POP_SIZE) {


				// Select 1st Parent
				randMod2(POP_SIZE, select_1, select_2);
				do {
					select_3 = randMod(POP_SIZE);
				} while (select_3 == select_2 || select_3 == select_1);

				tour_pool[0] = Curr_Gen[select_1];
				tour_pool[1] = Curr_Gen[select_2];
				tour_pool[2] = Curr_Gen[select_3];
				Max_index = FindMinIndex_Pool(tour_pool, 0, 3);
				Parent1 = tour_pool[Max_index].first->copy();

				
			

				// Select 2nd Parent
				randMod2(POP_SIZE, select_1, select_2);
				do {
					select_3 = randMod(POP_SIZE);
				} while (select_3 == select_2 || select_3 == select_1);

				tour_pool[0] = Curr_Gen[select_1];
				tour_pool[1] = Curr_Gen[select_2];
				tour_pool[2] = Curr_Gen[select_3];
				Max_index = FindMinIndex_Pool(tour_pool, 0, 3);
				Parent2 = tour_pool[Max_index].first->copy();


				// If true, do Xover. Or don't do anything.
				if (choose((double)XOVER_PROB)) {
					Xover(Parent1, Parent2);
				}
				
				//Mutation(Parent1, Parent2);


				Fit = Fitness(Parent1, Input);
				Next_Gen[POP] = make_pair(Parent1, Fit);
				Fit = Fitness(Parent2, Input);
				Next_Gen[POP+1] = make_pair(Parent2, Fit);

				POP += 2;
				

			} // End while 

			for (int i = 0; i < POP_SIZE; i++) {

			Curr_Gen[i] = Next_Gen[i];
		}

		//Max_index = FindMinIndex(Curr_Gen, 0, POP_SIZE);
		//cout << "Best Fit: " << Curr_Gen[Max_index].second << endl;
	} // End of Generation

	Max_index = FindMinIndex(Curr_Gen, 0, POP_SIZE);
	cout << "Best Fit: " << Curr_Gen[Max_index].second << endl;


	return 0;
}
