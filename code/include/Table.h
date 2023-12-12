#ifndef  __TABLE__
#define __TABLE__

#include "octet.h"
#include "codeBinaire.h"

typedef struct TDC_TableDeCodage
{
    long int nbElements;
    long int table[255];
};

typedef struct Donnees
{
    Octet octet;
    CB_CodeBinaire code;
}

TDC_TableDeCodage TDC_tableDeCodage();

int TDC_estVide(TDC_TableDeCodage tableDeCodage);

int TDC_octetPresent(TDC_TableDeCodage tableDeCodage, Octet octet);

int TDC_codePresent(TDC_TableDeCodage tableDeCodage, CB_CodeBinaire codeBinaire);

int TDC_octetPossedeCode(TDC_TableDeCodage tableDeCodage, Octet octet);

void TDC_ajouterOctet(TDC_TableDeCodage* pTableDeCodage, Octet octet, CB_CodeBinaire codeBinaire);

CB_CodeBinaire TDC_obtenireCodeOctet(TDC_TableDeCodage tableDeCodage, Octet octet);

Octet TDC_obtenirOctetCode(TDC_TableDeCodage tableDeCodage, CB_CodeBinaire codeBinaire);

#endif

