#include <stdlib.h>
#include <CUnit/Basic.h>
#include "arbre.h"

int init_suite_success(void) { 
  return 0; 
}

int clean_suite_success(void) { 
  return 0; 
}

void test_AH_obtenirElement(void) {
    ABR_ArbreDeHuffman arbre = ARB_arbreDeHuffman('A', 5);
    CU_ASSERT_TRUE(AH_obtenirElement(arbre) == 'A');
}

void test_AH_combiner(void) {
    ABR_ArbreDeHuffman arbreGauche = ABR_arbreDeHuffman('B', 3);
    ABR_ArbreDeHuffman arbreDroit = ABR_arbreDeHuffman('C', 2);
    ABR_ArbreDeHuffman combinaison = ABR_combiner(arbreGauche, arbreDroit);
    CU_ASSERT_TRUE(AH_obtenirPondération(combinaison) == (AH_obtenirPondération(arbreGauche) + AH_obtenirPondération(arbreDroit)));
}

void test_AH_obtenirPondération(void) {
    ABR_ArbreDeHuffman arbre = ABR_arbreDeHuffman('A', 5);
    CU_ASSERT_TRUE(AH_obtenirPondération(arbre) == 5);
}

void test_AH_estUneFeuille(void) {
    ABR_ArbreDeHuffman arbre = ABR_arbreDeHuffman('A', 5);
    ABR_ArbreDeHuffman arbreGauche = ABR_arbreDeHuffman('B', 3);
    ABR_ArbreDeHuffman arbreDroit = ABR_arbreDeHuffman('C', 2);
    ABR_ArbreDeHuffman combinaison = ABR_combiner(arbreGauche, arbreDroit);
    CU_ASSERT_TRUE(AH_estUneFeuille(arbre));
    CU_ASSERT_FALSE(AH_estUneFeuille(combinaison));
}

void test_AH_obtenirArbreGauche(void) {
    ABR_ArbreDeHuffman arbreGauche = ABR_arbreDeHuffman('B', 3);
    ABR_ArbreDeHuffman arbreDroit = ABR_arbreDeHuffman('C', 2);
    ABR_ArbreDeHuffman combinaison = ABR_combiner(arbreGauche, arbreDroit);
    CU_ASSERT_TRUE(AH_obtenirArbreGauche(combinaison) == arbreGauche);
}

void test_AH_obtenirArbreDroit(void) {
    ABR_ArbreDeHuffman arbreGauche = ABR_arbreDeHuffman('B', 3);
    ABR_ArbreDeHuffman arbreDroit = ABR_arbreDeHuffman('C', 2);
    ABR_ArbreDeHuffman combinaison = ABR_combiner(arbreGauche, arbreDroit);
    CU_ASSERT_TRUE(AH_obtenirArbreDroit(combinaison) == arbreDroit);
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
  if ((NULL == CU_add_test(pSuite, "AH_obtenirElement", test_AH_obtenirElement))
      || (NULL == CU_add_test(pSuite, "AH_combiner", test_AH_combiner))
      || (NULL == CU_add_test(pSuite, "AH_obtenirPonderation", test_AH_obtenirPonderation))
      || (NULL == CU_add_test(pSuite, "AH_estUneFeuille", test_AH_estUneFeuille))
      || (NULL == CU_add_test(pSuite, "AH_obtenirArbreGauche", test_AH_obtenirArbreGauche))
      || (NULL == CU_add_test(pSuite, "AH_obtenirArbreDroit", test_AH_obtenirArbreDroit))
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