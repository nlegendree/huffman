#ifndef  __CODEBINAIRE__
#define __CODEBINAIRE__

#include "bit.h"

#define CB_NBMAXBIT 7

/**
 * @brief structure code binaire
 * 
 */
typedef struct CB_CodeBinaire
{
    short int nbBits;
    Bit bits[CB_NBMAXBIT];
} CB_CodeBinaire;

/**
 * @brief crée un code binaire à partir d'un bit
 * 
 * @param bit de type Bit
 * @return CodeBinaire
 */
CB_CodeBinaire CB_codeBinaire(Bit bit);

/**
 * @brief permet d'ajouter un bit à un code binaire
 * 
 * @param cB code binaire auquel on souhaite ajouter un bit
 * @param bit bit à ajouter
 */
void CB_ajouterBit(CB_CodeBinaire* cB, Bit bit);

/**
 * @brief donne la longueur d'un code binaire (son nombre de bits)
 * 
 * @param cB code binaire dont on souhaite obtenir la longueur
 * @return short int
 */
short int CB_obtenirLongueur(CB_CodeBinaire cB);

/**
 * @brief permet d'obtenir le ième bit d'un code binaire
 * 
 * @param cB code binaire dont on souhaite obtenir le ième bit
 * @param ind indice du bit que l'on souhaite obtenir (inférieur ou égal à la longueur du code binaire)
 * @return Bit
 */
Bit CB_obtenirIemeBit(CB_CodeBinaire cB, short int ind);

/**
 * @brief permet de comparer 2 codes binaires
 * 
 * @param cB1 
 * @param cB2 
 * @return int 
 */
int CB_egale(CB_CodeBinaire cB1, CB_CodeBinaire cB2);

#endif
