#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
// #include "gEquation.c"
#define _USE_MATH_DEFINES
// #include "director.c"
#include <dirent.h>
#include "gEquation.c"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "isDirEmpty.c"
void director();
int isDirEmpty();
// float gEquation();

void gainer2(int m, float quality, float Cr, float Lr, float Lm, float gMin, float gMax)
{
    float frqW0 = 1 / (2 * M_PI * sqrt(Lr * Cr));

    if (frqW0 < 1e6 && frqW0 > 5 * 1e5) // if frequenci of LC is lower than 1Mhz
    {

        FILE *img;
        char nameFile[200];
        char directorName[200];
        sprintf(directorName, "./outputDat/Cap%eLm%eLr%e", Cr, Lm, Lr);
        director(directorName);
        sprintf(nameFile, "./outputDat/Cap%eLm%eLr%e/m%d.dat", Cr, Lm, Lr, m);
        img = fopen(nameFile, "wb");
        float gain = 0;

        float gainOld = 0, gainMin = 0, gainMax = 0, frqWx = 0, frqW = 0;

        // for (int i = -1; i < 1; i++)
        {
            for (double j = 0; j <= 20; j++)
            {
                frqWx = j / 10; //* pow(10, i);
                if (frqWx != 0)
                {
                    frqW = frqW0 * frqWx;
                    gain = gEquation(frqWx, m, quality);
                    if (!(gainOld == 0))
                    {
                        if (gain > gainOld && gain > gainMax)
                            gainMax = gain;
                        if (gainMax > gain && gainOld > gain)
                            gainMin = gain;
                    }
                    else
                    {
                        gainMin = gain;
                        gainMax = gain;
                    }

                    // fprintf(img,"M gain Cr Lr Lm: %d\t%f\t%e\t%e\t%e\n",m,gain,Cr,Lr,Lm);
                    // fprintf(img,"frqWx:%f Gain:%f gainOld:%f gainMax:%f gainMin:%f\n",frqWx,gain,gainOld,gainMax,gainMin);
                    fprintf(img, "%f\t%f\t%f\t%f\n", frqWx, gain, frqW, frqW0);
                    gainOld = gain;
                }
            }
        }
        int deleter = 0;
        if (gainMax > gMax && gainMin < gMin)
            deleter = 1;
        else
            deleter = 0;

        int len = ftell(img);
        fclose(img);

        if (len == 0 || deleter != 1)
            remove(nameFile);

        if (isDirEmpty(directorName) != 1)
        {
            printf("New values: %s\n", directorName);
            rmdir(directorName);
        }
    }
}