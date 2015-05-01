#include "rand.h"
#include "opList.h"

// // // // // // // // // // // // // // // // // // // // // // // // 
// Operators
//
// Operators are Op objects that contain a function that
// can be evaluated
//


double addOp(double x, double y)
{
    return x+y;
}

double subOp(double x, double y)
{
    return x-y;
}

double mulOp(double x, double y)
{
    return x*y;
}

double divOp(double x, double y)
{
    const double cutoff=.000001;

    if (fabs(y)>cutoff) return x/y;
    else return x/cutoff;
}

double sinOp(double x, double y)
{
    return sin(x);
}


// the value of X is set as a global variable in this file!

static double xValue;
double xOp(double x, double y)
{
    return xValue;
}


void setX(double x)
{
    xValue = x;
}


// not actually called
double constOp(double x, double y)
{
    return 0.0;
}
