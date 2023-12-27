#include "octet.h"
#ifndef __ARBRE__
#define __ARBRE__

typedef struct Noeud Noeud;

struct Noeud {
    Noeud* gauche;          // Left child
    Noeud* droite;          // Right child
    O_Octet octet;          // Data (assuming O_Octet is defined elsewhere)
    unsigned int ponderation; // Weight
};

typedef Noeud* ABR_ArbreDeHuffman; // Pointer to a Huffman Tree node

// Constructeur 
ABR_ArbreDeHuffman ABR_arbreDeHuffman(O_Octet octet, unsigned int ponderation);
// Destructeur
void ABR_detruireArbre(ABR_ArbreDeHuffman arbre);
// Copie l'arbre 
ABR_ArbreDeHuffman ABR_copierArbre(ABR_ArbreDeHuffman arbre);
// Combine les deux arbres et retourne le nouvel arbre
ABR_ArbreDeHuffman ABR_combiner(ABR_ArbreDeHuffman arbreDroit, ABR_ArbreDeHuffman arbreGauche);
unsigned int ABR_obtenirPonderation(ABR_ArbreDeHuffman arbre);
O_Octet ABR_obtenirOctet(ABR_ArbreDeHuffman arbre);
int ABR_estUneFeuille(ABR_ArbreDeHuffman arbre);
ABR_ArbreDeHuffman ABR_obtenirFilsGauche(ABR_ArbreDeHuffman arbre);
ABR_ArbreDeHuffman ABR_obtenirFilsDroit(ABR_ArbreDeHuffman arbre);

#endif // !__ARBRE__
