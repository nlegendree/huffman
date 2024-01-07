#include "arbre.h"
#include <stdio.h> 
#include <stdlib.h>

// Créer un arbre vide de manière dynamique
ABR_ArbreDeHuffman ABR_arbreDeHuffman(O_Octet octet, unsigned int ponderation) {
    ABR_ArbreDeHuffman arbre;
    arbre = malloc(sizeof (Noeud));
    arbre->gauche = NULL;
    arbre->droite = NULL;
    arbre->ponderation = ponderation;
    arbre->octet = octet;
    return arbre;
}

// Destructeur de tout l'arbre de manière récursive
void ABR_detruireArbre(ABR_ArbreDeHuffman arbre) {
    if (arbre != NULL) {
        ABR_detruireArbre((ABR_ArbreDeHuffman)arbre->gauche);
        ABR_detruireArbre((ABR_ArbreDeHuffman)arbre->droite);
        free(arbre);
    }
}

// Combine les deux arbres et retourne le nouvel arbre
ABR_ArbreDeHuffman ABR_combiner(ABR_ArbreDeHuffman arbreGauche, ABR_ArbreDeHuffman arbreDroit) {
    ABR_ArbreDeHuffman arbre;
    arbre = malloc(sizeof (Noeud));
    arbre->gauche = arbreGauche;
    arbre->droite = arbreDroit;
    arbre->ponderation = ABR_obtenirPonderation(arbreDroit) + ABR_obtenirPonderation(arbreGauche);
    return arbre;
}

// Retourne la pondération de l'arbre
unsigned int ABR_obtenirPonderation(ABR_ArbreDeHuffman arbre) {
    return arbre->ponderation;
}

// Retourne l'octet de l'arbre
O_Octet ABR_obtenirOctet(ABR_ArbreDeHuffman arbre) {
    return arbre->octet;
}

// Retourne vrai si l'arbre est une feuille
int ABR_estUneFeuille(ABR_ArbreDeHuffman arbre ) {
    return (arbre->gauche == NULL && arbre->droite == NULL);
}

// Retourne le fils gauche de l'arbre
ABR_ArbreDeHuffman ABR_obtenirFilsGauche(ABR_ArbreDeHuffman arbre) {
    return (ABR_ArbreDeHuffman)arbre->gauche;
}

// Retourne le fils droit de l'arbre
ABR_ArbreDeHuffman ABR_obtenirFilsDroit(ABR_ArbreDeHuffman arbre) {
    return (ABR_ArbreDeHuffman)arbre->droite;
}
