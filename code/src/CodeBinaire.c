#include "CodeBinaire.h"

CB_CodeBinaire CB_codeBinaire(Bit bit){
    CB_CodeBinaire temp;
    temp.nbBits = 1;
    temp.bits[0] = bit;
    return temp;
}

void CB_ajouterBit(CB_CodeBinaire* cB, Bit bit){
    (*cB).nbBits = (*cB).nbBits + 1;
    (*cB).bits[(*cB).nbBits] = bit;
}

short int CB_obtenirLongueur(CB_CodeBinaire cB){
    return cB.nbBits;
}

Bit CB_obtenirIemeBit(CB_CodeBinaire cB, short int ind){
    return cB.bits[ind];
}