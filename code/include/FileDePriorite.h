#ifndef  __FILDEPRIORITE__
#define __FILDEPRIORITE__

FileDePriorite fileDePrioriteVide();
void ajouterElement(Element element, unsigned int indice, FileDePriorite file);
void supprimerDernier(FileDePriorite file);
Element obtenirDernier(FileDePriorite file);
bool estVide(FileDePriorite file);
int longueur(FileDePriorite file);

#endif