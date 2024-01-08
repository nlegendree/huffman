/**
 * \file octet.h
 * \brief Implantation du TAD Octet
 * \author V. Sentchev
 * \version 1.0
 * \date 19/12/2023
 *
 */

#ifndef __OCTET__
#define __OCTET__
#include "octet.h"
#include "bit.h"

typedef unsigned char Naturel8Bits;

/**
 * @brief structure octet
 * 
 */
typedef struct 
{
    Naturel8Bits octet;
} O_Octet;

/**
 * @brief crée un octet à partir d'un tableau de 8 bits
 * 
 * @param tableau de 8 bits
 * @return Octet 
 */
O_Octet O_octet(Naturel8Bits octet);

/**
 * @brief permet d'obtenir le ième bit d'un octet
 * 
 * @param octet octet dont on veut obtenir le ième bit
 * @param i indice du bit
 * @return Bit 
 */
Bit O_obtenirIemeBit(O_Octet octet, int i);

/**
 * @brief permet de fixer le ième bit d'un octet
 * 
 * @param octet octet dont on veut fixer le ième bit
 * @param i indice du bit
 * @param bit bit à fixer
 */

void O_fixerIemeBit(O_Octet* octet, int i, Bit bit);

/**
 * @brief permet d'obtenir la valeur décimale d'un octet
 * 
 * @param octet octet dont on veut obtenir la valeur décimale
 * @return int 
 */
Naturel8Bits O_obtenirNaturel8bits(O_Octet octet);

/**
 * @brief Permet de comparer l'instance de 2 octets
 * 
 * @param o1 
 * @param o2 
 * @return int 
 */
int O_egale(O_Octet octet1, O_Octet octet2);

#endif
