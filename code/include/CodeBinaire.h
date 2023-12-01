#ifndef  __CODEBINAIRE__
#define __CODEBINAIRE__
struct CodeBinaire
{
long int nbBits;
long int bits[];
};

CodeBinaire codeBinaire();
void ajouterBit();
long int obtenirLongueur();
Bit obtenirIemeBit();
#endif