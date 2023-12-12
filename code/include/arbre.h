#include "octet.h"
#ifndef __ARBRE__

typedef struct 
{
    struct Noeud *gauche;
    struct Noeud *droite;
    Octet octet;
    unsigned int ponderation;
    
} Noeud;

typedef Noeud* ArbreDeHuffman;

// Constructeur 
ArbreDeHuffman* ARB_arbreDeHuffman(Octet octet, unsigned int ponderation);
// Destructeur
void ARB_detruireArbre(ArbreDeHuffman arbre);
// Copie l'arbre 
ArbreDeHuffman ARB_copierArbre(ArbreDeHuffman arbre);
// Combine les deux arbres et retourne le nouvel arbre
ArbreDeHuffman ARB_combiner(arbreDroit: ArbreDeHuffman, arbreGauche: ArbreDeHuffman);
unsigned int ARB_obtenirPonderation(ArbreDeHuffman arbre);
Octet ARB_obtenirOctet(ArbreDeHuffman arbre);
bool ARB_estUneFeuille(ArbreDeHuffman arbre);
ArbreDeHuffman ARB_obtenirFilsGauche(ArbreDeHuffman arbre);
ArbreDeHuffman ARB_obtenirFilsDroit(ArbreDeHuffman arbre);

#endif // !__ARBRE__
