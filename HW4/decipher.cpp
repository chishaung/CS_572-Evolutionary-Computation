#include <iostream> 
#include <utility>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <cctype>
#include <algorithm>
#include <iomanip>
#include <math.h>
#include "rand.h"
#include <string.h>
#include <utility>


//#define POP_SIZE 50
#define MUTATION_RATE 0.95
//#define Generation 600
#define XOVER_RATE 18
// 0 - off, 1 - on
#define SHOW_FIT 0
#define SHOW_TIME 0
#define SHOW_ANSWER 0

using namespace std;

// These Global varaiables are determind in the READ_FILE
// And will not modify anymore in the whole program.
char *clear_chips = new char[4000];
char *ALP = new char[26];
double freq_E[26][26];
int length;
int POP_SIZE;
int Generation;



void Print_Key(string key) {
cout << key << endl;
}

// For Debugging 
void Print_Table(double freq_D[][26], double freq_E[][26]) {

	cout << "Decoded Frequency Table: " << endl;
    for (int i = 0; i < 26; i++) {
    	for (int j = 0; j < 26; j++) {
    		cout << setw(5) << freq_D[i][j];
    	}
    	cout << endl;
    }

    cout << "English Frequency Table: " << endl;
    for (int i = 0; i < 26; i++) {
    	for (int j = 0; j < 26; j++) {
    		cout << setw(5) << freq_E[i][j];
    	}
    	cout << endl;
    }

}

// This is the Shuffle Cards algorithm, this returns a


void shuffle(char *a, int size)
{
    for (int i=0; i<size; i++) {
        a[i] = i + 65;
    }

    for (int i=size-1; i>0; i--) {
        char tmp, j;

        j = randMod(i+1);
        tmp = a[i];
        a[i] = a[j];
        a[j] = tmp;
    }
    a[27] = '\0';

}


// This function only execute once, and gives necessary data
// clear_chips -> The encoded text
// length 	   -> The length of the encoded text
// freq_E      -> The frequency table of the normal English language
void ReadFile(char *&clear_chips) {

	char c;
	int i = 0;
	char * pch1;
	char * pch2;
	double Sum = 0;

	// Here to read Encoded Text and its length
	while (cin.get(c)) {
		
		if (c != ' ' && c != '\n') {
			clear_chips[i] = c;
			i++;
			length++;
			//cout << c;
		}
	}

	// Initialize English_Frequency_Table
	for (int p = 0; p < 26; p++) {
		for (int q = 0; q < 26; q++) {
			freq_E[p][q] = 0;
		}
	}

	// Open File
	ifstream fin("freq1.txt"); 
    const int LINE_LENGTH = 20; 
    char str[LINE_LENGTH];  

    // Fill the English_Frequency_Table
    while( fin.getline(str,LINE_LENGTH) )
    {    
        pch1 = strtok(str," ");
        pch2 = strtok(NULL," ");
        freq_E[pch1[0]-97][pch1[1]-97] = atoi(pch2);
        Sum = Sum + atoi(pch2);

    }



    for (int i = 0; i < 26; i++) {
    	for (int j = 0; j < 26; j++) {
    		freq_E[i][j] = freq_E[i][j] / Sum;
    		// Create ALP
    		ALP[i] = 65 + i;
    		//cout << setw(5) << freq_E[i][j];
    	}
    	//cout << endl;
    }
//cout << "Length: " << length << endl;
    //cout << "SUM: " << Sum << endl;

}

void pmx(string a, string b, char *out, int k, int size) 
{
    bool pick[size];   // which elements to copy from B
    int locA[size];    // locA[x] is where is x in A
    int locB[size];    // locB[x] is where is x in B
    const double prob = (double)k/size;

    // copy random subset of B
    for (int i = 0; i < size; i++) {
        // choose 
        if (choose(prob)) {
            pick[i] = true;        // select what to copy from B
            out[i] = b[i];         // copy from B
        }
        else {
            pick[i] = false;       
            out[i] = '@';           // if not copied from B then mark -1
        }

        // make table as a side effect
        locA[int(a[i]-65)] = locB[int(b[i]-65)] = i;   // set up location lookup for A and B
    }

    //cout << "S1: " << out << endl;
    // ASSERT: out[i] is either from B or -1.  pick[i]=T if B



    // copy the lost elements into the duplicate elements
    for (int i = 0; i < size; i++) {
        // for each location in the child where an element from B was put 
        // was the element from A that could have been put there also
        if (pick[i] && !pick[locB[int(a[i]-65)]]) {
            // a[i] was an element that was not picked so we need to put it
            // somewhere
            int loc;

            // find duplicate
            loc = i;
            do {
                loc = locA[int(b[loc]-65)];
            }
            while (out[loc] != '@');

            out[loc] = a[i];  // copy lost element over duplicate
        }
    }

    // copy from A anything not already copied
    for (int i = 0; i < size; i++) {
        if (out[i] == '@') out[i] = a[i];
    }
    out[27] = '\0';
}       
 
