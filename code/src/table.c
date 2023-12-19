#include "table.h"
#include "octet.h"
#include <assert.h>
#include <stdio.h>

/*TDC_TableDeCodage TDC_tableDeCodage(){
    TDC_TableDeCodage tableDeCodage;
    tableDeCodage.nbElements = 0;
}

int TDC_estVide(TDC_TableDeCodage tableDeCodage) {
    return tableDeCodage.nbElements == 0;
}

int TDC_octetPresent(TDC_TableDeCodage tableDeCodage, O_Octet octet) {
    for (int i=0; i<tableDeCodage.nbElements; i++) {
        if (tableDeCodage.table[i].octet == octet) {
            return 1;
        } 
    }
    return 0;
}

int TDC_codePresent(TDC_TableDeCodage tableDeCodage, CB_CodeBinaire codeBinaire) {
    for (int i=0; i<tableDeCodage.nbElements; i++) {
        if (tableDeCodage.table[i].codeBinaire==codeBinaire) {
            return 1;
        }
    }
    return 0;
}

void TDC_ajouterOctet(TDC_TableDeCodage* pTableDeCodage, O_Octet octet, CB_CodeBinaire codeBinaire) {
    assert(!TDC_octetPresent(*pTableDeCodage, octet));
    assert(pTableDeCodage->nbElements < 255);
    pTableDeCodage->nbElements++;
    pTableDeCodage->table[pTableDeCodage->nbElements-1].octet = (long int)octet;
    pTableDeCodage->table[pTableDeCodage->nbElements-1].codeBinaire = (long int)codeBinaire;
}

CB_CodeBinaire TDC_obtenireCodeOctet(TDC_TableDeCodage tableDeCodage, O_Octet octet) {
    assert(TDC_octetPresent(tableDeCodage,octet));
    for (int i=0; i<tableDeCodage.nbElements; i++) {
        if (tableDeCodage.table[i].octet==octet) {
            return tableDeCodage.table[i].codeBinaire;
        }
    }
}

O_Octet TDC_obtenirOctetCode(TDC_TableDeCodage tableDeCodage, CB_CodeBinaire codeBinaire) {
    assert(TDC_codeBinairePresent(tableDeCodage,codeBinaire));
    for (int i=0; i<tableDeCodage.nbElements; i++) {
        if (tableDeCodage.table[i].codeBinaire==codeBinaire) {
            return tableDeCodage.table[i].octet;
        }
    }
}*/

TDC_TableDeCodage TDC_tableDeCodage(){
    TDC_TableDeCodage tableDeCodage;
    tableDeCodage.nbElements = 0;

    return tableDeCodage;
}

int TDC_estVide(TDC_TableDeCodage tableDeCodage) {
    return tableDeCodage.nbElements == 0;
}

int TDC_octetPresent(TDC_TableDeCodage tableDeCodage, O_Octet o) {
    
    for (int i=0; i<tableDeCodage.nbElements; i++) {
        if (O_egale(tableDeCodage.table[i].octet, o)) {
            return 1;
        }
    }
    return 0;
}



int TDC_codeBinairePresent(TDC_TableDeCodage tableDeCodage, CB_CodeBinaire codeBinaire) {
    for (int i=0; i<tableDeCodage.nbElements; i++) {
        if (CB_egale(tableDeCodage.table[i].code, codeBinaire)) {
            return 1;
        }
    }
    return 0;
}



void TDC_ajouterOctet(TDC_TableDeCodage* pTableDeCodage, O_Octet octet, CB_CodeBinaire codeBinaire) {
    assert(!TDC_octetPresent(*pTableDeCodage, octet));
    assert(pTableDeCodage->nbElements < 255);
    pTableDeCodage->nbElements++;
    pTableDeCodage->table[pTableDeCodage->nbElements-1].octet = octet;
    pTableDeCodage->table[pTableDeCodage->nbElements-1].code = codeBinaire;
}




O_Octet TDC_obtenirOctetCode(TDC_TableDeCodage tableDeCodage, CB_CodeBinaire codeBinaire)
{
    assert(TDC_codeBinairePresent(tableDeCodage, codeBinaire));
    for (int i = 0; i < tableDeCodage.nbElements; i++)
    {
        if (CB_egale(tableDeCodage.table[i].code, codeBinaire))
        {
            return tableDeCodage.table[i].octet;
        }
    }

}




