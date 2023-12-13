#include <stdio.h>
#include <stdbool.h>
#include "FileDePriorite.h"
#include "Arbre.h"

#define FP_MAX_TAILLE = 0xFF


typedef struct {
    ArbreDeHuffman arbre;
    unsigned int priorite;
} ElementFile;


typedef struct {
    ElementFile tab[FP_MAX_TAILLE];
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
    while (i > 1 && pfile->tab[i].priorite <= priorite) {
        pfile->tab[i] = pfile->tab[i - 1];
        i--;
    }
    pfile->tab[i].arbre = arbre;
    pfile->tab[i].priorite = priorite;
}


void FP_supprimerDernier(FileDePriorite *pfile) {
    if (!estVide(*pfile)) {
        pfile->tailleActuelle--;
        pfile->tab[pfile->tailleActuelle - 1].priorite = 0;
    }
}


ArbreDeHuffman FP_obtenirDernier(FileDePriorite *pfile) {
    if (!estVide(pfile)) {
        return pfile->tab[pfile->tailleActuelle - 1];
    }
}


bool FP_estVide(FileDePriorite *pfile) {
    return (pfile->tailleActuelle == 0);
}


unsigned int FP_longueur(FileDePriorite *pfile) {
    return pfile->tailleActuelle;
}
