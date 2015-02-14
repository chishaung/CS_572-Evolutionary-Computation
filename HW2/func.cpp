#include "func.h"

inline double sq(double x)
{
    return x*x;
}

double f0(double x, double y)
{
    return 1.0/(sq(x-1.0) + sq(y-3.0)) + 1.0;
}

double fa(double x, double y)
{
    return  sq(sin(3*x + 2)) + sin(2*y + 1) + 10/(3 + sq(y - (sq(x - .5) - 3)));
}

double fb(double x, double y)
{
    return  sq(sin(5*x + 1)) + sin(y + 2) + 10/(4 + sq(y - (x*x - 3)));
}

double fc(double x, double y)
{
    return  sq(sin(5*x + 1)) + sin(y + 2) + y*y/10 + 10/(4 + sq(y - (x*x - 3)));
}

double fd(double x, double y)
{
    return (sq(sin(3*x + 2)) + sin(2*y + 1)) * cos((x + 2)/5)*cos((y - 3)/2) + 10/(3 + sq(y - (sq(x - .5) - 3)));
}

double fr(double x, double y)
{
    double xx, yy;

    xx = .7 * (x + y);
    yy = .7 * (x - y); 

    return fd(xx, yy);
}
