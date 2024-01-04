#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "octet.h"
#include "stats.h"
#include "arbre.h"
#include "table.h"
#include "fileDePriorite.h"
#include "codeBinaire.h"
#include "bit.h"

#define CLE 0x0B1213D2ul

Bit bit0 = ZERO;
Bit bit1 = UN;

void afficherTable(TDC_TableDeCodage table) {
    printf("Table de codage : \n");
    for (int i = 0; i < table.nbElements; i++) {
        printf("%c : ", O_obtenirNaturel8bits(table.table[i].octet));
        for (int j = 0; j < CB_obtenirLongueur(table.table[i].code); j++) {
            if (CB_obtenirIemeBit(table.table[i].code, j) == bit0) {
                printf("0");
            } else {
                printf("1");
            }
        }
        printf("\n");
    }
}

void afficherStats(ST_Statistiques stats) {
    printf("Statistiques : \n");
    for (int i = 0; i < 256; i++) {
        if (ST_obtenirOccurenceOctet(stats, O_octet(i)) != 0) {
            printf("%c : %ld\n", i, ST_obtenirOccurenceOctet(stats, O_octet(i)));
        }
    }
}

ST_Statistiques calculerStatistiques(char *nom) {
    FILE *fichier;

    fichier = fopen(nom, "rb");
    if (fichier == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier.\n");
        exit(EXIT_FAILURE);
    }

    ST_Statistiques stats = ST_statistiques();

    while (!feof(fichier)) {
        O_Octet octetLu = O_octet((Naturel8Bits)fgetc(fichier));
        ST_incrementerOccurenceOctet(octetLu, &stats);
    }

    fclose(fichier);

    return stats;
}


ABR_ArbreDeHuffman creerArbre(ST_Statistiques stats) {
    FP_FileDePriorite file = FP_fileDePriorite();

    for (int i = 0; i < 256; ++i) {
        if (ST_obtenirOccurenceOctet(stats, O_octet(i)) != 0) {
            FP_ajouterElement(&file, ABR_arbreDeHuffman(O_octet(i), ST_obtenirOccurenceOctet(stats, O_octet(i))));
        }
    }

    while (FP_longueur(file) > 1) {
        ABR_ArbreDeHuffman arbreGauche = FP_obtenirDernier(file);
        FP_supprimerDernier(&file);

        ABR_ArbreDeHuffman arbreDroit = FP_obtenirDernier(file);
        FP_supprimerDernier(&file);

        FP_ajouterElement(&file, ABR_combiner(arbreGauche, arbreDroit));
    }

    return FP_obtenirDernier(file);
}

void descendreArbre(ABR_ArbreDeHuffman arbre, CB_CodeBinaire code, TDC_TableDeCodage *table) {
    if (ABR_estUneFeuille(arbre)) {
        TDC_ajouterOctet(table, ABR_obtenirOctet(arbre), code);
    } else {
        CB_CodeBinaire codeTemp = code;
        CB_ajouterBit(&code, bit1);
        CB_ajouterBit(&codeTemp, bit0);
        descendreArbre(ABR_obtenirFilsDroit(arbre), code, table);
        descendreArbre(ABR_obtenirFilsGauche(arbre), codeTemp, table);
    }
}

TDC_TableDeCodage codage(ABR_ArbreDeHuffman arbre) {
    TDC_TableDeCodage table = TDC_tableDeCodage();

    if (ABR_estUneFeuille(arbre)) {
        TDC_ajouterOctet(&table, ABR_obtenirOctet(arbre), CB_codeBinaire(bit0));
    } else {
        descendreArbre(ABR_obtenirFilsDroit(arbre), CB_codeBinaire(bit1), &table);
        descendreArbre(ABR_obtenirFilsGauche(arbre), CB_codeBinaire(bit0), &table);
    }
    return table;
}

// Sera modifié par Dimitri
void ecrireCodeBinaire(FILE *fichier, CB_CodeBinaire codeBinaire) {
    // TODO: fix
    for (int i = 0; i < CB_obtenirLongueur(codeBinaire); i++) {
        if (CB_obtenirIemeBit(codeBinaire, i) == bit0) {
            fputc('0', fichier);
        } else {
            fputc('1', fichier);
        }
    }
}

