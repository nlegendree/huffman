#include "arbre.h"
#include <stdio.h> 

ABR_ArbreDeHuffman ARB_arbreDeHuffman(O_Octet octet, unsigned int ponderation) {
    ABR_ArbreDeHuffman arbre;
    arbre = malloc(sizeof (Noeud));
    arbre->gauche = NULL;
    arbre->droite = NULL;
    arbre->ponderation = ponderation;
    arbre->octet = octet;
    return arbre;
}

// Destructeur
void ARB_detruireArbre(ABR_ArbreDeHuffman arbre);
// Copie l'arbre 
ABR_ArbreDeHuffman ARB_copierArbre(ABR_ArbreDeHuffman arbre);
// Combine les deux arbres et retourne le nouvel arbre
ABR_ArbreDeHuffman ARB_combiner(ABR_ArbreDeHuffman arbreDroit, ABR_ArbreDeHuffman arbreGauche) {
    ABR_ArbreDeHuffman arbre;
    arbre = malloc(sizeof (Noeud));
    arbre->gauche = arbreGauche;
    arbre->droite = arbreDroit;
    arbre->ponderation = ARB_obtenirPonderation(arbreDroit) + ARB_obtenirPonderation(arbreGauche);
    return arbre;
}
unsigned int ARB_obtenirPonderation(ABR_ArbreDeHuffman arbre);
O_Octet ARB_obtenirOctet(ABR_ArbreDeHuffman arbre);
int ARB_estUneFeuille(ABR_ArbreDeHuffman arbre);
ABR_ArbreDeHuffman ARB_obtenirFilsGauche(ABR_ArbreDeHuffman arbre);
ABR_ArbreDeHuffman ARB_obtenirFilsDroit(ABR_ArbreDeHuffman arbre);
