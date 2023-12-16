#include <stdio.h>
#include <stdbool.h>
#include "fileDePriorite.h"
#include "arbre.h"


FP_FileDePriorite FP_fileDePriorite() {
    FP_FileDePriorite temp;
    temp.tailleActuelle = 0;
    return temp;
}


void FP_ajouterElement(FP_FileDePriorite *pfile, ABR_ArbreDeHuffman arbre) {
    unsigned int i;
    pfile->tailleActuelle++;
    i = pfile->tailleActuelle;
    while (i > 1 && ARB_obtenirPonderation(arbre[i]) <= priorite) {
        pfile->arbre[i] = pfile->arbre[i - 1];
        i--;
    }
    pfile->tab[i].arbre = arbre;
}


void FP_supprimerDernier(FP_FileDePriorite *pfile) {
    if (!FP_estVide(*pfile)) {
        pfile->tailleActuelle--;
    }
}


ABR_ArbreDeHuffman FP_obtenirDernier(FP_FileDePriorite *pfile) {
    if (!FP_estVide(*pfile)) {
        return pfile->arbre[pfile->tailleActuelle];
    }
}


bool FP_estVide(FP_FileDePriorite pfile) {
    return (pfile.tailleActuelle == 0);
}


unsigned int FP_longueur(FP_FileDePriorite pfile) {
    return pfile.tailleActuelle;
}
