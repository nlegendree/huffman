#ifndef  __FILDEPRIORITE__
#define __FILDEPRIORITE__

FileDePriorite fileDePrioriteVide();
void FP_ajouterElement(Octet octet, unsigned int indice, FileDePriorite file);
void FP_supprimerDernier(FileDePriorite file);
Octet FP_obtenirDernier(FileDePriorite file);
bool FP_estVide(FileDePriorite file);
int FP_longueur(FileDePriorite file);

#endif