void pmm(char *key) {
	//char temp = '@';
	int index1, index2, index3, index4, index5, index6;
	char ch1, ch2, ch3;
	vector<char > temp;
	randMod2(26, index1, index2);
	do {
		index3 = randMod(26);
	} while (index3 == index2 || index3 == index1);

	ch1 = key[index1];
	ch2 = key[index2];
	ch3 = key[index3];
	temp.push_back(ch1);
	temp.push_back(ch2);
	temp.push_back(ch3);

	randMod2(3, index4, index5);
	do {
		index6 = randMod(3);
	} while (index6 == index5 || index6 == index4);



	key[index1] = temp[index4];
	key[index2] = temp[index5];
	key[index3] = temp[index6];

	key[27] = '\0';
	

}

double Fitness(string key2) {

	char key[27];
	strcpy(key, key2.c_str());
	double fitness = 0;
	char decoded_chips[length];
	double freq_D[26][26];
	int SUM = 0;

		// Initializing Freq_D
		for (int i = 0; i < 26; i++) {
    		for (int j = 0; j < 26; j++) {
    		freq_D[i][j] = 0;
    		}
    	}

		// Decoding Text
		for (int i = 0; i < length; i++) {

			int x = distance(key, find(key, key + 26, clear_chips[i]-32));
			decoded_chips[i] = ALP[x];

		}

		
		

    	// Filling Freq_D
    	for (int i = 0; i < length-1; i++) {
    		freq_D[(int)decoded_chips[i]-65][(int)decoded_chips[i+1]-65]++;
    		SUM++;
    	}


    	// So now I have Freq_E, Freq_D for the keys[k]
    	// Time to calculate and store the fitenss
    	for (int i = 0; i < 26; i++) {
    		for (int j = 0; j < 26; j++) {
    			if (freq_D[i][j]!=0 && freq_E[i][j]!=0) {
	   				freq_D[i][j] = freq_D[i][j] / SUM;

	   				if (freq_E[i][j] < 0.001) {
	   					fitness = fitness + 0.5 * (sqrt  (freq_E[i][j] * freq_D[i][j]) );	

	   				}

	   				else if (freq_E[i][j] > 0.008) {
	   					fitness = fitness + 1.5 * (sqrt  (freq_E[i][j] * freq_D[i][j]) );
	   					//cout << "2" << endl;	
	   				}

	   				else 
    				fitness = fitness + (sqrt  (freq_E[i][j] * freq_D[i][j]) );
    			}
    		}
    	}


    	return fitness;

}



int FindMaxIndex( pair<string, double> *vpa, int start, int end) {
	int best = start;
	for (int i = start+1; i < end; i++) {
		if (vpa[i].second > vpa[best].second)
			best = i;
	}

	return best;
}


int FindMaxIndex_Pool( pair<string, double> *vpa, int start, int end) {
	int best = start;
	for (int i = start+1; i < end; i++) {
		if (vpa[i].second > vpa[best].second)
			best = i;
	}

	return best;
}

void swap(pair<string, double> *vpa, int a, int b) {
	pair<string, double> temp;
	temp = vpa[a];
	vpa[a] = vpa[b];
	vpa[b] = temp;
}


