#ifndef  __TABLE__
#define __TABLE__

#include "Octet.h"
#include "CodeBinaire.h"

#TYPEDEF struct TableDeCodage
{
    long int nbElements;
    long int table[255];
};

#TYPEDEF struct Donnees
{
    Octet octet;
    CodeBinaire code;
}

TableDeCodage TDC_tableDeCodage();

int TDC_estVide(TableDeCodage tableDeCodage);

int TDC_octetPresent(TableDeCodage tableDeCodage, Octet octet);

int TDC_codePresent(TableDeCodage tableDeCodage, CodeBinaire codeBinaire);

int TDC_octetPossedeCode(TableDeCodage tableDeCodage, Octet octet);

void TDC_ajouterOctet(TableDeCodage* pTableDeCodage, Octet octet, CodeBinaire codeBinaire);

CodeBinaire TDC_obtenireCodeOctet(TableDeCodage tableDeCodage, Octet octet);

Octet TDC_obtenirOctetCode(TableDeCodage tableDeCodage, CodeBinaire codeBinaire);

#endif

