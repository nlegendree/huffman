/**
 * \file arbre.h
 * \brief Implantation du TAD ArbreDeHuffman
 * \author D. Timoz
 * \version 1.0
 * \date 19/12/2023
 *
 */

#include "octet.h"
#ifndef __ARBRE__
#define __ARBRE__

typedef struct Noeud Noeud;

/**
 * @brief structure arbre de Huffman
*/
struct Noeud
{
    Noeud *gauche;            // Left child
    Noeud *droite;            // Right child
    O_Octet octet;            // Data (assuming O_Octet is defined elsewhere)
    unsigned int ponderation; // Weight
};

/**
 * @brief structure arbre de Huffman
*/
typedef Noeud *ABR_ArbreDeHuffman; // Pointer to a Huffman Tree node

/// @fn ABR_ArbreDeHuffman ABR_arbreDeHuffman(O_Octet octet, unsigned int ponderation)
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
/// @pre Les arbres doivent être différents de NULL
/// @return ABR_ArbreDeHuffman
ABR_ArbreDeHuffman ABR_combiner(ABR_ArbreDeHuffman arbreGauche, ABR_ArbreDeHuffman arbreDroit);

/// @brief Retourne la pondération de l'arbre
/// @param arbre arbre dont on souhaite obtenir la pondération
/// @pre L'arbre doit être différent de NULL
/// @return unsigned int
unsigned int ABR_obtenirPonderation(ABR_ArbreDeHuffman arbre);

/// @brief Retourne l'octet de l'arbre
/// @param arbre arbre dont on souhaite obtenir l'octet
/// @pre L'arbre doit être différent de NULL
/// @return O_Octet
O_Octet ABR_obtenirOctet(ABR_ArbreDeHuffman arbre);

/// @brief Retourne vrai si l'arbre est une feuille
/// @param arbre arbre dont on souhaite savoir si c'est une feuille
/// @pre L'arbre doit être différent de NULL
/// @return int
int ABR_estUneFeuille(ABR_ArbreDeHuffman arbre);

/// @brief Retourne le fils gauche de l'arbre
/// @param arbre arbre dont on souhaite obtenir le fils gauche
/// @pre L'arbre doit être différent de NULL et doit avoir un fils gauche
/// @return ABR_ArbreDeHuffman
ABR_ArbreDeHuffman ABR_obtenirFilsGauche(ABR_ArbreDeHuffman arbre);

/// @brief Retourne le fils droit de l'arbre
/// @param arbre arbre dont on souhaite obtenir le fils droit
/// @pre L'arbre doit être différent de NULL et doit avoir un fils droit
/// @return ABR_ArbreDeHuffman
ABR_ArbreDeHuffman ABR_obtenirFilsDroit(ABR_ArbreDeHuffman arbre);

#endif // !__ARBRE__
