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

/// @brief Crée un arbre de Huffman à partir d'un octet et d'une pondération
/// @param octet élement de l'arbre
/// @param ponderation pondération de l'élément
/// @return ABR_ArbreDeHuffman
ABR_ArbreDeHuffman ABR_arbreDeHuffman(O_Octet octet, unsigned int ponderation);

/// @brief Libère la mémoire allouée à l'arbre de manière récursive
/// @param arbre arbre à détruire
void ABR_detruireArbre(ABR_ArbreDeHuffman arbre);

/// @brief Combine deux arbres et retourne le nouvel arbre
/// @param arbreGauche l'arbre de gauche
/// @param arbreDroit l'arbre de droite
/// @return ABR_ArbreDeHuffman 
ABR_ArbreDeHuffman ABR_combiner(ABR_ArbreDeHuffman arbreGauche, ABR_ArbreDeHuffman arbreDroit);

/// @brief Retourne la pondération de l'arbre
/// @param arbre arbre dont on souhaite obtenir la pondération
/// @return unsigned int
unsigned int ABR_obtenirPonderation(ABR_ArbreDeHuffman arbre);

/// @brief Retourne l'octet de l'arbre
/// @param arbre arbre dont on souhaite obtenir l'octet
/// @return O_Octet
O_Octet ABR_obtenirOctet(ABR_ArbreDeHuffman arbre);

/// @brief Retourne vrai si l'arbre est une feuille
/// @param arbre arbre dont on souhaite savoir si c'est une feuille
/// @return int
int ABR_estUneFeuille(ABR_ArbreDeHuffman arbre);

/// @brief Retourne le fils gauche de l'arbre
/// @param arbre arbre dont on souhaite obtenir le fils gauche
/// @return ABR_ArbreDeHuffman
ABR_ArbreDeHuffman ABR_obtenirFilsGauche(ABR_ArbreDeHuffman arbre);

/// @brief Retourne le fils droit de l'arbre
/// @param arbre arbre dont on souhaite obtenir le fils droit
/// @return ABR_ArbreDeHuffman
ABR_ArbreDeHuffman ABR_obtenirFilsDroit(ABR_ArbreDeHuffman arbre);

#endif // !__ARBRE__
