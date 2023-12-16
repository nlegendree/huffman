#include "arbre.h"
#include <stdio.h> 

// Créer un arbre vide de manière dynamique
ABR_ArbreDeHuffman ARB_arbreDeHuffman(O_Octet octet, unsigned int ponderation) {
    ABR_ArbreDeHuffman arbre;
    arbre = malloc(sizeof (Noeud));
    arbre->gauche = NULL;
    arbre->droite = NULL;
    arbre->ponderation = ponderation;
    arbre->octet = octet;
    return arbre;
}

// Destructeur de tout l'arbre de manière récursive
void ARB_detruireArbre(ABR_ArbreDeHuffman arbre) {
    if (arbre != NULL) {
        ARB_detruireArbre(arbre->gauche);
        ARB_detruireArbre(arbre->droite);
        free(arbre);
    }
}
// Copie l'arbre 
ABR_ArbreDeHuffman ARB_copierArbre(ABR_ArbreDeHuffman arbre) {
    ABR_ArbreDeHuffman arbreCopie;
    arbreCopie = memcpy(malloc(sizeof (Noeud)), arbre, sizeof (Noeud));
    return arbreCopie;
}
// Combine les deux arbres et retourne le nouvel arbre
ABR_ArbreDeHuffman ARB_combiner(ABR_ArbreDeHuffman arbreDroit, ABR_ArbreDeHuffman arbreGauche) {
    ABR_ArbreDeHuffman arbre;
    arbre = malloc(sizeof (Noeud));
    arbre->gauche = arbreGauche;
    arbre->droite = arbreDroit;
    arbre->ponderation = ARB_obtenirPonderation(arbreDroit) + ARB_obtenirPonderation(arbreGauche);
    return arbre;
}

// Retourne la pondération de l'arbre
unsigned int ARB_obtenirPonderation(ABR_ArbreDeHuffman arbre) {
    return arbre->ponderation;
}

// Retourne l'octet de l'arbre
O_Octet ARB_obtenirOctet(ABR_ArbreDeHuffman arbre) {}

// Retourne vrai si l'arbre est une feuille
int ARB_estUneFeuille(ABR_ArbreDeHuffman arbre ) {
    return (arbre->gauche == NULL && arbre->droite == NULL);
}

// Retourne le fils gauche de l'arbre
ABR_ArbreDeHuffman ARB_obtenirFilsGauche(ABR_ArbreDeHuffman arbre) {
    return arbre->gauche;
}

// Retourne le fils droit de l'arbre
ABR_ArbreDeHuffman ARB_obtenirFilsDroit(ABR_ArbreDeHuffman arbre) {
    return arbre->droite;
}
