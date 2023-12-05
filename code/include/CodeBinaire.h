#ifndef  __CODEBINAIRE__
#define __CODEBINAIRE__

#define CB_NBMAXBIT 7

typedef enum {bitA0 = 0, bitA1 = 1} Bit; /*ça sera aussi dans le main je suppose*/

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
