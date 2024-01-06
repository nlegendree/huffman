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

// couleurs pour le terminal
#define couleur_verte   "\x1b[32m" 
#define couleur_rouge    "\x1b[31m"
#define couleur_bleu    "\x1b[34m"
#define couleur_jaune   "\x1b[33m"

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

void CB_afficherCodeBinaire(CB_CodeBinaire code) {
    for (int i = 0; i < CB_obtenirLongueur(code); i++) {
        if (CB_obtenirIemeBit(code, i) == bit0) {
            printf("0");
        } else {
            printf("1");
        }
    }
    printf("\n");
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
    char codeBuffer = 0;
    char codeBufferSize = 8;
    while (!feof(fichierSource)) {
        O_Octet octetLu = O_octet((Naturel8Bits)fgetc(fichierSource));
        CB_CodeBinaire code = TDC_obtenirCodeOctet(table, octetLu);
        for (int i = 0; i < CB_obtenirLongueur(code); i++) {
            if (CB_obtenirIemeBit(code, i) == bit0) {
                codeBuffer = codeBuffer << 1;
            } else {
                codeBuffer = (codeBuffer << 1) | 1;
            }
            codeBufferSize--;
            if (codeBufferSize <= 0) {
                fputc(codeBuffer, fichierDestination);
                codeBuffer = 0;
                codeBufferSize = 8;
            }
        }

    }

    fclose(fichierSource);
    fclose(fichierDestination);
}

void compresser(char *nom) {
    ST_Statistiques stats = calculerStatistiques(nom);
    ABR_ArbreDeHuffman arbre = creerArbre(stats);
    TDC_TableDeCodage table = codage(arbre);

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
        for (int i = 0; i < 8; i++) {
            Bit bit = bit0;
            if (bitLu & 0x80) {
                bit = bit1;
            }
            if (resetCode) {
                code = CB_codeBinaire(bit);
                resetCode = 0;
            } else {
                CB_ajouterBit(&code, bit);
            }
            bitLu = bitLu << 1;
            if (TDC_codeBinairePresent(*table, code)) {
                O_Octet octet = TDC_obtenirOctetCode(*table, code);
                char buffer = (char)O_obtenirNaturel8bits(octet);
                fputc(buffer, fichierDestination);
                resetCode = 1;
            }  
        }
    }
}

void decompreser(char* nomFichier) {
    FILE *fichierSource = fopen(nomFichier, "rb");
    if (estUnFichierCompresse(fichierSource)) {
        FILE *fichierDestination;

        if (fichierSource == NULL) {
            fprintf(stderr, "Erreur lors de l'ouverture du fichier source.\n");
            exit(EXIT_FAILURE);
        }

        // On retire les 5 derniers caractères du nom du fichier
        char *nomFichierSansExtension = malloc(sizeof(char) * (strlen(nomFichier) - 5));
        strncpy(nomFichierSansExtension, nomFichier, strlen(nomFichier) - 5);
        fichierDestination = fopen(nomFichierSansExtension, "wb");

        // Lire les statistiques
        ST_Statistiques stats = lireStatistiques(fichierSource);
        
        // Créer la table de codage
        ABR_ArbreDeHuffman arbre = creerArbre(stats);
        TDC_TableDeCodage table = codage(arbre);

        ABR_detruireArbre(arbre);
        decompreserFichier(fichierSource, fichierDestination, &table);

        fclose(fichierSource);
        fclose(fichierDestination);
    } else {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier. Le fichier entré n'a pas été compressé par le même programme.\n");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    printf("bienvenue !!!\n");
    printf("pour compiler, veuillez taper : ./huffman c nom_du_fichier\n");
    printf("pour decompiler, veuillez taper : ./huffman d nom_du_fichier\n");

    if (argc != 3) {
        printf("commande incorrect, nombre d'argument, pas respecté \n");
       
        return 1;  
    }

    // recupère le choix de l'utilisateur entre c et d
    char choix = argv[1][0];  
    char *nom_fichier = argv[2];

    switch (choix) {
        case 'c':
            printf("compression du fichier %s.\n", nom_fichier);
            compresser(nom_fichier);
            break;
        case 'd':
            printf("decompression du fichier %s.\n", nom_fichier);
            decompreser(nom_fichier);
            break;
        default:
            printf("commande incorrecte, il faut choisir entre 'c' ou 'd'.\n");
            return 1; 
    }

    return 0;
}
