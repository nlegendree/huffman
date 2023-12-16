#ifndef OCTET_H
#define OCTET_H
#include "octet.h"
#include "bit.h"

typedef unsigned char Naturel8Bits;

/**

 * @brief structure octet

 * 

 */

struct O_Octet

{

    Naturel8Bits octet;

};

typedef struct O_Octet O_Octet;

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



#endif
