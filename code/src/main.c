#include <stdio.h>
#include "octet.h"
#include "Stats.h"
#include "arbre.h"
#include "Table.h"
#include "FileDePriorite.h"
#include "CodeBinaire.h"
#include "bit.h"

Bit bit0 = ZERO;
Bit bit1 = UN;

void compresser(char *nom) {
    Statistiques stats = calculerStatistiques(nom);
    ArbreDeHuffman arbre = creerArbre(stats);
    TableDeCodage table = codage(arbre);
    compresserFichier(nom, table, stats);
}

Statistiques calculerStatistiques(char *nom) {
    FILE *fichier;

    fichier = fopen(nom, "rb");
    if (fichier == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier.\n");
        exit(EXIT_FAILURE);
    }

    Statistiques stats = ST_statistiques();

    Octet octetLu;
    while (fread(&octetLu, sizeof(Octet), 1, fichier) == 1) { //à modifier
        ST_incrementerOccurrenceOctet(stats, octetLu);
    }

    fclose(fichier);

    return stats;
}


ArbreDeHuffman creerArbre(Statistiques stats) {
    FileDePriorite file = FP_fileDePriorite();

    for (int i = 0; i < 256; ++i) {
        if (ST_obtenirOccurrenceOctet(stats, O_octet(i)) != 0) {
            FP_ajouterElement(ABR_creerArbreDeHuffman(O_octet(i), ST_obtenirOccurrenceElement(stats, O_octet(i))), file);
        }
    }

    while (longueur(file) > 1) {
        ArbreDeHuffman arbreGauche = FP_obtenirDernier(file);
        FP_supprimerDernier(file);

        ArbreDeHuffman arbreDroit = FP_obtenirDernier(file);
        FP_supprimerDernier(file);

        FP_ajouterElement(file, ABR_combiner(arbreGauche, arbreDroit));
    }

    return FP_obtenirDernier(file);
}


TableDeCodage codage(ArbreDeHuffman arbre) {
    TableDeCodage table = TDC_tableDeCodage();

    if (ABR_estUneFeuille(arbre)) {
        FP_ajouterElement(table, ABR_obtenirOctet(arbre));
        TDC_assignerCodeElement(table, ABR_obtenirOctet(arbre), CB_codeBinaire(bit0)); //n'existe plus ?
    } else {
        descendreArbre(obtenirArbreDroit(arbre), CB_codeBinaire(bit1), &table);
        descendreArbre(obtenirArbreGauche(arbre), CB_codeBinaire(bit0), &table);
    }
    return table;
}


void descendreArbre(ArbreDeHuffman arbre, CodeBinaire code, TableDeCodage *table) {
    if (ABR_estUneFeuille(arbre)) {
        FP_ajouterOctet(*table, ABR_obtenirOctet(arbre));
        TDC_assignerCodeElement(*table, ABR_obtenirOctet(arbre), code);
    } else {
        CodeBinaire codeTemp = code;
        CB_ajouterBit(code, bit1);
        CB_ajouterBit(codeTemp, bit0);
        descendreArbre(ABR_obtenirArbreDroit(arbre), code, table);
        descendreArbre(ABR_obtenirArbreGauche(arbre), codeTemp, table);
    }
}


void compresserFichier(char *nom, TableDeCodage table, Statistiques stats) {
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


void ecrireCodeBinaire(FILE *fichier, CodeBinaire codeBinaire) {
    for (int i = 0; i < obtenirLongueur(codeBinaire); i++) {
        if (O_obtenirIemeBit(codeBinaire, i) == bit0) {
            fputc('0', fichier);
        } else {
            fputc('1', fichier);
        }
    }
}
