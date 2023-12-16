#ifndef  __STATS__
#define __STATS__

#include "octet.h"

#define MAX 0x100

typedef struct ST_Statistiques
{
    long int nbOccurenceTotal;
    long int lesStatistiques[MAX];
} ST_Statistiques;

ST_Statistiques ST_statistiques();

long int ST_obtenirOccurenceOctet(ST_Statistiques statistiques,O_Octet octet);

void ST_incrementerOccurenceOctet(O_Octet octet, ST_Statistiques* pstatistiques);

void ST_fixerOccurenceOctet(O_Octet octet, long int nbOccurence, ST_Statistiques* pstatistiques);

long int ST_obtenirTotalOccurence(ST_Statistiques statistiques);

#endif