int main (int argc, char *argv[]) {

	/********************
   	 Varaiable Declration
	 ********************/



   	

   	string Parent1, Parent2, New_Parent1, New_Parent2;
   	string Child1, Child2;
	char cards[27];
	char out[27];
	int arr1[27];
	int arr2[27];
	int int_out[27];
	int select_1;
	int select_2;
	int select_3;
	int Min_index;
	int Max_index;
	double fitness;
	double Parent1_Fit, Parent2_Fit, New_Parent1_Fit, New_Parent2_Fit;

	clock_t begin, end;
	double time_spent;

	begin = clock();


	/*****************************
	 Initializing Random Operators
	 *****************************/
	srand(time(NULL));
	initRand();



	/****************
	 GA Starting HERE
	 ****************/

	ReadFile(clear_chips);
	if (length <= 387) {
   	 	#define POP_SIZE 200
   	 	Generation = 2000;
   	 }

   	 else if (length >= 388 && length <= 714) {
   	 	#define POP_SIZE 120
   	 	Generation = 1000;
   	 }

   	 else if (length == 715) {
   	 	#define POP_SIZE 90
   	 	Generation = 1000;	
   	 }

   	 else if (length >= 716 && length <= 945) {
   	 	#define POP_SIZE 50
   	 	Generation = 700;
   	 }

   	 else if (length >= 946 && length <= 1182) {
   	 	#define POP_SIZE 50
   	 	Generation = 700;
   	 }

   	 else if (length >= 1183 && length <= 1830) {
   	 	#define POP_SIZE 30
   	 	Generation = 500;
   	 }

   	 else if (length >= 1831) {
   	 	#define POP_SIZE 20
   	 	Generation = 300;
   	 }

   	pair<string, double> vpa[POP_SIZE];
   	pair<string, double> vpa_next[POP_SIZE];
   	pair<string, double> tour_pool[3];


	double Fit;

	// Initialize Population: - test ok
	for (int i = 0; i < POP_SIZE; i++) {
		shuffle(cards, 26);
		Fit = Fitness(string(cards));
		vpa[i] = make_pair(string(cards), Fit);

		
		//cout << vpa[i].first << " = " << vpa[i].second << endl;
	}





	for (int z = 0; z < Generation; z++) {

		// Find 2 Elites, put into next generation 

		
		Max_index = FindMaxIndex(vpa, 0, POP_SIZE);
		vpa_next[0] = make_pair(vpa[Max_index].first, vpa[Max_index].second);
		//cout << vpa_next[0].first << endl;
		swap(vpa, Max_index, POP_SIZE-1);
		Max_index = FindMaxIndex(vpa, 0, POP_SIZE-1);
		vpa_next[1] = make_pair(vpa[Max_index].first, vpa[Max_index].second);
		//cout << vpa_next[1].first << endl;

		
		for (int b = 2; b < POP_SIZE; b++) {

			// Select 1st Parent
			randMod2(POP_SIZE, select_1, select_2);
			do {
				select_3 = randMod(POP_SIZE);
			} while (select_3 == select_2 || select_3 == select_1);

			tour_pool[0] = vpa[select_1];
			tour_pool[1] = vpa[select_2];
			tour_pool[2] = vpa[select_3];
			Max_index = FindMaxIndex_Pool(tour_pool, 0, 3);
			Parent1 = tour_pool[Max_index].first;
			//Parent1_Fit = tour_pool[Max_index].second;

			

			// Select 2nd Parent
			randMod2(POP_SIZE, select_1, select_2);
			do {
				select_3 = randMod(POP_SIZE);
			} while (select_3 == select_2 || select_3 == select_1);

			tour_pool[0] = vpa[select_1];
			tour_pool[1] = vpa[select_2];
			tour_pool[2] = vpa[select_3];
			Max_index = FindMaxIndex_Pool(tour_pool, 0, 3);
			Parent2 = tour_pool[Max_index].first;
			//Parent2_Fit = tour_pool[Max_index].second;

		



			// Xover + Mutation = New Chromosome!

			// Get Child
    		pmx(Parent1, Parent2, out, XOVER_RATE, 26);
			out[26] = '\0';


			// PMM - Permutation Based Mutation, out is the Child now.
    		if (choose(MUTATION_RATE)){
	    		pmm(out);
	    	}
	    	Child1 = string(out);
	    	Fit = Fitness(Child1);
	    	vpa_next[b] = make_pair(Child1, Fit);

	    }


	    for (int i = 0; i < POP_SIZE; i++) {
			vpa[i] = vpa_next[i];
		}


		if (SHOW_FIT == 1) {
			Max_index = FindMaxIndex(vpa, 0, POP_SIZE);
			cout << vpa[Max_index].second << endl;
		}
	
	} // End Generation 
	//for (int i = 0; i < POP_SIZE; i++) {
	//	cout << "[" << i << "]: " << vpa[i].first << " = " << vpa[i].second << endl;
	//}
	cout << "** wang ";
	for (int i = 0; i < 26; i++) {
		cout << char(vpa[Max_index].first[i]+32);
	}
	cout << endl;

	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

	if (SHOW_ANSWER == 1){
		if (length == 1209) {
			cout << "1209" << endl;
			cout << "** answ osjpedqyvkrtznbhcgalmuifxw" << endl;
		}

		else if (length == 715) {
			cout << "** answ kxtecgusjqidzvbywrhplfnmoa" << endl;
			cout << "715" << endl;
		}

		else if (length == 250) {
			cout << "** answ uehnlrxjwipmobfkcyvsgztdqa" << endl;
			cout << "250" << endl;
		}

		else if (length == 369) 
		cout << "** answ axoievjhyfmlutrgnbqsckdwpz" << endl;

		else if (length == 603)
		cout << "** answ ukjhsogdlbatfqepxzmwvrniyc" << endl;

		else if (length == 237)
		cout << "** answ ewltkoudpicmnagbvfqxsryhjz" << endl;

		else if (length == 158)
		cout << "** answ ewltkoudpicmnagbvfqxsryhjz" << endl;

		else if (length == 115)
		cout << "** answ xskfagolpumhbwqzvijrncteyd" << endl;

	}
	if (SHOW_TIME == 1) 
		cout << "Time Spent: " << time_spent << endl;

}