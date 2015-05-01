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
#include "func.h"

using namespace std;



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
    a[size] = '\0';

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
		}
	}

	// Initialize English_Frequency_Table
	for (int p = 0; p < 26; p++) {
		for (int q = 0; q < 26; q++) {
			freq_E[p][q] = 0;
		}
	}

	// Open File
	ifstream fin("freq.txt"); 
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

    //cout << "=========" << Sum << endl;

    for (int i = 0; i < 26; i++) {
    	for (int j = 0; j < 26; j++) {
    		freq_E[i][j] = freq_E[i][j] / Sum;
    		//cout << setw(5) << freq_E[i][j];
    	}
    	//cout << endl;
    }



	// Create ALP
	for (int i = 0; i < 26; i++) {
		ALP[i] = 65 + i;
	}

}

void pmx(int *a, int *b, int *out, int k, int size) 
{
    bool pick[size];   // which elements to copy from B
    int locA[size];    // locA[x] is where is x in A
    int locB[size];    // locB[x] is where is x in B
    const double prob = (double)k/size;

    // copy random subset of B
    for (int i=0; i<size; i++) {
        // choose 
        if (choose(prob)) {
            pick[i] = true;        // select what to copy from B
            out[i] = b[i];         // copy from B
        }
        else {
            pick[i] = false;       
            out[i] = -1;           // if not copied from B then mark -1
        }

        // make table as a side effect
        locA[a[i]] = locB[b[i]] = i;   // set up location lookup for A and B
    }
    // ASSERT: out[i] is either from B or -1.  pick[i]=T if B



    // copy the lost elements into the duplicate elements
    for (int i=0; i<size; i++) {
        // for each location in the child where an element from B was put 
        // was the element from A that could have been put there also
        if (pick[i] && !pick[locB[a[i]]]) {
            // a[i] was an element that was not picked so we need to put it
            // somewhere
            int loc;

            // find duplicate
            loc = i;
            do {
                loc = locA[b[loc]];
            }
            while (out[loc] != -1);

            out[loc] = a[i];  // copy lost element over duplicate
        }
    }

    // copy from A anything not already copied
    for (int i=0; i<size; i++) {
        if (out[i] == -1) out[i] = a[i];
    }
}       
 
void pmm(char *key) {
	//char temp = '@';
	int index1, index2, index3;
	char ch1, ch2, ch3;
	randMod2(26, index1, index2);
	do {
		index3 = randMod(26);
	} while (index3 == index2 && index3 == index2);

	ch1 = key[index1];
	ch2 = key[index2];
	ch3 = key[index3];
	key[index1] = ch3;
	key[index2] = ch1;
	key[index3] = ch2;
	

}

double Fitness(string key2) {

	char key[27];
	strcpy(key, key2.c_str());
	double fitness = 0;
	char decoded_chips[length];
	double freq_D[26][26];
	int SUM = 0;


		// Decoding Text
		for (int i = 0; i < length; i++) {

			int x = distance(key, find(key, key + 26, clear_chips[i]-32));
			decoded_chips[i] = ALP[x];

		}

		// Initializing Freq_D
		for (int i = 0; i < 26; i++) {
    		for (int j = 0; j < 26; j++) {
    		freq_D[i][j] = 0;
    		}
    	}

    	// Filling Freq_D
    	for (int i = 0; i < length-1; i++) {
    		freq_D[(int)decoded_chips[i+1]-65][(int)decoded_chips[i]-65]++;
    		SUM++;
    	}


    	// Scale
    	for (int i = 0; i < 26; i++) {
    		for (int j = 0; j < 26; j++) {
    		freq_D[i][j] = freq_D[i][j] / SUM;
    		}
    	}

    	// So now I have Freq_E, Freq_D for the keys[k]
    	// Time to calculate and store the fitenss
    	for (int i = 0; i < 26; i++) {
    		for (int j = 0; j < 26; j++) {
   
    			fitness = fitness + (sqrt  (freq_E[i][j] * freq_D[i][j]) );
    		}
    	}


    	return fitness;

}

int FindMinIndex(vector<pair<string, double> > vp, int start, int end) {
	int best = start;
	for (int i = start+1; i < end; i++) {
		if (vp[i].second < vp[best].second)
			best = i;
	}

	return best;
}
