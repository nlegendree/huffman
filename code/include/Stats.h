#ifndef  __STATS__
#define __STATS__

#include "octet.h"

#define MAX 0x100

typedef struct Statistiques
{
    long int nbOccurenceTotal;
    long int lesStatistiques[MAX];
};

Statistiques statistiques();

long int obtenirOccurenceOctet(Statistique statistiques,O_Octet octet);

void incrementerOccurenceOctet(O_Octet octet, Statistiques* pstatistiques);

void fixerOccurenceOctet(O_Octet octet, long int nbOccurence, Statistiques* pstatistiques);

long int obtenirTotalOccurence(Statistiques statistiques);

#endif

