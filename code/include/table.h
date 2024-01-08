/**
 * \file table.h
 * \brief Implantation du TAD TableDeCodage
 * \author L. Janneau
 * \version 1.0
 * \date 19/12/2023
 *
 */

#ifndef  __TABLE__
#define __TABLE__

#include "octet.h"
#include "codeBinaire.h"

typedef struct 
{
    O_Octet octet;
    CB_CodeBinaire code;
} Donnees;

typedef struct
{
    long int nbElements;
    Donnees table[256];
} TDC_TableDeCodage;


/**
 * @brief Permet de créer une table de codage vide
 * 
 * @return TDC_TableDeCodage 
 */
TDC_TableDeCodage TDC_tableDeCodage(void);

/**
 * @brief Permet de savoir si une table de codage est vide
 * 
 * @param tableDeCodage 
 * @return int 
 */
int TDC_estVide(TDC_TableDeCodage tableDeCodage);

/**
 * @brief Permet de savoir si un octet est présent dans une table de codage
 * 
 * @param tableDeCodage 
 * @param octet 
 * @return int 
 */
int TDC_octetPresent(TDC_TableDeCodage tableDeCodage, O_Octet octet);


/**
 * @brief Permet d'ajouter un octet et son code binaire dans une table de codage
 * 
 * @param pTableDeCodage 
 * @param octet 
 * @param codeBinaire
 * @pre L'octet ne doit pas être présent dans la table de codage 
 * @pre Le nombre d'éléments de la table de codage doit être inférieur ou égal à 255
 */
void TDC_ajouterOctet(TDC_TableDeCodage* pTableDeCodage, O_Octet octet, CB_CodeBinaire codeBinaire);

/**
 * @brief Permet d'obtenir le code binaire d'un octet dans une table de codage
 * 
 * @param tableDeCodage 
 * @param octet
 * @pre L'octet doit être présent dans la table de codage
 * @return CB_CodeBinaire 
 */
CB_CodeBinaire TDC_obtenirCodeOctet(TDC_TableDeCodage tableDeCodage, O_Octet octet);

/**
 * @brief Permet de savoir si un code binaire est présent dans une table de codage
 * 
 * @param tableDeCodage 
 * @param codeBinaire 
 * @return int 
 */
int TDC_codeBinairePresent(TDC_TableDeCodage tableDeCodage, CB_CodeBinaire codeBinaire);

/**
 * @brief Permet d'obtenir l'octet d'un code binaire dans une table de codage
 * 
 * @param tableDeCodage 
 * @param codeBinaire
 * @pre Le code binaire doit être présent dans la table de codage
 * @return O_Octet 
 */
O_Octet TDC_obtenirOctetCode(TDC_TableDeCodage tableDeCodage, CB_CodeBinaire codeBinaire);

#endif
