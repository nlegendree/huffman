#include "octet.h"

void compresser(char *nom) {
    // Calcul des statistiques
    Statistiques stats = calculerStatistiques(nom);

    // Création de l'arbre de Huffman
    ArbreDeHuffman arbre = creerArbre(stats);

    // Création de la table de codage
    TableDeCodage table = codage(arbre);

    // Compression du fichier
    compresserFichier(nom, table, stats);
}


Statistiques calculerStatistiques(char *nom) {
    FILE *fichier;
    Statistiques stats;

    fichier = fopen(nom, "rb");
    if (fichier == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier.\n");
        exit(EXIT_FAILURE);
    }

    stats = creerStatistiques();

    Octet octetLu;
    while (fread(&octetLu, sizeof(Octet), 1, fichier) == 1) {
        incrementerOccurrenceElement(stats, octetLu);
    }

    fclose(fichier);

    return stats;
}


ArbreDeHuffman creerArbre(Statistiques stats) {
    FileDePriorite file = fileDePrioriteVide();

    for (int i = 0; i < 256; ++i) {
        if (obtenirOccurrenceElement(octet(i), stats) != 0) {
            ajouterElement(file, creerArbreDeHuffman(octet(i), obtenirOccurrenceElement(octet(i), stats)));
        }
    }

    while (longueur(file) > 1) {
        ArbreDeHuffman arbreGauche = obtenirDernier(file);
        supprimerDernier(file);

        ArbreDeHuffman arbreDroit = obtenirDernier(file);
        supprimerDernier(file);

        ajouterElement(file, combiner(arbreGauche, arbreDroit));
    }

    return obtenirDernier(file);
}


TableDeCodage codage(ArbreDeHuffman arbre) {
    TableDeCodage table = tableDeCodage();

    if (estUneFeuille(arbre)) {
        ajouterElement(table, obtenirElement(arbre));
        assignerCodeElement(table, obtenirElement(arbre), codeBinaire(Bit0));
    } else {
        descendreArbre(obtenirArbreDroit(arbre), codeBinaire(Bit1), &table);
        descendreArbre(obtenirArbreGauche(arbre), codeBinaire(Bit0), &table);
    }

    return table;
}


void descendreArbre(ArbreDeHuffman arbre, CodeBinaire code, TableDeCodage *table) {
    if (estUneFeuille(arbre)) {
        ajouterElement(*table, obtenirElement(arbre));
        assignerCodeElement(*table, obtenirElement(arbre), code);
    } else {
        CodeBinaire codeTemp = code;
        ajouterBit(code, Bit1);
        ajouterBit(codeTemp, Bit0);
        descendreArbre(obtenirArbreDroit(arbre), code, table);
        descendreArbre(obtenirArbreGauche(arbre), codeTemp, table);
    }
}


void compresserFichier(char *nom, TableDeCodage table, Statistiques stats) {
    FILE *fichierSource, *fichierDestination;
    Octet octet;

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
        octet = octet(i);
        fwrite(&octet, sizeof(octet), 1, fichierDestination);
        fwrite(&obtenirOccurenceElement(octet), sizeof(obtenirOccurenceElement(octet)), 1, fichierDestination);
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
        if (obtenirIemeBit(codeBinaire, i) == Bit0) {
            fputc('0', fichier);
        } else {
            fputc('1', fichier);
        }
    }
}


int main() {
    return 0;
}
