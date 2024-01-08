/**
 * @file main.c
 * @brief Programme principal du projet Huffman
 * @version 1.0
 *
 */
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
#define couleur_verte "\x1b[32m"
#define couleur_rouge "\x1b[31m"
#define couleur_bleu "\x1b[34m"
#define couleur_jaune "\x1b[33m"

#define CLE 0x0B1213D2ul

Bit bit0 = ZERO;
Bit bit1 = UN;

/**
 * \fn void afficherTable(TDC_TableDeCodage table)
 * \brief Procédure qui affiche la table de codage correspondant au fichier
 *
 * \param table : table de codage à afficher
 */
void afficherTable(TDC_TableDeCodage table)
{
    printf("Table de codage : \n");
    for (int i = 0; i < table.nbElements; i++)
    {
        printf("%c : ", O_obtenirNaturel8bits(table.table[i].octet));
        for (int j = 0; j < CB_obtenirLongueur(table.table[i].code); j++)
        {
            if (CB_obtenirIemeBit(table.table[i].code, j) == bit0)
            {
                printf("0");
            }
            else
            {
                printf("1");
            }
        }
        printf("\n");
    }
}

/**
 * \fn void afficherStats(ST_Statistiques stats)
 * \brief Procédure qui affiche les statistiques correspondantes au fichier
 *
 * \param stats : statistiques à afficher
 */
void afficherStats(ST_Statistiques stats)
{
    printf("Statistiques : \n");
    for (int i = 0; i < 256; i++)
    {
        if (ST_obtenirOccurenceOctet(stats, O_octet(i)) != 0)
        {
            printf("%c : %ld\n", i, ST_obtenirOccurenceOctet(stats, O_octet(i)));
        }
    }
}

/**
 * \fn void CB_afficherCodeBinaire(CB_CodeBinaire code)
 * \brief Procédure qui affiche les codes binaires correspondants au fichier
 *
 * \param code : codes binaires à afficher
 */
void CB_afficherCodeBinaire(CB_CodeBinaire code)
{
    for (int i = 0; i < CB_obtenirLongueur(code); i++)
    {
        if (CB_obtenirIemeBit(code, i) == bit0)
        {
            printf("0");
        }
        else
        {
            printf("1");
        }
    }
    printf("\n");
}

/**
 * \fn ST_Statistiques calculerStatistiques(char *nom)
 * \brief Fonction qui calcule les statistiques du fichier
 *
 * \param nom : nom du fichier
 * \return ST_Statistiques
 */
ST_Statistiques calculerStatistiques(char *nom)
{
    FILE *fichier;

    fichier = fopen(nom, "rb");
    if (fichier == NULL)
    {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier.\n");
        exit(EXIT_FAILURE);
    }

    ST_Statistiques stats = ST_statistiques();

    while (!feof(fichier))
    {
        O_Octet octetLu = O_octet((Naturel8Bits)fgetc(fichier));
        ST_incrementerOccurenceOctet(octetLu, &stats);
    }

    fclose(fichier);

    return stats;
}

/**
 * \fn ABR_ArbreDeHuffman creerArbre(ST_Statistiques stats)
 * \brief Fonction qui crée un arbre de Huffman à partir des statistiques
 *
 * \param stats : statistiques pour créer l'arbre d'Huffman
 * \return ABR_ArbreDeHuffman
 */
ABR_ArbreDeHuffman creerArbre(ST_Statistiques stats)
{
    FP_FileDePriorite file = FP_fileDePriorite();

    for (int i = 0; i < 256; ++i)
    {
        if (ST_obtenirOccurenceOctet(stats, O_octet(i)) != 0)
        {
            FP_ajouterElement(&file, ABR_arbreDeHuffman(O_octet(i), ST_obtenirOccurenceOctet(stats, O_octet(i))));
        }
    }

    while (FP_longueur(file) > 1)
    {
        ABR_ArbreDeHuffman arbreGauche = FP_obtenirDernier(file);
        FP_supprimerDernier(&file);

        ABR_ArbreDeHuffman arbreDroit = FP_obtenirDernier(file);
        FP_supprimerDernier(&file);

        FP_ajouterElement(&file, ABR_combiner(arbreGauche, arbreDroit));
    }

    return FP_obtenirDernier(file);
}

/**
 * \fn void descendreArbre(ABR_ArbreDeHuffman arbre, CB_CodeBinaire code, TDC_TableDeCodage *table)
 * \brief Procédure qui descend un arbre de Huffman
 *
 * \param arbre : arbre de Huffman à descendre
 * \param code :
 * \param table :
 * \return ABR_ArbreDeHuffman
 */
