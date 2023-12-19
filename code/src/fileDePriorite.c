#include <stdio.h>
#include <stdbool.h>
#include "fileDePriorite.h"


FP_FileDePriorite FP_fileDePriorite() {
    FP_FileDePriorite temp;
    temp.tailleActuelle = 0;
    return temp;
}


void FP_ajouterElement(FP_FileDePriorite *pfile, ABR_ArbreDeHuffman arbre) {
    unsigned int i;
    unsigned int priorite = ABR_obtenirPonderation(&arbre);
    pfile->tailleActuelle++;
    i = pfile->tailleActuelle;
    while (i > 1 && ABR_obtenirPonderation(&arbre[i]) <= priorite) {
        pfile->arbres[i] = pfile->arbres[i - 1];
        i--;
    }
    pfile->arbres[i] = arbre;
}


void FP_supprimerDernier(FP_FileDePriorite *pfile) {
    if (!FP_estVide(*pfile)) {
        pfile->tailleActuelle--;
    }
}


ABR_ArbreDeHuffman FP_obtenirDernier(FP_FileDePriorite file) {
    if (!FP_estVide(file)) {
        return (file.arbres[file.tailleActuelle]);
    }
}


bool FP_estVide(FP_FileDePriorite file) {
    return (file.tailleActuelle == 0);
}


unsigned int FP_longueur(FP_FileDePriorite file) {
    return file.tailleActuelle;
}
