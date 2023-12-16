#include <stdio.h>
#include "octet.h"
#include "stats.h"
#include "arbre.h"
#include "table.h"
#include "fileDePriorite.h"
#include "CodeBinaire.h"
#include "bit.h"

Bit bit0 = ZERO;
Bit bit1 = UN;

void compresser(char *nom) {
    ST_Statistiques stats = calculerStatistiques(nom);
    ABR_ArbreDeHuffman arbre = creerArbre(stats);
    TDC_TableDeCodage table = codage(arbre);
    compresserFichier(nom, table, stats);
}

ST_Statistiques calculerStatistiques(char *nom) {
    FILE *fichier;

    fichier = fopen(nom, "rb");
    if (fichier == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier.\n");
        exit(EXIT_FAILURE);
    }

    ST_Statistiques stats = ST_statistiques();

    O_Octet octetLu;
    while (fread(&octetLu, sizeof(O_Octet), 1, fichier) == 1) { //à modifier
        ST_incrementerOccurrenceOctet(stats, octetLu);
    }

    fclose(fichier);

    return stats;
}


ABR_ArbreDeHuffman creerArbre(ST_Statistiques stats) {
    FP_FileDePriorite file = FP_fileDePriorite();

    for (int i = 0; i < 256; ++i) {
        if (ST_obtenirOccurrenceOctet(stats, O_octet(i)) != 0) {
            FP_ajouterElement(ABR_creerArbreDeHuffman(O_octet(i), ST_obtenirOccurrenceElement(stats, O_octet(i))), file);
        }
    }

    while (longueur(file) > 1) {
        ABR_ArbreDeHuffman arbreGauche = FP_obtenirDernier(&file);
        FP_supprimerDernier(&file);

        ABR_ArbreDeHuffman arbreDroit = FP_obtenirDernier(&file);
        FP_supprimerDernier(&file);

        FP_ajouterElement(file, ABR_combiner(arbreGauche, arbreDroit));
    }

    return FP_obtenirDernier(&file);
}


TDC_TableDeCodage codage(ABR_ArbreDeHuffman arbre) {
    TDC_TableDeCodage table = TDC_tableDeCodage();

    if (ABR_estUneFeuille(arbre)) {
        FP_ajouterElement(table, ABR_obtenirOctet(arbre));
        TDC_assignerCodeElement(table, ABR_obtenirOctet(arbre), CB_codeBinaire(bit0)); //n'existe plus ?
    } else {
        descendreArbre(obtenirArbreDroit(arbre), CB_codeBinaire(bit1), &table);
        descendreArbre(obtenirArbreGauche(arbre), CB_codeBinaire(bit0), &table);
    }
    return table;
}


void descendreArbre(ABR_ArbreDeHuffman arbre, CB_CodeBinaire code, TDC_TableDeCodage *table) {
    if (ABR_estUneFeuille(arbre)) {
        FP_ajouterOctet(*table, ABR_obtenirOctet(arbre));
        TDC_assignerCodeElement(*table, ABR_obtenirOctet(arbre), code);
    } else {
        CB_CodeBinaire codeTemp = code;
        CB_ajouterBit(&code, bit1);
        CB_ajouterBit(&codeTemp, bit0);
        descendreArbre(ABR_obtenirArbreDroit(arbre), code, table);
        descendreArbre(ABR_obtenirArbreGauche(arbre), codeTemp, table);
    }
}


void compresserFichier(char *nom, TDC_TableDeCodage table, ST_Statistiques stats) {
    FILE *fichierSource, *fichierDestination;
    O_Octet octet;

    fichierSource = fopen(nom, "rb");
    if (fichierSource == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier source.\n");
        exit(EXIT_FAILURE);
    }

    // Tronquer le nom
    // ...

    fichierDestination = fopen(strcat(nom, ".zip"), "wb");
    if (fichierDestination == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier destination.\n");
        exit(EXIT_FAILURE);
    }

    // Écrire la clé et le nombre d'éléments
    fwrite(&CLE, sizeof(CLE), 1, fichierDestination);
    fwrite(&nbElement(stats), sizeof(nbElement(stats)), 1, fichierDestination);

    // Écrire les statistiques
    for (int i = 0; i < 256; i++) {
        O_Octet octet = O_octet(i);
        fwrite(&octet, sizeof(octet), 1, fichierDestination);
        fwrite(&ABR_obtenirOccurenceElement(octet), sizeof(obtenirOccurenceElement(octet)), 1, fichierDestination);
    }

    // Écrire le code binaire du fichier source
    while (!feof(fichierSource)) {
        octet = lireOctet(fichierSource);
        ecrireCodeBinaire(fichierDestination, obtenirCodeElement(table, octet));
    }

    fclose(fichierSource);
    fclose(fichierDestination);
}


void ecrireCodeBinaire(FILE *fichier, CB_CodeBinaire codeBinaire) {
    for (int i = 0; i < obtenirLongueur(codeBinaire); i++) {
        if (CB_obtenirIemeBit(codeBinaire, i) == bit0) {
            fputc('0', fichier);
        } else {
            fputc('1', fichier);
        }
    }
}
