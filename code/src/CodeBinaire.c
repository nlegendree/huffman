#include "CodeBinaire.h"

CodeBinaire codeBinaire(Bit bit){
    CodeBinaire temp;
    temp.nbBits = 1;
    temp.bits[0] = bit;
    return temp;
}

void ajouterBit(CodeBinaire* cB, Bit bit){
    (*cB).nbBits = (*cB).nbBits + 1;
    (*cB).bits[(*cB).nbBits] = bit;
}

short int obtenirLongueur(CodeBinaire cB){
    return cB.nbBits;
}

Bit obtenirIemeBit(CodeBinaire cB, short int ind){
    return cB.bits[ind];
}