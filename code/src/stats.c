#include "octet.h"
#include "stats.h"

ST_Statistiques ST_statistiques(){
    ST_Statistiques stats;
    stats.nbOccurenceTotal=0;
    for (long int i=0;i<256;i++){
        stats.lesStatistiques[i]=0;
    }
    return stats;
}

long int ST_obtenirOccurenceOctet(ST_Statistiques statistiques, O_Octet octet){
    return statistiques.lesStatistiques[O_obtenirNaturel8bits(octet)];
}

void ST_incrementerOccurenceOctet(O_Octet octet, ST_Statistiques* pstatistiques){
    pstatistiques->lesStatistiques[O_obtenirNaturel8bits(octet)]++;
}

void ST_fixerOccurenceOctet(O_Octet octet, long int nbOccurence, ST_Statistiques* pstatistiques){
    pstatistiques->lesStatistiques[O_obtenirNaturel8bits(octet)] = nbOccurence;
}
long int ST_obtenirTotalOccurence(ST_Statistiques statistiques){
    return statistiques.nbOccurenceTotal;
}
