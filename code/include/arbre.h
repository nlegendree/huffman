#include "octet.h"
#ifndef __ARBRE__

typedef struct 
{
    struct Noeud *gauche;
    struct Noeud *droite;
    Octet octet;
    unsigned int ponderation;
    
} Noeud;

typedef Noeud* ABR_ArbreDeHuffman;

// Constructeur 
ABR_ArbreDeHuffman* ARB_arbreDeHuffman(O_Octet octet, unsigned int ponderation);
// Destructeur
void ARB_detruireArbre(ABR_ArbreDeHuffman arbre);
// Copie l'arbre 
ABR_ArbreDeHuffman ARB_copierArbre(ABR_ArbreDeHuffman arbre);
// Combine les deux arbres et retourne le nouvel arbre
ABR_ArbreDeHuffman ARB_combiner(ABR_ArbreDeHuffman arbreDroit, ABR_ArbreDeHuffman arbreGauche);
unsigned int ARB_obtenirPonderation(ABR_ArbreDeHuffman arbre);
O_Octet ARB_obtenirOctet(ABR_ArbreDeHuffman arbre);
bool ARB_estUneFeuille(ABR_ArbreDeHuffman arbre);
ABR_ArbreDeHuffman ARB_obtenirFilsGauche(ABR_ArbreDeHuffman arbre);
ABR_ArbreDeHuffman ARB_obtenirFilsDroit(ABR_ArbreDeHuffman arbre);

#endif // !__ARBRE__