void descendreArbre(ABR_ArbreDeHuffman arbre, CB_CodeBinaire code, TDC_TableDeCodage *table)
{
    if (ABR_estUneFeuille(arbre))
    {
        TDC_ajouterOctet(table, ABR_obtenirOctet(arbre), code);
    }
    else
    {
        CB_CodeBinaire codeTemp = code;
        CB_ajouterBit(&code, bit1);
        CB_ajouterBit(&codeTemp, bit0);
        descendreArbre(ABR_obtenirFilsDroit(arbre), code, table);
        descendreArbre(ABR_obtenirFilsGauche(arbre), codeTemp, table);
    }
}

/**
 * \fn TDC_TableDeCodage codage(ABR_ArbreDeHuffman arbre)
 * \brief Fonction qui crée la table de codage d'un arbre de Huffman
 *
 * \param arbre : arbre dont on veut la table de codage
 * \return TDC_TableDeCodage
 */
TDC_TableDeCodage codage(ABR_ArbreDeHuffman arbre)
{
    TDC_TableDeCodage table = TDC_tableDeCodage();

    if (ABR_estUneFeuille(arbre))
    {
        TDC_ajouterOctet(&table, ABR_obtenirOctet(arbre), CB_codeBinaire(bit0));
    }
    else
    {
        descendreArbre(ABR_obtenirFilsDroit(arbre), CB_codeBinaire(bit1), &table);
        descendreArbre(ABR_obtenirFilsGauche(arbre), CB_codeBinaire(bit0), &table);
    }
    return table;
}

/**
 * \fn void compresserFichier(char *nom, TDC_TableDeCodage table, ST_Statistiques stats)
 * \brief Procédure qui compresse le fichier
 *
 * \param nom : nom du fichier à compresser
 * \param table : table de codage pour la compression
 * \param stats : statistiques pour la compression
 * \return FILE
 */
void compresserFichier(char *nom, TDC_TableDeCodage table, ST_Statistiques stats)
{
    FILE *fichierSource, *fichierDestination;
    fichierSource = fopen(nom, "rb");
    if (fichierSource == NULL)
    {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier source.\n");
        exit(EXIT_FAILURE);
    }

    // Agrandir la taille du buffer du nom du fichier
    char *nomFichier = malloc(sizeof(char) * (strlen(nom) + 5));
    strcpy(nomFichier, nom);
    fichierDestination = fopen(strcat(nomFichier, ".huff"), "wb");
    if (fichierDestination == NULL)
    {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier destination.\n");
        exit(EXIT_FAILURE);
    }

    long buffer = CLE;
    fwrite(&buffer, sizeof(long), 1, fichierDestination);
    buffer = ST_obtenirTotalOccurence(stats);
    fwrite(&buffer, sizeof(long), 1, fichierDestination);

    for (int i = 0; i < 256; i++)
    {
        buffer = ST_obtenirOccurenceOctet(stats, O_octet(i));
        fwrite(&buffer, sizeof(long), 1, fichierDestination);
    }
    char codeBuffer = 0;
    char codeBufferSize = 8;
    while (!feof(fichierSource))
    {
        O_Octet octetLu = O_octet((Naturel8Bits)fgetc(fichierSource));
        CB_CodeBinaire code = TDC_obtenirCodeOctet(table, octetLu);
        for (int i = 0; i < CB_obtenirLongueur(code); i++)
        {
            if (CB_obtenirIemeBit(code, i) == bit0)
            {
                codeBuffer = codeBuffer << 1;
            }
            else
            {
                codeBuffer = (codeBuffer << 1) | 1;
            }
            codeBufferSize--;
            if (codeBufferSize <= 0)
            {
                fputc(codeBuffer, fichierDestination);
                codeBuffer = 0;
                codeBufferSize = 8;
            }
        }
    }

    fclose(fichierSource);
    fclose(fichierDestination);
}

/**
 * \fn void compresser(char *nom)
 * \brief Procédure qui compresse le fichier
 *
 * \param nom : nom du fichier à compresser
 * \return FILE
 */
void compresser(char *nom)
{
    ST_Statistiques stats = calculerStatistiques(nom);
    ABR_ArbreDeHuffman arbre = creerArbre(stats);
    TDC_TableDeCodage table = codage(arbre);

    ABR_detruireArbre(arbre);
    compresserFichier(nom, table, stats);
}

