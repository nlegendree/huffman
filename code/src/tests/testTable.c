#include <stdlib.h>
#include <stdio.h>
#include <CUnit/Basic.h>
#include "table.h"
#include "octet.h"
#include "codeBinaire.h"
#include "bit.h"

int init_suite_success(void) { 
  return 0; 
}

int clean_suite_success(void) { 
  return 0; 
}

void test_tableDeCodage(void) {

    TDC_TableDeCodage table = TDC_tableDeCodage();
    CU_ASSERT_TRUE(table.nbElements == 0);

    TDC_ajouterOctet(&table, O_octet(1), CB_codeBinaire(1));
    CU_ASSERT_TRUE(table.nbElements == 1)
    
}


void test_estVide(void) {
    TDC_TableDeCodage table = TDC_tableDeCodage();

    // si est vide
    CU_ASSERT_TRUE(TDC_estVide(table));

    // si n'est pas vide
    CB_CodeBinaire code = CB_codeBinaire(UN);
    O_Octet octet = O_octet(34);
    TDC_ajouterOctet(&table,octet,code);
    CU_ASSERT_FALSE(TDC_estVide(table));

}

void test_octetPresent(void) {
    CB_CodeBinaire code = CB_codeBinaire(UN);
    O_Octet octet = O_octet(127);
    TDC_TableDeCodage table = TDC_tableDeCodage();

    // si octet non present
    CU_ASSERT_FALSE(TDC_octetPresent(table,octet));

    // si octet present
    TDC_ajouterOctet(&table,octet,code);
    CU_ASSERT_TRUE(TDC_octetPresent(table,octet));

    
}

void test_TDC_codeBinairePresent(void)
{
  TDC_TableDeCodage table = TDC_tableDeCodage();
  CB_CodeBinaire code = CB_codeBinaire(UN);
  O_Octet octet = O_octet(65);
  O_Octet octet2 = O_octet(103);
  TDC_ajouterOctet(&table,octet,code);

  // Si Code bianire présent
  CU_ASSERT_TRUE(TDC_octetPresent(table,octet));

  // Si code binaire non présent
  CU_ASSERT_FALSE(TDC_octetPresent(table,octet2));



}


void test_TDC_obtenirCodeOctet(void) {
    TDC_TableDeCodage table = TDC_tableDeCodage();
    O_Octet octet = O_octet(102);
  
    CB_CodeBinaire code = CB_codeBinaire(ZERO);
    CB_CodeBinaire code2 = CB_codeBinaire(UN);

    TDC_ajouterOctet(&table,octet, code);

    // si code non present
    CU_ASSERT_FALSE(CB_egale(TDC_obtenirCodeOctet(table,octet),code2));
    

    // si code present

    CU_ASSERT_TRUE(CB_egale(TDC_obtenirCodeOctet(table,octet),code));

}

void test_TDC_obtenirOctetCode(void)
{


  TDC_TableDeCodage table = TDC_tableDeCodage();
  O_Octet octet1 = O_octet(72);
  O_Octet octet2 = O_octet(88);
  CB_CodeBinaire code = CB_codeBinaire(UN);

  TDC_ajouterOctet(&table,octet2,code);


  // Si octet non présent
  CU_ASSERT_FALSE(O_egale(TDC_obtenirOctetCode(table,code),octet1));

  // Si octet présent
  TDC_ajouterOctet(&table,octet1,code);
  CU_ASSERT_TRUE(O_egale(TDC_obtenirOctetCode(table,code),octet2));

}



int main(int argc, char** argv){
  CU_pSuite pSuite = NULL;

  /* initialisation du registre de tests */
  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  /* ajout d'une suite de test */
  pSuite = CU_add_suite("Tests : CodeBinaire", init_suite_success, clean_suite_success);
  if (NULL == pSuite) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* Ajout des tests à la suite de tests boite noire */
  if ((NULL == CU_add_test(pSuite, "Constructeur table de codage ",test_tableDeCodage )) 
  || (NULL == CU_add_test(pSuite," test estVide ",test_estVide)) 
  || (NULL == CU_add_test(pSuite,"test octetPresent",test_octetPresent))
  || (NULL == CU_add_test(pSuite,"test obtenir code octet",test_TDC_obtenirCodeOctet))
  || (NULL == CU_add_test(pSuite,"test obtenir octet code",test_TDC_obtenirOctetCode))
  || (NULL == CU_add_test(pSuite,"test code binaire présent",test_TDC_codeBinairePresent))

      
      )
  {
    CU_cleanup_registry();
    return CU_get_error();
  }
  /* Lancement des tests */
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  printf("\n");
  CU_basic_show_failures(CU_get_failure_list());
  printf("\n\n");

  /* Nettoyage du registre */
  CU_cleanup_registry();
  return CU_get_error();
}
