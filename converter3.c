// https://www.infineon.com/dgdl/Application_Note_Resonant+LLC+Converter+Operation+and+Design_Infineon.pdf?fileId=db3a30433a047ba0013a4a60e3be64a1
#include "capitance.c"
#include "qVal.c"
#include "LrVal.c"
#include "LmVal.c"
#include "gainer.c"
#include "gainSorter.c"
#include "director.c"
int main()
{
    char capCr[20] = "./parts/Cr.dat";
    char qFile[20] = "./parts/qual.dat";
    char inductLr[20] = "./parts/Lr.dat";
    char inductLm[20] = "./parts/Lm.dat";
    char gainFile[20] = "./parts/gain.dat";

    int uIn = 48, uOut = 48, Pwr = 750;
    float deltauIn = uIn * 0.1;

    float smallestCap = 1e-12, biggestCap = 1e-6;
    float biggestLm = 1e-3, biggestLr = 1e-3;

    director("outputDat");
    director("parts");

    capitance(capCr, smallestCap, biggestCap);
    qVal(qFile);
    LrVal(inductLr, qFile, capCr, uIn, uOut, Pwr, biggestLr);
    LmVal(inductLm, inductLr, biggestLm);
    gainSorter(capCr, inductLm, uIn, uOut, Pwr, deltauIn);
    return 0;
}