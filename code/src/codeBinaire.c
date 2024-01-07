#include "codeBinaire.h"

CB_CodeBinaire CB_codeBinaire(Bit bit){
    CB_CodeBinaire temp;
    temp.nbBits = 1;
    temp.bits[0] = bit;
    return temp;
}

void CB_ajouterBit(CB_CodeBinaire* cB, Bit bit){
    cB->bits[cB->nbBits] = bit;
    cB->nbBits = cB->nbBits + 1;
}

short int CB_obtenirLongueur(CB_CodeBinaire cB){
    return cB.nbBits;
}

Bit CB_obtenirIemeBit(CB_CodeBinaire cB, short int ind){
    return cB.bits[ind];
}

int CB_egale(CB_CodeBinaire cB1, CB_CodeBinaire cB2){
    if (cB1.nbBits != cB2.nbBits) {
        return 0;
    }
    for (int i=0; i<cB1.nbBits; i++) {
        if (cB1.bits[i] != cB2.bits[i]) {
            return 0;
        }
    }
    return 1;
}
