#ifndef FUNC_H
#define FUNC_H
#include <string>
#include <vector>
#include <utility>
extern char *clear_chips = new char[4000];
extern char *ALP = new char[26];
extern double freq_E[26][26];
extern int length;

void Print_Key(string key);
void Print_Table(double freq_D[][26], double freq_E[][26]);
void shuffle(char *a, int size);
void ReadFile(char *&clear_chips);
void pmx(int *a, int *b, int *out, int k, int size);
void pmm(char *key);
double Fitness(string key2);
int FindMinIndex(vector<pair<string, double> > vp, int start, int end);
#endif