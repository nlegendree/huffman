#ifndef  __FILDEPRIORITE__
#define __FILDEPRIORITE__
#include <stdbool.h>
#include "arbre.h"

typedef struct FP_FileDePriorite {
    ArbreDeHuffman arbre[255];
    unsigned int tailleActuelle;
} FP_FileDePriorite;

FP_FileDePriorite FP_fileDePriorite();
void FP_ajouterElement(ArbreDeHuffman arbre, FP_FileDePriorite *pfile);
void FP_supprimerDernier(FP_FileDePriorite *pfile);
ArbreDeHuffman FP_obtenirDernier(FP_FileDePriorite *pfile);
bool FP_estVide(FileDePriorite *pfile);
int FP_longueur(FileDePriorite *pfile);

#endif