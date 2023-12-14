#include <stdio.h>
#include <stdbool.h>
#include "fileDePriorite.h"
#include "arbre.h"


typedef struct {
    ArbreDeHuffman arbre[255];
    unsigned int tailleActuelle;
} FileDePriorite;


FileDePriorite FP_fileDePriorite() {
    FileDePriorite temp;
    temp.tailleActuelle = 0;
    return temp;
}


void FP_ajouterElement(ArbreDeHuffman arbre, unsigned int priorite, FileDePriorite *pfile) {
    unsigned int i;
    pfile->tailleActuelle++;
    i = pfile->tailleActuelle;
    while (i > 1 && ARB_obtenirPonderation(arbre[i]) <= priorite) {
        pfile->arbre[i] = pfile->arbre[i - 1];
        i--;
    }
    pfile->tab[i].arbre = arbre;
}


void FP_supprimerDernier(FileDePriorite *pfile) {
    if (!estVide(*pfile)) {
        pfile->tailleActuelle--;
    }
}


ArbreDeHuffman FP_obtenirDernier(FileDePriorite *pfile) {
    if (!estVide(*pfile)) {
        return pfile->arbre[pfile->tailleActuelle];
    }
}


bool FP_estVide(FileDePriorite *pfile) {
    return (pfile->tailleActuelle == 0);
}


unsigned int FP_longueur(FileDePriorite *pfile) {
    return pfile->tailleActuelle;
}
