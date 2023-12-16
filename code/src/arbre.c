#include "arbre.h"
#include <stdio.h> 

ABR_ArbreDeHuffman ARB_arbreDeHuffman(O_Octet octet, unsigned int ponderation) {
    ABR_ArbreDeHuffman arbre;
    arbre->gauche = NULL;
    arbre->droite = NULL;
    arbre->ponderation = ponderation;
    arbre->octet = octet;
    return arbre;
}
