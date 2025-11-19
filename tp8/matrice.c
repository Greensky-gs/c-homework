#include <stdio.h>
#include <stdlib.h>
#include "./matrice.h"

typedef int tArrayType;
typedef tArrayType** tMat;

tMat matAllouer(int lignes, int colonnes) {
    tArrayType * elements = malloc(lignes * colonnes * sizeof(tArrayType));
    tArrayType ** ptrs = malloc(lignes * sizeof(tArrayType *));

    if (elements == NULL || ptrs == NULL) return NULL;

    for (int i = 0; i < lignes; i++) {
        *(ptrs + i) = (elements + i * colonnes);
    }

    return ptrs;
}
tMat lireMat(int * lignes, int * colonnes) {
    printf("Entrez le nombre de lignes :  \x1b[96m");
    fflush(stdout);
    scanf("%d", lignes);

    printf("\x1b[0mEntrez le nombre de colonnes : \x1b[96m");
    fflush(stdout);
    scanf("%d", colonnes);

    tMat matrice = matAllouer(*lignes, *colonnes);

    printf("\x1b[0mEntrez vos valeurs : \x1b[96m");
    fflush(stdout);

    for (int i = 0; i < *lignes; i++) {
        for (int j = 0; j < *colonnes; j++) {
            scanf("%d", &(*(*(matrice + i) + j)));
            // &matrice[i][j]
        }
    }

    printf("\x1b[0m");
    return matrice;
}
static int calculateChar(int i, int base) {
    return (base + 1) + (i % 7);
}
void afficherMat(tMat matrice, int lignes, int colonnes) {
    printf("\x1b[33m[\n");

    for (int i = 0; i < lignes; i++) {
        printf("    ");
        for (int j = 0; j < colonnes; j++) {
            printf("\x1b[%dm%3d\x1b[0m ", calculateChar(i + j, 90), *(*(matrice + i) + j));
        }
        printf("\n");
    }
    printf("\x1b[33m]\x1b[0m\n");
}
tMat matCopier(tMat matrice, int lignes, int colonnes) {
    tMat copie = matAllouer(lignes, colonnes);

    for (int i = 0; i < lignes; i++) {
        for (int j = 0; j < colonnes; j++) {
            *(*(copie + i) + j) = *(*(matrice + i) + j);
        }
    }
    return copie;
}
void libererMatrice(tMat * matrice) {
    free(*(matrice)[0]);
    free(*matrice);

    *matrice = NULL;
}
