#include <stdlib.h>
#include <CUnit/Basic.h>
#include "fileDePriorite.h"
#include "octet.h"
#include "arbre.h"

int init_suite_success(void) { 
  return 0; 
}

int clean_suite_success(void) { 
  return 0; 
}

void test_FP_fileDePriorite(void) {
    FP_FileDePriorite fileDePriorite = FP_fileDePriorite();
    CU_ASSERT_TRUE(FP_estVide(fileDePriorite));
}

void test_FP_ajouterElement(void) {
    FP_FileDePriorite fileDePriorite;
    fileDePriorite = FP_fileDePriorite();
    ABR_ArbreDeHuffman arbreDeHuffman1 = ABR_arbreDeHuffman(O_octet(42),5);
    ABR_ArbreDeHuffman arbreDeHuffman2 = ABR_arbreDeHuffman(O_octet(41),7);
    ABR_ArbreDeHuffman arbreDeHuffman3 = ABR_arbreDeHuffman(O_octet(58),9);
    FP_ajouterElement(&fileDePriorite,arbreDeHuffman3);
    FP_ajouterElement(&fileDePriorite,arbreDeHuffman1);
    FP_ajouterElement(&fileDePriorite,arbreDeHuffman2);
    CU_ASSERT_FALSE(FP_estVide(fileDePriorite));
    CU_ASSERT_TRUE(FP_longueur(fileDePriorite)==3);
    CU_ASSERT_TRUE(ABR_obtenirPonderation(FP_obtenirDernier(fileDePriorite))==5);
    CU_ASSERT_TRUE(ABR_obtenirOctet(FP_obtenirDernier(fileDePriorite)).octet==O_octet(42).octet);
    FP_supprimerDernier(&fileDePriorite);
    CU_ASSERT_TRUE(ABR_obtenirPonderation(FP_obtenirDernier(fileDePriorite))==7);
    CU_ASSERT_TRUE(ABR_obtenirOctet(FP_obtenirDernier(fileDePriorite)).octet==O_octet(41).octet);
    FP_supprimerDernier(&fileDePriorite);
    CU_ASSERT_TRUE(ABR_obtenirPonderation(FP_obtenirDernier(fileDePriorite))==9);
    CU_ASSERT_TRUE(ABR_obtenirOctet(FP_obtenirDernier(fileDePriorite)).octet==O_octet(58).octet);
    FP_supprimerDernier(&fileDePriorite);
}

void test_FP_longueur(void) {
    FP_FileDePriorite fileDePriorite;
    fileDePriorite = FP_fileDePriorite();
    ABR_ArbreDeHuffman arbreDeHuffman = ABR_arbreDeHuffman(O_octet(42),5);
    FP_ajouterElement(&fileDePriorite,arbreDeHuffman);
    CU_ASSERT_TRUE(FP_longueur(fileDePriorite)==1);
}

void test_FP_supprimerDernier(void) {
    FP_FileDePriorite fileDePriorite = FP_fileDePriorite();
    ABR_ArbreDeHuffman arbre = ABR_arbreDeHuffman(O_octet(42),5);
    FP_ajouterElement(&fileDePriorite,arbre);   
    FP_supprimerDernier(&fileDePriorite);
    CU_ASSERT_TRUE(FP_estVide(fileDePriorite));
}

int main(int argc, char** argv){
  CU_pSuite pSuite = NULL;

  /* initialisation du registre de tests */
  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  /* ajout d'une suite de test */
  pSuite = CU_add_suite("Tests : FileDePriorite", init_suite_success, clean_suite_success);
  if (NULL == pSuite) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* Ajout des tests à la suite de tests boite noire */
  if ((NULL == CU_add_test(pSuite, "FP_fileDePriorite", test_FP_fileDePriorite))
      || (NULL == CU_add_test(pSuite, "FP_ajouterElement", test_FP_ajouterElement))
      || (NULL == CU_add_test(pSuite, "FP_longueur", test_FP_longueur))
      || (NULL == CU_add_test(pSuite, "FP_supprimerDernier", test_FP_supprimerDernier))
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
