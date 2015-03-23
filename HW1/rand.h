#ifndef RANDFLEAH
#define RANDFLEAH

///////////////////////////////////////////////////
//
// Simple fast portable 64 bit random number generators based on
// a RNG called flea by Bob Jenkins.  Thanks, Bob!
//
// http://burtleburtle.net/bob/rand/talksmall.html
//
// WARNING: INIT REQUIRED before use!!!
//

// WARNING: the following includes may vary by OS, since these
// libraries may be in different places on different machines.
//#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

void     initRand();                       // init required before use!!!
void     initRand(unsigned long long int a, unsigned long long int b);  // init with 2 seeds

unsigned long long int randULL();          // 64 bits random number
double   randUnit();                       // random [0,1]
double   randPMUnit();                     // random [-1,1]
int      randMod(int m);                   // random [0,m-1]
void     randMod2(int m, int &a, int &b);
int      randMask(unsigned long long int mask);  // random in bit mask
bool     choose(double prob);              // true with probability prob
unsigned long long randCoinToss();         // 50:50 true or false
bool     choose8(int eigth);               // fast choose based on prob in 1/8 increments
bool     chooseMask(unsigned long long int mask, int prob); 
double   randNorm(double stddev);          // normal distribution
double   randCauchy();                     // Cauchy distribution
double   randCauchy(double mean, double scale);
#endif