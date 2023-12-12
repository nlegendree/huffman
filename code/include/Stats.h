#ifndef  __STATS__
#define __STATS__

#include "Octet.h"

#TYPEDEF struct Statistiques
{
    long int nbOccurenceTotal;
    long int lesStatistiques[MAX];
}

Statistiques statistiques();

long int obtenirOccurenceOctet(Statistique statistiques,Octet octet);

void incrementerOccurenceOctet(Octet octet,Statistiques* pstatistiques);

void fixerOccurenceOctet(Octet octet, long int nbOccurence, Statistiques* pstatistiques);

long int obtenirTotalOccurence(Statistiques statistiques);

#endif

