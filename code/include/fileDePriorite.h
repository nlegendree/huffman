/**
 * \file fileDePriorite.h
 * \brief Implantation du TAD FileDePriorite
 * \author N. Legendre
 * \version 1.0
 * \date 19/12/2023
 *
 */

#ifndef  __FILDEPRIORITE__
#define __FILDEPRIORITE__
#include <stdbool.h>
#include "arbre.h"

/**
 * \brief Le type FP_FileDePriorite permet de représenter une file de priorité
 *
 */

typedef struct FP_FileDePriorite {
    ABR_ArbreDeHuffman arbres[256];
    unsigned int tailleActuelle;
} FP_FileDePriorite;

/**
 * \fn FP_FileDePriorite FP_fileDePriorite(void)
 * \brief Fonction de création d'une file de priorité vide
 * 
 * \return FP_FileDePriorite
 */
FP_FileDePriorite FP_fileDePriorite(void);

/**
 * \fn void FP_ajouterElement(FP_FileDePriorite *pfile, ABR_ArbreDeHuffman arbre)
 * \brief Fonction qui ajoute un arbre à la file de priorité
 * 
 * \param pfile : file de priorité à laquelle on veut ajouter un arbre
 * \param arbre : arbre que l'on souhaite ajouter
 * \return FP_FileDePriorite 
 */
void FP_ajouterElement(FP_FileDePriorite *pfile, ABR_ArbreDeHuffman arbre);

/**
 * \fn void FP_supprimerDernier(FP_FileDePriorite *pfile)
 * \brief Fonction qui supprime le dernier arbre d'une file de priorité
 * 
 * \param pfile : file de priorité à laquelle on veut supprimer le dernier arbre
 * \return FP_FileDePriorite
 */
void FP_supprimerDernier(FP_FileDePriorite *pfile);

/**
 * \fn ABR_ArbreDeHuffman FP_obtenirDernier(FP_FileDePriorite *pfile)
 * \brief Fonction qui permet d'obtenir le dernier arbre d'une file de priorité
 * 
 * \param file : file de priorité
 * \return ABR_ArbreDeHuffman 
 */
ABR_ArbreDeHuffman FP_obtenirDernier(FP_FileDePriorite file);

/**
 * \fn bool FP_estVide(FP_FileDePriorite pfile)
 * \brief Fonction qui permet de savoir si une file de priorité est vide
 * 
 * \param file : file de priorité
 * \return FP_FileDePriorite
 */
bool FP_estVide(FP_FileDePriorite file);

/**
 * \fn bool FP_estVide(FP_FileDePriorite pfile)
 * \brief Fonction qui permet d'obtenir la longueur d'une file de priorité
 * 
 * \param file : file de priorité
 * \return unsigned int
 */
unsigned int FP_longueur(FP_FileDePriorite file);

#endif
