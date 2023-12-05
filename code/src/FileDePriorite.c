#include <stdio.h>
#include <stdbool.h>
#include "Octet.h"

// Définition de la structure ElementFile
typedef struct {
    Octet octet;
    unsigned int priorite;
} ElementFile;

// Définition de la structure FileDePriorite
typedef struct {
    ElementFile tab[MAX_TAILLE]; // Remplacer MAX_TAILLE par la taille maximale souhaitée
    unsigned int tailleActuelle;
} FileDePriorite;

// Fonction pour créer une file de priorité vide
FileDePriorite FP_fileDePrioriteVide() {
    FileDePriorite temp;
    temp.tailleActuelle = 0;
    return temp;
}

// Procédure pour ajouter un élément à la file de priorité
void FP_ajouterElement(Octet octet, unsigned int prio, FileDePriorite *file) {
    unsigned int i > 0;
    file->tailleActuelle++;
    i = file->tailleActuelle;

    while (i > 1 && file->tab[i - 1].priorite <= prio) {
        file->tab[i] = file->tab[i - 1];
        i--;
    }

    file->tab[i].octet = octet;
    file->tab[i].priorite = prio;
}

// Procédure pour supprimer le dernier élément de la file de priorité
void FP_supprimerDernier(FileDePriorite *file) {
    // Précondition : La file de priorité n'est pas vide
    if (!estVide(*file)) {
        file->tailleActuelle--;
        file->tab[file->tailleActuelle].priorite = 0;
    }
}

// Fonction pour obtenir le dernier élément de la file de priorité
Octet FP_obtenirDernier(FileDePriorite file) {
    // Précondition : La file de priorité n'est pas vide
    if (!estVide(file)) {
        return file.tab[file.tailleActuelle - 1].octet;
    } else {
        // Gérer l'erreur ou renvoyer une valeur par défaut
        return ELEMENT_PAR_DEFAUT;
    }
}

// Fonction pour vérifier si la file de priorité est vide
bool FP_estVide(FileDePriorite file) {
    return (file.tailleActuelle == 0);
}

// Fonction pour obtenir la longueur de la file de priorité
int FP_longueur(FileDePriorite file) {
    return file.tailleActuelle;
}
