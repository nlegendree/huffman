#ifndef  __FILDEPRIORITE__
#define __FILDEPRIORITE__
#include "arbre.h"

FileDePriorite FP_fileDePriorite();
void FP_ajouterElement(ArbreDeHuffman arbre, FileDePriorite *pfile);
void FP_supprimerDernier(FileDePriorite *pfile);
ArbreDeHuffman FP_obtenirDernier(FileDePriorite *pfile);
bool FP_estVide(FileDePriorite *pfile);
int FP_longueur(FileDePriorite *pfile);

#endif