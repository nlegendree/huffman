#ifndef  __TABLE__
#define __TABLE__

#include "octet.h"
#include "codeBinaire.h"

typedef struct
{
    long int nbElements;
    long int table[255];
} TDC_TableDeCodage;

typedef struct 
{
    O_Octet octet;
    CB_CodeBinaire code;
} Donnees;

TDC_TableDeCodage TDC_tableDeCodage(void);

int TDC_estVide(TDC_TableDeCodage tableDeCodage);

int TDC_octetPresent(TDC_TableDeCodage tableDeCodage, O_Octet octet);

int TDC_codePresent(TDC_TableDeCodage tableDeCodage, CB_CodeBinaire codeBinaire);

int TDC_octetPossedeCode(TDC_TableDeCodage tableDeCodage, O_Octet octet);

void TDC_ajouterOctet(TDC_TableDeCodage* pTableDeCodage, O_Octet octet, CB_CodeBinaire codeBinaire);

CB_CodeBinaire TDC_obtenireCodeOctet(TDC_TableDeCodage tableDeCodage, O_Octet octet);

O_Octet TDC_obtenirOctetCode(TDC_TableDeCodage tableDeCodage, CB_CodeBinaire codeBinaire);

#endif

