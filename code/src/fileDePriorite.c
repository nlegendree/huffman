#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include "fileDePriorite.h"
#include "octet.h"


FP_FileDePriorite FP_fileDePriorite() {
    FP_FileDePriorite temp;
    for (int i = 0; i <= 255; ++i) {
        temp.arbres[i] = ABR_arbreDeHuffman(O_octet(0), 0);
    }
    temp.tailleActuelle = 0;
    return temp;
}


void FP_ajouterElement(FP_FileDePriorite *pfile, ABR_ArbreDeHuffman arbre) {
    unsigned int i;
    unsigned int priorite = ABR_obtenirPonderation(arbre);
    i = pfile->tailleActuelle;
    while (i > 1 && ABR_obtenirPonderation(pfile->arbres[i - 1]) <= priorite) {
        pfile->arbres[i] = pfile->arbres[i - 1];
        i--;
    }
    pfile->tailleActuelle++;
    pfile->arbres[i] = arbre;
}


void FP_supprimerDernier(FP_FileDePriorite *pfile) {
    assert(!FP_estVide(*pfile));
    if (pfile->tailleActuelle > 0) {
        pfile->tailleActuelle--;
    }
}


ABR_ArbreDeHuffman FP_obtenirDernier(FP_FileDePriorite file) {
    assert(!FP_estVide(file));
    return (file.arbres[file.tailleActuelle - 1]);
}


bool FP_estVide(FP_FileDePriorite file) {
    return (file.tailleActuelle == 0);
}


unsigned int FP_longueur(FP_FileDePriorite file) {
    return file.tailleActuelle;
}

