#include "octet.h"
#include "codeBinaire.h"
#include <assert.h>
TableDeCodage TDC_tableDeCodage(){
    TableDeCodage tableDeCodage;
    tableDeCodage.nbElements = 0;
}

int TDC_estVide(TableDeCodage tableDeCodage) {
    return tableDeCodage.nbElements == 0;
}

int TDC_octetPresent(TableDeCodage tableDeCodage, Octet octet) {
    for (int i=0; i<tableDeCodage.nbElements; i++) {
        if (tableDeCodage.table[i].octet==octet) {
            return 1;
        } 
    }
    return 0;
}

int TDC_codePresent(TableDeCodage tableDeCodage, CodeBinaire codeBinaire) {
    for (int i=0; i<tableDeCodage.nbElements; i++) {
        if (tableDeCodage.table[i].codeBinaire==codeBinaire) {
            return 1;
        }
    }
    return 0;
}

void TDC_ajouterOctet(TableDeCodage* pTableDeCodage, Octet octet, CodeBinaire codeBinaire) {
    assert(!TDC_octetPresent(*pTableDeCodage,octet));
    assert(*pTableDeCodage.nbElements<255);
    *pTableDeCodage.nbElements++;
    *pTableDeCodage.table[*pTableDeCodage.nbElements-1].octet=octet;
    *pTableDeCodage.table[*pTableDeCodage.nbElements-1].codeBinaire=codeBinaire;
}

CodeBinaire TDC_obtenireCodeOctet(TableDeCodage tableDeCodage, Octet octet) {
    assert(TDC_octetPresent(tableDeCodage,octet));
    for (int i=0; i<tableDeCodage.nbElements; i++) {
        if (tableDeCodage.table[i].octet==octet) {
            return tableDeCodage.table[i].codeBinaire;
        }
    }
}

Octet TDC_obtenirOctetCode(TableDeCodage tableDeCodage, CodeBinaire codeBinaire) {
    assert(TDC_codeBinairePresent(tableDeCodage,codeBinaire));
    for (int i=0; i<tableDeCodage.nbElements; i++) {
        if (tableDeCodage.table[i].codeBinaire==codeBinaire) {
            return tableDeCodage.table[i].octet;
        }
    }
}

