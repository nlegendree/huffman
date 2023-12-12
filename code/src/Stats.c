#include "Octet.h"
#include "Stats.h"

Statistiques statistiques(){
    Statistiques stats;
    stats.nbOccurenceTotal=0;
    for (long int i=0;i<256;i++){
        stats.lesStatistiques[i]=0;
    }
    return stats;
}

long int obtenirOccurenceOctet(Statistique statistiques,Octet octet){
    return statistiques.lesStatistiques[octetToInt(octet)];
}

void incrementerOccurenceOctet(Octet octet,Statistiques* pstatistiques){
    *pstatistiques.lesStatistiques[octetToInt(octet)]++;
}

void fixerOccurenceOctet(Octet octet, long int nbOccurence, Statistiques* pstatistiques){
    *pstatistiques.lesStatistiques[octetToInt(octet)] = nbOccurence;
}
long int obtenirTotalOccurence(Statistiques statistiques){
    return statistiques.nbOccurenceTotal;
}
