#include "table.h"
#include "octet.h"
#include <assert.h>
#include <stdio.h>

TDC_TableDeCodage TDC_tableDeCodage(void)
{
    TDC_TableDeCodage tableDeCodage;
    tableDeCodage.nbElements = 0;

    return tableDeCodage;
}

int TDC_estVide(TDC_TableDeCodage tableDeCodage)
{
    return tableDeCodage.nbElements == 0;
}

int TDC_octetPresent(TDC_TableDeCodage tableDeCodage, O_Octet o)
{

    for (int i = 0; i < tableDeCodage.nbElements; i++)
    {
        if (O_egale(tableDeCodage.table[i].octet, o))
        {
            return 1;
        }
    }
    return 0;
}

int TDC_codeBinairePresent(TDC_TableDeCodage tableDeCodage, CB_CodeBinaire codeBinaire)
{
    for (int i = 0; i < tableDeCodage.nbElements; i++)
    {
        if (CB_egale(tableDeCodage.table[i].code, codeBinaire))
        {
            return 1;
        }
    }
    return 0;
}

CB_CodeBinaire TDC_obtenirCodeOctet(TDC_TableDeCodage tableDeCodage, O_Octet o)
{
    assert(TDC_octetPresent(tableDeCodage, o));
    for (int i = 0; i < tableDeCodage.nbElements; i++)
    {
        if (O_egale(tableDeCodage.table[i].octet, o))
        {
            return tableDeCodage.table[i].code;
        }
    }

    return CB_codeBinaire(ZERO);
}

void TDC_ajouterOctet(TDC_TableDeCodage *pTableDeCodage, O_Octet octet, CB_CodeBinaire codeBinaire)
{
    assert(!TDC_octetPresent(*pTableDeCodage, octet));
    assert(pTableDeCodage->nbElements < 255);
    pTableDeCodage->nbElements++;
    pTableDeCodage->table[pTableDeCodage->nbElements - 1].octet = octet;
    pTableDeCodage->table[pTableDeCodage->nbElements - 1].code = codeBinaire;
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
    return O_octet(0);
}
