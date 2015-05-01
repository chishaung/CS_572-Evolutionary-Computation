#include <stdio.h>
#include "rand.h"

// EXAMPLE OF A UNIFORM PMX CROSSOVER OPERATOR
//
// An example of a Uniform PMX Crossover operator by Robert
// Heckendorn (University of Idaho).   This will work like
// the classic PMX operator except that it is not restricted
// to the case that the copied elements are adjacent.   It is
// more like UX than 2 point crossover but for permuations.
//  
// copy selected A's into out (child)
// 
// set 1: things in B selected that are not in A selected are kicked
// out and must go new place 
// 
// set 2: things in A selected that are not in B selected are copies
// move set 1 to set 2.
// 
// Do a uniform pmx xover:
//
// Example:
//   B 7  3  1  2  5  0  4  6 
//   A 7  2  5  0  3  4  1  6 
//PICK             *  *  *  * 
// OUT 7  2  3  1  5  0  4  6 
//
// set 1: 8 2
// set 2: 4 7
//     
// Example 2:
//     
//   B 6  4  0  8  5  2  1  7  3 
//   A 5  4  3  2  6  8  0  1  7 
//PICK    *  *        *     *    
// OUT 5  4  0  8  6  2  3  7  1 


// make up a random permuation of size size
void shuffle(int *a, int size)
{
    for (int i=0; i<size; i++) {
        a[i] = i;
    }

    for (int i=size-1; i>0; i--) {
        int tmp, j;

        j = randMod(i+1);
        tmp = a[i];
        a[i] = a[j];
        a[j] = tmp;
    }
}


// print a permuation
void print(char *label, int *a, int size)
{
    printf("%4s", label);
    for (int i=0; i<size; i++) printf("%2d ", a[i]);
    printf("\n");
}



// is it a permutation?
bool isPermP(int *a, int size)
{
    for (int i=0; i<size; i++) {
        for (int j=i+1; j<size; j++) {
            if (a[i] == a[j]) {
                printf("ERROR: positions %d and %d are same\n", i, j);
                return false;
            }
        }
    }
    return true;
}
        

// uniform pmx xover
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

    // print for to use as example
    printf("%4s", "PICK");
    for (int i=0; i<size; i++) printf("%2s ", (pick[i] ? "*" : " "));
    printf("\n");

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
            

int main()
{
    initRand();
    const int size=26;
    int a[size], b[size], out[size];
    
    // make up some random permuations
    shuffle(a, size);
    shuffle(b, size);

    for (int i=0; i<1; i++) {
        print((char *)"B", b, size);
        print((char *)"A", a, size);
        pmx(a, b, out, 4, size);
        print((char *)"OUT", out, size);
        printf("\n");
        if (!isPermP(out, size)) {
            printf("ERROR: NOT PERM: ");
            print((char *)"", out, size);
        }
    }
     

    return 0;
}