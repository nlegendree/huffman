#include <stdlib.h>
#include <CUnit/Basic.h>
#include "arbre.h"
#include "octet.h"

int init_suite_success(void) { 
  return 0; 
}

int clean_suite_success(void) { 
  return 0; 
}

void test_ABR_obtenirOctet(void) {
    ABR_ArbreDeHuffman arbre = ABR_arbreDeHuffman(O_octet(42), 5);
    CU_ASSERT_TRUE(ABR_obtenirOctet(arbre).octet == O_octet(42).octet);
}

void test_ABR_obtenirPonderation(void) {
    ABR_ArbreDeHuffman arbre = ABR_arbreDeHuffman(O_octet(42), 5);
    CU_ASSERT_TRUE(ABR_obtenirPonderation(arbre) == 5);
}

void test_ABR_combiner(void) {
    ABR_ArbreDeHuffman arbreGauche = ABR_arbreDeHuffman(O_octet(10), 3);
    ABR_ArbreDeHuffman arbreDroit = ABR_arbreDeHuffman(O_octet(20), 2);
    ABR_ArbreDeHuffman combinaison = ABR_combiner(arbreGauche, arbreDroit);
    CU_ASSERT_TRUE(ABR_obtenirPonderation(combinaison) == (ABR_obtenirPonderation(arbreGauche) + ABR_obtenirPonderation(arbreDroit)));
}

void test_ABR_estUneFeuille(void) {
    ABR_ArbreDeHuffman arbre = ABR_arbreDeHuffman(O_octet(42), 5);
    ABR_ArbreDeHuffman arbreGauche = ABR_arbreDeHuffman(O_octet(10), 3);
    ABR_ArbreDeHuffman arbreDroit = ABR_arbreDeHuffman(O_octet(20), 2);
    ABR_ArbreDeHuffman combinaison = ABR_combiner(arbreGauche, arbreDroit);
    CU_ASSERT_TRUE(ABR_estUneFeuille(arbre));
    CU_ASSERT_FALSE(ABR_estUneFeuille(combinaison));
}

void test_ABR_obtenirFilsGauche(void) {
    ABR_ArbreDeHuffman arbreGauche = ABR_arbreDeHuffman(O_octet(10), 3);
    ABR_ArbreDeHuffman arbreDroit = ABR_arbreDeHuffman(O_octet(20), 2);
    ABR_ArbreDeHuffman combinaison = ABR_combiner(arbreGauche, arbreDroit);
    CU_ASSERT_TRUE(ABR_obtenirFilsGauche(combinaison) == arbreGauche);
}

void test_ABR_obtenirFilsDroit(void) {
    ABR_ArbreDeHuffman arbreGauche = ABR_arbreDeHuffman(O_octet(10), 3);
    ABR_ArbreDeHuffman arbreDroit = ABR_arbreDeHuffman(O_octet(20), 2);
    ABR_ArbreDeHuffman combinaison = ABR_combiner(arbreGauche, arbreDroit);
    CU_ASSERT_TRUE(ABR_obtenirFilsDroit(combinaison) == arbreDroit);
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
  if ((NULL == CU_add_test(pSuite, "ABR_obtenirOctet", test_ABR_obtenirOctet))
      || (NULL == CU_add_test(pSuite, "ABR_obtenirPonderation", test_ABR_obtenirPonderation))
      || (NULL == CU_add_test(pSuite, "ABR_combiner", test_ABR_combiner))
      || (NULL == CU_add_test(pSuite, "ABR_estUneFeuille", test_ABR_estUneFeuille))
      || (NULL == CU_add_test(pSuite, "ABR_obtenirFilsGauche", test_ABR_obtenirFilsGauche))
      || (NULL == CU_add_test(pSuite, "ABR_obtenirFilsDroit", test_ABR_obtenirFilsDroit))
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
