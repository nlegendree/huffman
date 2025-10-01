/**
 * \file stats.h
 * \brief Implantation du TAD Statistiques
 * \author L. Janneau
 * \version 1.0
 * \date 19/12/2023
 *
 */

#ifndef  __STATS__
#define __STATS__

#include "octet.h"

#define MAX 0x100

/**
 * \brief Le type ST_Statistiques permet de représenter des statistiques d'apparition d'octets
 *
 */
typedef struct ST_Statistiques
{
    long int nbOccurenceTotal;
    long int lesStatistiques[MAX];
} ST_Statistiques;

/**
 * @fn ST_Statistiques ST_statistiques(void)
 * @brief Permet de créer des statistiques vides
 * 
 * @return ST_Statistiques
 */
ST_Statistiques ST_statistiques(void);

/**
 * @fn long int ST_obtenirOccurenceOctet(ST_Statistiques statistiques,O_Octet octet)
 * @brief Permet d'obtenir le nombre d'occurences d'un octet
 * 
 * @param statistiques 
 * @param octet
 * @return long int 
 */
long int ST_obtenirOccurenceOctet(ST_Statistiques statistiques,O_Octet octet);

/**
 * @fn void ST_incrementerOccurenceOctet(O_Octet octet, ST_Statistiques* pstatistiques)
 * @brief Permet d'incrémenter le nombre d'occurences d'un octet
 * 
 * @param octet
 * @param pstatistiques
 */
void ST_incrementerOccurenceOctet(O_Octet octet, ST_Statistiques* pstatistiques);

/**
 * @fn void ST_fixerOccurenceOctet(O_Octet octet, long int nbOccurence, ST_Statistiques* pstatistiques)
 * @brief Permet de fixer le nombre d'occurences d'un octet
 * 
 * @param octet
 * @param nbOccurence
 * @param pstatistiques
 */
void ST_fixerOccurenceOctet(O_Octet octet, long int nbOccurence, ST_Statistiques* pstatistiques);

/**
 * @fn long int ST_obtenirTotalOccurence(ST_Statistiques statistiques)
 * @brief Permet d'obtenir le nombre total d'occurences (tout octet compris)
 * 
 * @param statistiques
 * @return long int
 */
long int ST_obtenirTotalOccurence(ST_Statistiques statistiques);

#endif

