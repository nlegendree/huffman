#include <stdlib.h>
#include <CUnit/Basic.h>
#include "stats.h"
#include "octet.h"

int init_suite_success(void) { 
  return 0; 
}

int clean_suite_success(void) { 
  return 0; 
}

void test_ST_statistiques(void) {
    ST_Statistiques stats = ST_statistiques();
    for (long int i=0;i<256;i++) CU_ASSERT_TRUE(stats.lesStatistiques[i]==0);
}

void test_ST_obtenirOccurenceOctet(void) {
    ST_Statistiques stats = ST_statistiques();
    ST_fixerOccurenceOctet(O_octet(42),1618,&stats);
    CU_ASSERT_TRUE(ST_obtenirOccurenceOctet(stats,O_octet(42))==1618);
}

void test_ST_incrementerOccurenceOctet(void) {
    ST_Statistiques stats = ST_statistiques();
    ST_incrementerOccurenceOctet(O_octet(42),&stats);
    CU_ASSERT_TRUE(ST_obtenirOccurenceOctet(stats,O_octet(42))==1);
}


int main(int argc, char** argv){
  CU_pSuite pSuite = NULL;

  /* initialisation du registre de tests */
  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  /* ajout d'une suite de test */
  pSuite = CU_add_suite("Tests : Statistiques", init_suite_success, clean_suite_success);
  if (NULL == pSuite) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* Ajout des tests à la suite de tests boite noire */
  if ((NULL == CU_add_test(pSuite, "ST_statistiques", test_ST_statistiques))
      || (NULL == CU_add_test(pSuite, "ST_obtenirOccurenceOctet", test_ST_obtenirOccurenceOctet))
      || (NULL == CU_add_test(pSuite, "ST_incrementerOccurenceOctet", test_ST_incrementerOccurenceOctet))
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