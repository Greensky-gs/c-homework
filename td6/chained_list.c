#include <stdio.h>
#include <stdlib.h>

struct Cellule {
    int entier;
    struct Cellule * suivant;
};
typedef struct Cellule tCellule;

tCellule * creerCellule(int entier) {
    tCellule * cellule = malloc(sizeof(tCellule));
    cellule->entier = entier;
    cellule->suivant = NULL;

    return cellule;
}

tCellule * ajouterEnTete(tCellule * ptr, int entier) {
    tCellule * nouveau = creerCellule(entier);

    nouveau->suivant = ptr;
    return nouveau;
}

tCellule * celluleDeQueue(tCellule * ptr) {
    if (ptr->suivant == NULL) {
        return ptr;
    }
    return celluleDeQueue(ptr->suivant);
}

tCellule * ajouterEnQueue(tCellule * ptr, int entier) {
    tCellule * nouveau = creerCellule(entier);
    tCellule * queue = celluleDeQueue(ptr);

    queue->suivant = nouveau;
    return ptr;
}

void affichageRecursif(tCellule * ptr) {
    printf(" %d", ptr->entier);

    if (ptr->suivant != NULL) {
        printf(",");
        affichageRecursif(ptr->suivant);
    }
}
void afficherList(tCellule * ptr) {
    printf("[");
    affichageRecursif(ptr);
    printf("]");
}

void supprimerList(tCellule * ptr) {
    tCellule * courant = ptr;

    while (courant != NULL) {
        tCellule * suivant = courant->suivant;
        free(courant);
        courant = suivant;
    }
}

int main() {
    tCellule * liste = creerCellule(0);

    for (int i = 1; i <= 8; i++) {
        liste = ajouterEnQueue(liste, i);
    }
    liste = ajouterEnTete(liste, -1);
    afficherList(liste);

    supprimerList(liste);
}