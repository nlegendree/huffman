#include <stdlib.h>
#include <CUnit/Basic.h>
#include "Arbre.h"

int init_suite_success(void) { 
  return 0; 
}

int clean_suite_success(void) { 
  return 0; 
}

ArbreDeHuffman arbre = arbreDeHuffman('A', 5);
ArbreDeHuffman arbreGauche = arbreDeHuffman('B', 3);
ArbreDeHuffman arbreDroit = arbreDeHuffman('C', 2);
ArbreDeHuffman combinaison = combiner(arbreGauche, arbreDroit);

void test_obtenirElement(void) {
    CU_ASSERT_TRUE(obtenirElement(arbre)=='A');
}

void test_combiner(void) {
    CU_ASSERT_TRUE(obtenirPondération(combinaison) == (obtenirPondération(arbreGauche) + obtenirPondération(arbreDroit)));
}

void test_obtenirPondération(void) {
    CU_ASSERT_TRUE(obtenirPondération(arbre), 5);
}

void test_estUneFeuille(void) {
    CU_ASSERT_TRUE(estUneFeuille(arbre));
    CU_ASSERT_FALSE(estUneFeuille(combinaison));
}

void test_obtenirArbreGauche(void) {
    CU_ASSERT_TRUE(obtenirArbreGauche(combinaison) == arbreGauche);
}

void test_obtenirArbreDroit(void) {
    CU_ASSERT_TRUE(obtenirArbreDroit(combinaison) == arbreDroit);
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
  if ((NULL == CU_add_test(pSuite, "obtenirElement", test_obtenirElement))
      || (NULL == CU_add_test(pSuite, "combiner", test_combiner))
      || (NULL == CU_add_test(pSuite, "obtenirPonderation", test_obtenirPonderation))
      || (NULL == CU_add_test(pSuite, "estUneFeuille", test_estUneFeuille))
      || (NULL == CU_add_test(pSuite, "obtenirArbreGauche", test_obtenirArbreGauche))
      || (NULL == CU_add_test(pSuite, "obtenirArbreDroit", test_obtenirArbreDroit))
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