#include "octet.h"

typedef struct 
{
    struct Noeud *gauche;
    struct Noeud *droite;
    Octet octet;
    unsigned int ponderation;
    
} Noeud;

typedef Noeud* ArbreDeHuffman;

// Constructeur 
ArbreDeHuffman arbreDeHuffman(Octet octet, unsigned int ponderation);
// Destructeur
void detruireArbre(ArbreDeHuffman arbre);
// Copie l'arbre 
ArbreDeHuffman copierArbre(ArbreDeHuffman arbre);
// Combine les deux arbres et retourne le nouvel arbre
ArbreDeHuffman combiner(abreDroit: ArbreDeHuffman, arbreGauche: ArbreDeHuffman);
unsigned int obtenirPonderation(ArbreDeHuffman arbre);
Octet obtenirOctet(ArbreDeHuffman arbre);
bool estUneFeuille(ArbreDeHuffman arbre);
ArbreDeHuffman obtenirFilsGauche(ArbreDeHuffman arbre);
ArbreDeHuffman obtenirFilsDroit(ArbreDeHuffman arbre);

