#ifndef  __FILDEPRIORITE__
#define __FILDEPRIORITE__
#include <stdbool.h>
#include "arbre.h"

typedef struct FP_FileDePriorite {
    ABR_ArbreDeHuffman arbre[255];
    unsigned int tailleActuelle;
} FP_FileDePriorite;

FP_FileDePriorite FP_fileDePriorite();
void FP_ajouterElement(FP_FileDePriorite *pfile, ABR_ArbreDeHuffman arbre);
void FP_supprimerDernier(FP_FileDePriorite *pfile);
ABR_ArbreDeHuffman FP_obtenirDernier(FP_FileDePriorite *pfile);
bool FP_estVide(FP_FileDePriorite pfile);
unsigned int FP_longueur(FP_FileDePriorite pfile);

#endif