void compresserFichier(char *nom, TDC_TableDeCodage table, ST_Statistiques stats) {
    FILE *fichierSource, *fichierDestination;
    fichierSource = fopen(nom, "rb");
    if (fichierSource == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier source.\n");
        exit(EXIT_FAILURE);
    }

    // Agrandir la taille du buffer du nom du fichier
    char *nomFichier = malloc(sizeof(char) * (strlen(nom) + 5));
    strcpy(nomFichier, nom);
    fichierDestination = fopen(strcat(nomFichier, ".huff"), "wb");
    if (fichierDestination == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier destination.\n");
        exit(EXIT_FAILURE);
    }
    
    long buffer = CLE;
    fwrite(&buffer, sizeof(long), 1, fichierDestination);
    buffer = ST_obtenirTotalOccurence(stats);
    fwrite(&buffer, sizeof(long), 1, fichierDestination);
    
    for (int i = 0; i < 256; i++) {
        buffer = ST_obtenirOccurenceOctet(stats, O_octet(i));
        fwrite(&buffer, sizeof(long), 1, fichierDestination);
    }

    while (!feof(fichierSource)) {
        O_Octet octetLu = O_octet((Naturel8Bits)fgetc(fichierSource));
        ecrireCodeBinaire(fichierDestination, TDC_obtenirCodeOctet(table, octetLu));
    }

    fclose(fichierSource);
    fclose(fichierDestination);
}

void compresser(char *nom) {
    ST_Statistiques stats = calculerStatistiques(nom);
    ABR_ArbreDeHuffman arbre = creerArbre(stats);
    TDC_TableDeCodage table = codage(arbre);
    afficherStats(stats);
    afficherTable(table);
    ABR_detruireArbre(arbre);
    compresserFichier(nom, table, stats);
}

ST_Statistiques lireStatistiques(FILE* fichier) {
    ST_Statistiques stats = ST_statistiques();
    long buffer;
    fread(&buffer, sizeof(long), 1, fichier);
    stats.nbOccurenceTotal = buffer;
    for (int i = 0; i < 256; i++) {
        fread(&buffer, sizeof(long), 1, fichier);
        ST_fixerOccurenceOctet(O_octet(i), buffer, &stats);
    }
    return stats;
}

int estUnFichierCompresse(FILE* fichier) {
    if (fichier == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier.\n");
        exit(EXIT_FAILURE);
    }
    
    long cle;
    fread(&cle, sizeof(long), 1, fichier);

    return cle == CLE;
}

void decompreserFichier(FILE* fichierSource, FILE* fichierDestination, TDC_TableDeCodage* table) {
    CB_CodeBinaire code;
    int resetCode = 1;
    char bitLu;
    while ((bitLu = fgetc(fichierSource)) != EOF) {
        if (TDC_codeBinairePresent(*table, code)) {
            O_Octet octet = TDC_obtenirOctetCode(*table, code);
            char buffer = (unsigned char)O_obtenirNaturel8bits(octet);
            fputc(&buffer, fichierDestination);
            resetCode = 1;
        } else {
            Bit bit = bit0;
            if (bitLu == '1') {
                bit = bit1;
            }
            code = CB_codeBinaire(bit);

            if (resetCode) {
                resetCode = 0;
            } else {
                CB_ajouterBit(&code, bit);
            }
        }
    }
}

void decompreser(FILE* fichierSource) {
    if (estUnFichierCompresse(fichierSource)) {
        FILE *fichierDestination;

        if (fichierSource == NULL) {
            fprintf(stderr, "Erreur lors de l'ouverture du fichier source.\n");
            exit(EXIT_FAILURE);
        }

        fichierDestination = fopen("decompresse.txt", "wb");

        // Lire les statistiques
        ST_Statistiques stats = lireStatistiques(fichierSource);
        
        // Créer la table de codage
        ABR_ArbreDeHuffman arbre = creerArbre(stats);
        TDC_TableDeCodage table = codage(arbre);
        afficherStats(stats);
        afficherTable(table);

        ABR_detruireArbre(arbre);
        decompreserFichier(fichierSource, fichierDestination, &table);

        fclose(fichierSource);
        fclose(fichierDestination);
    } else {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier. Le fichier entré n'a pas été compressé par le même programme.\n");
        exit(EXIT_FAILURE);
    }
}

int main(void) {
    compresser("test.txt");
    FILE* fichier = fopen("test.txt.huff", "rb");
    decompreser(fichier);
    return 0;
}