/// @brief Lit les statistiques d'un fichier compressé par le programme
/// @param fichier fichier à lire
/// @return les statistiques du fichier
ST_Statistiques lireStatistiques(FILE *fichier)
{
    ST_Statistiques stats = ST_statistiques();
    long buffer;
    fread(&buffer, sizeof(long), 1, fichier);
    stats.nbOccurenceTotal = buffer;
    for (int i = 0; i < 256; i++)
    {
        fread(&buffer, sizeof(long), 1, fichier);
        ST_fixerOccurenceOctet(O_octet(i), buffer, &stats);
    }
    return stats;
}

/// @brief  Vérifie si le fichier est compressé par le programme
/// @param fichier fichier à vérifier
/// @return 1 si le fichier est compressé par le programme, 0 sinon
int estUnFichierCompresse(FILE *fichier)
{
    if (fichier == NULL)
    {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier.\n");
        exit(EXIT_FAILURE);
    }

    long cle;
    fread(&cle, sizeof(long), 1, fichier);

    return cle == CLE;
}

/// @brief Décompresse un fichier compressé par le programme
/// @param fichierSource fichier à décompresser
/// @param fichierDestination fichier décompressé
/// @param table table de codage
void decompreserFichier(FILE *fichierSource, FILE *fichierDestination, ABR_ArbreDeHuffman arbre)
{
    CB_CodeBinaire code;
    int resetCode = 1;
    int ocetLu;

    ABR_ArbreDeHuffman noeudActuel = arbre;
    while ((ocetLu = fgetc(fichierSource)) != EOF)
    {
        for (int i = 0; i < 8; i++)
        {
            Bit bit = bit0;
            if (ocetLu & 0x80)
            {
                bit = bit1;
            }
            if (resetCode)
            {
                code = CB_codeBinaire(bit);
                resetCode = 0;
            }
            else
            {
                CB_ajouterBit(&code, bit);
            }
            ocetLu = ocetLu << 1;

            if (bit == bit0)
            {
                noeudActuel = ABR_obtenirFilsGauche(noeudActuel);
            }
            else
            {
                noeudActuel = ABR_obtenirFilsDroit(noeudActuel);
            }
            if (ABR_estUneFeuille(noeudActuel))
            {
                O_Octet octet = ABR_obtenirOctet(noeudActuel);
                char buffer = (char)O_obtenirNaturel8bits(octet);
                fputc(buffer, fichierDestination);
                resetCode = 1;
                noeudActuel = arbre;
            }
        }
    }
}

void decompreser(char *nomFichier)
{
    FILE *fichierSource = fopen(nomFichier, "rb");
    if (estUnFichierCompresse(fichierSource))
    {
        FILE *fichierDestination = NULL;

        if (fichierSource == NULL)
        {
            fprintf(stderr, "Erreur lors de l'ouverture du fichier source.\n");
            exit(EXIT_FAILURE);
        }

        // On retire les 5 derniers caractères du nom du fichier
        char *nomFichierSansExtension = malloc(sizeof(char) * (strlen(nomFichier) - 4));
        strncpy(nomFichierSansExtension, nomFichier, strlen(nomFichier) - 5);
        nomFichierSansExtension[strlen(nomFichier) - 5] = '\0'; // On ajoute le caractère de fin de chaine

        fichierDestination = fopen(nomFichierSansExtension, "wb");
        if (fichierDestination == NULL)
        {
            fprintf(stderr, "Erreur lors de l'ouverture du fichier destination.\n");
            fclose(fichierSource);
            free(nomFichierSansExtension);
            exit(EXIT_FAILURE);
        }

        // Lire les statistiques
        ST_Statistiques stats = lireStatistiques(fichierSource);
        ABR_ArbreDeHuffman arbre = creerArbre(stats);

        decompreserFichier(fichierSource, fichierDestination, arbre);

        ABR_detruireArbre(arbre);
        fclose(fichierDestination);
        free(nomFichierSansExtension);
    }
    else
    {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier. Le fichier entré n'a pas été compressé par le même programme.\n");
        exit(EXIT_FAILURE);
    }
    fclose(fichierSource);
}

/// @brief Procedure qui affiche l'interface homme machine, avec les instructions à faire.
/// @param argc argument compteur
/// @param argv argument pour le terminal pour le fichier a selectionner et le choix entre compresser et decompresser.
void afficherIHM(int argc, char *argv[])
{
    printf("bienvenue !!!\n");
    printf("pour compiler, veuillez taper : ./huffman c nom_du_fichier\n");
    printf("pour decompiler, veuillez taper : ./huffman d nom_du_fichier\n");

    if (argc != 3) {
        printf("commande incorrect, nombre d'argument, pas respecté \n");
        exit(EXIT_FAILURE);
       
        
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
            exit(EXIT_FAILURE);
    }
}




int main(int argc, char *argv[])
{
    afficherIHM(argc,argv);

    return 0;
}
