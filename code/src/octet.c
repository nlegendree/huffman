#include "octet.h"
#include <stdio.h>
#include <stdlib.h>

O_Octet O_octet(Naturel8Bits octet)
{
    O_Octet o;
    o.octet = octet;
    return o;
}

Bit O_obtenirIemeBit(O_Octet octet, int i)
{
    if (i < 0 || i > 7)
    {
        printf("erreur : i doit etre compris entre 0 et 7\n");
        exit(1);
    }
    // On se deplace de i bits vers la droite
    return (octet.octet >> i) & 1;
}

void O_fixerIemeBit(O_Octet* octet, int i, Bit bit) {
    if (i < 0 || i > 7) {
        printf("erreur : l'indice i doit être compris entre 0 et 7\n");
        exit(1);
    }
    /*
    On deplace 1 de i bits vers la gauche,
    puis on inverse les bits de 1 avec ~, 
    pour finir on fait un AND logique avec l'octet, puis on fait un OR logique avec le bit
    */
    octet->octet = (octet->octet & ~(1 << i)) | (bit << i);
}

int O_obtenirNaturel8bits(O_Octet octet) {
    return (int)octet.octet;
}


int O_egale(O_Octet octet1, O_Octet octet2)
{
    return octet1.octet == octet2.octet;
}
