#ifndef  __CODEBINAIRE__
#define __CODEBINAIRE__

#define NBMAXBIT 7

typedef enum {bitA0 = 0, bitA1 = 1} Bit; /*ça sera aussi dans le main je suppose*/

typedef struct CodeBinaire
{
    short int nbBits;
    Bit bits[NBMAXBIT];
} CodeBinaire;

CodeBinaire codeBinaire(Bit bit);

void ajouterBit(CodeBinaire* cB, Bit bit);

short int obtenirLongueur(CodeBinaire cB);

Bit obtenirIemeBit(CodeBinaire cB, short int ind);

#endif
