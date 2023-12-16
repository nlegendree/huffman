#ifndef  __CODEBINAIRE__
#define __CODEBINAIRE__

#include "bit.h"

#define CB_NBMAXBIT 7


typedef struct CB_CodeBinaire
{
    short int nbBits;
    Bit bits[CB_NBMAXBIT];
} CB_CodeBinaire;

CB_CodeBinaire CB_codeBinaire(Bit bit);

void CB_ajouterBit(CB_CodeBinaire* cB, Bit bit);

short int CB_obtenirLongueur(CB_CodeBinaire cB);

Bit CB_obtenirIemeBit(CB_CodeBinaire cB, short int ind);

#endif
