#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#define _USE_MATH_DEFINES

float gEquation(float frqWx,int m, float quality)
{
    return (pow(frqWx,2)*(m-1))/(sqrt(pow((m*pow(frqWx,2)-1),2) + pow((pow(frqWx,2)-1),2)*pow(m-1,2)*pow(quality,2)));
}