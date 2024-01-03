#include <stdlib.h>
#include <CUnit/Basic.h>
#include "octet.h"

int init_suite_success(void) { 
  return 0; 
}

int clean_suite_success(void) { 
  return 0; 
}

void test_O_octet(void) {
    Naturel8Bits A = 0x41; // 'A' en ASCII
    O_Octet o = O_octet(A);
    CU_ASSERT_TRUE(o.octet == A);
}

void test_O_obtenirIemeBit(void) {
    int i = 0;
    Naturel8Bits A = 0x41; // 'A' en ASCII^
    O_Octet o = O_octet(A);
    CU_ASSERT_TRUE(O_obtenirIemeBit(o, i) == UN); //le dernier bit de 41 (A) est 1
}

void test_O_fixerIemeBit(void) {
    int i = 0;
    Naturel8Bits A = 0x41; // 'A' en ASCII
    Naturel8Bits varTest = 0x40;
    O_Octet o1 = O_octet(A);
    O_Octet o2 = O_octet(varTest);
    O_fixerIemeBit(&o2, i, UN);
    CU_ASSERT_TRUE(o2.octet == o1.octet);
}

void test_O_obtenirNaturel8bits(void) {
    Naturel8Bits A = 0x41; // 'A' en ASCII
    O_Octet o = O_octet(A);
    CU_ASSERT_TRUE(O_obtenirNaturel8bits(o) == (int)A);
}

int main(int argc, char** argv){
  CU_pSuite pSuite = NULL;

  /* initialisation du registre de tests */
  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  /* ajout d'une suite de test */
  pSuite = CU_add_suite("Tests boite noire : arbredehuffman", init_suite_success, clean_suite_success);
  if (NULL == pSuite) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* Ajout des tests à la suite de tests boite noire */
  if ((NULL == CU_add_test(pSuite, "O_octet", test_O_octet))
      || (NULL == CU_add_test(pSuite, "O_obtenirIemeBit", test_O_obtenirIemeBit))
      || (NULL == CU_add_test(pSuite, "O_fixerIemeBit", test_O_fixerIemeBit))
      || (NULL == CU_add_test(pSuite, "O_obtenirNaturel8bits", test_O_obtenirNaturel8bits))
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
