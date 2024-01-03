#include <stdlib.h>
#include <CUnit/Basic.h>
#include "codeBinaire.h"
#include "bit.h"

int init_suite_success(void) { 
  return 0; 
}

int clean_suite_success(void) { 
  return 0; 
}

void test_CB_codeBinaire(void) {
    CB_CodeBinaire codeBinaire = CB_codeBinaire(UN);
    CU_ASSERT_TRUE(codeBinaire.nbBits == 1);
    CU_ASSERT_TRUE(codeBinaire.bits[0] == UN);
}

void test_CB_ajouterBit(void) {
    CB_CodeBinaire codeBinaire = CB_codeBinaire(UN);
    CB_ajouterBit(&codeBinaire, ZERO);
    CU_ASSERT_TRUE(codeBinaire.nbBits == 2);
    CU_ASSERT_TRUE(codeBinaire.bits[1] == ZERO);
}

void test_CB_obtenirLongueur(void) {
    CB_CodeBinaire codeBinaire = CB_codeBinaire(UN);
    CU_ASSERT_TRUE(CB_obtenirLongueur(codeBinaire) == 1);

    CB_ajouterBit(&codeBinaire, ZERO);
    CU_ASSERT_TRUE(CB_obtenirLongueur(codeBinaire) == 2);
}

void test_CB_obtenirIemeBit(void) {
    CB_CodeBinaire codeBinaire = CB_codeBinaire(UN);
    CB_ajouterBit(&codeBinaire, ZERO);
    CU_ASSERT_TRUE(CB_obtenirIemeBit(codeBinaire, 0) == UN);
    CU_ASSERT_TRUE(CB_obtenirIemeBit(codeBinaire, 1) == ZERO);
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
  if ((NULL == CU_add_test(pSuite, "CB_codeBinaire", test_CB_codeBinaire))
      || (NULL == CU_add_test(pSuite, "CB_ajouterBit", test_CB_ajouterBit))
      || (NULL == CU_add_test(pSuite, "CB_obtenirLongueur", test_CB_obtenirLongueur))
      || (NULL == CU_add_test(pSuite, "CB_obtenirIemeBit", test_CB_obtenirIemeBit))
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
