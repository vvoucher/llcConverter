#include <stdio.h>
#include <math.h>
#define _USE_MATH_DEFINES
float frq0Calc(float Cr, float Lr)
{
    return 1 / (2 * M_PI * sqrt(Lr * Cr));
}