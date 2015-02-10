// MathUtil.cpp

#include <math.h>
#include "MathUtil.h"


double MathUtil::Round(double value , const int position) {
    double result;
    value *= pow(10, double(-position - 1));
    result = floor(value + 0.5);
    result *= pow(10 , double(position + 1));
    return result;
}
