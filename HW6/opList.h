#ifndef OPLISTH
#define OPLISTH
#include <stdlib.h>
#include <stdio.h>

// // // // // // // // // // // // // // // // // // // // // // // // 
// Operators
//
// Operators are Op objects that contain a function that
// can be evaluated
//

double addOp(double x, double y);
double subOp(double x, double y);
double mulOp(double x, double y);
double divOp(double x, double y);
double sinOp(double x, double y);
double xOp(double x, double y);
void setX(double x);                  // allows you to set the value of X before evaluating at that point
double constOp(double x, double y);

#endif