#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#define _USE_MATH_DEFINES
#include "gainer2.c"

//#include "rounder.c"

void gainSorter(char CrFile[10], char LmFile[20],int uIn,int uOut, int Pwr,float deltauIn)
{
    FILE *LM, *CR, *img;
    LM=fopen(LmFile,"r+"); CR=fopen(CrFile,"r+");
    float quality=0, Cr=0, Lr=0, Lm=0,CrOG;
    int m=0;
    char name[FILENAME_MAX];

    double gain=uOut/uIn;
    float gMin= (float) uIn/(uIn+deltauIn), gMax=(float) uIn/(uIn-deltauIn);
    printf("Min %f, Max %f\n", gMin,gMax);
    
    int oneer;
    float oldCr,oldLr=0,oldLm=0;


    for(int i=1;i<=20; i++)
    {
        while(fscanf(CR,"%e\n",&CrOG)!=EOF)
        {
            while(fscanf(LM,"%d\t%e\t%e\t%e\t%e\n",&m,&quality,&Cr,&Lr,&Lm)!=EOF)
            {                 
                if(CrOG==Cr && m==i && rounder(Lm)!=oldLm && rounder(Lr)!=oldLr)
                {            
                   gainer2(m,quality,CrOG,rounder(Lr),rounder(Lm), gMin,gMax);
                }
                oldLr=rounder(Lr);oldLm=rounder(Lm);oldCr=Cr;
            }
            fseek(LM,0L,SEEK_SET);
        }
        fseek(CR,0L,SEEK_SET);   
    }

    fclose(CR);fclose(LM);
}