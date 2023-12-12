#ifndef OCTET_H
#define OCTET_H

typedef unsigned char Naturel8Bits;
typedef enum { FAUX, VRAI } Bit;

/**
 * @brief structure octet
 * 
 */
struct Octet
{
    Naturel8Bits octet;
};#ifndef OCTET_H

#define OCTET_H

typedef unsigned char Naturel8Bits;

typedef enum { FAUX, VRAI } Bit;

/**

 * @brief structure octet

 * 

 */

struct Octet

{

    Naturel8Bits octet;

};

typedef struct Octet Octet;

/**

 * @brief crée un octet à partir d'un tableau de 8 bits

 * 

 * @param tableau de 8 bits

 * @return Octet 

 */

Octet octet(Naturel8Bits octet);

/**

 * @brief permet d'obtenir le ième bit d'un octet

 * 

 * @param octet octet dont on veut obtenir le ième bit

 * @param i indice du bit

 * @return Bit 

 */

Bit obtenirIemeBit(Octet octet, int i);

/**

 * @brief permet de fixer le ième bit d'un octet

 * 

 * @param octet octet dont on veut fixer le ième bit

 * @param i indice du bit

 * @param bit bit à fixer

 */

void fixerIemeBit(Octet* octet, int i, Bit bit);

#endif
typedef struct Octet Octet;

/**
 * @brief crée un octet à partir d'un tab#ifndef OCTET_H

#define OCTET_H

typedef unsigned char Naturel8Bits;

typedef enum { FAUX, VRAI } Bit;

/**

 * @brief structure octet

 * 

 */

struct Octet

{

    Naturel8Bits octet;

};

typedef struct Octet Octet;

/**

 * @brief crée un octet à partir d'un tableau de 8 bits

 * 

 * @param tableau de 8 bits

 * @return Octet 

 */

Octet octet(Naturel8Bits octet);

/**

 * @brief permet d'obtenir le ième bit d'un octet

 * 

 * @param octet octet dont on veut obtenir le ième bit

 * @param i indice du bit

 * @return Bit 

 */

Bit obtenirIemeBit(Octet octet, int i);

/**

 * @brief permet de fixer le ième bit d'un octet

 * 

 * @param octet octet dont on veut fixer le ième bit

 * @param i indice du bit

 * @param bit bit à fixer

 */

void fixerIemeBit(Octet* octet, int i, Bit bit);

#endifleau de 8 bits
 * 
 * @param tableau de 8 bits
 * @return Octet 
 */
Octet octet(Naturel8Bits octet);

/**
 * @brief permet d'obtenir le ième bit d'un octet
 * 
 * @param octet octet dont on veut obtenir le ième bit
 * @param i indice du bit
 * @return Bit 
 */
Bit obtenirIemeBit(Octet octet, int i);

/**
 * @brief permet de fixer le ième bit d'un octet
 * 
 * @param octet octet dont on veut fixer le ième bit
 * @param i indice du bit
 * @param bit bit à fixer
 */
void fixerIemeBit(Octet* octet, int i, Bit bit);



#endif
