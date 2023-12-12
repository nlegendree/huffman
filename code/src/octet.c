#include "octet.h"
#include <stdio.h>
#include <stdlib.h>

Octet octet(Naturel8Bits octet)
{
    Octet o;
    o.octet = octet;
    return o;
}

Bit obtenirIemeBit(Octet octet, int i)
{
    if (i < 0 || i > 7)
    {
        printf("erreur : i doit etre compris entre 0 et 7\n");
        exit(1);
    }
    // On se deplace de i bits vers la droite
    return (octet.octet >> i) & 1;
}

void fixerIemeBit(Octet* octet, int i, Bit bit) {
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
