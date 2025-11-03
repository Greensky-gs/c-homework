#include <stdlib.h>
#include <stdio.h>

typedef unsigned char ** tMatrice;

tMatrice matAllouer(int nbLig, int nbCol) {
    unsigned char * elements = malloc(nbLig * nbCol * sizeof(unsigned char));
    unsigned char ** lignes = malloc(nbLig * sizeof(unsigned char *));

    for (int i = 0; i < nbLig; i++) {
        lignes[i] = elements + i * nbCol;
    }

    return lignes;
}

tMatrice matLire(int *pLig, int *pCol) {
    printf("Le nombre de lignes ? ");
    fflush(stdout);
    scanf("%d", pLig);
    printf("Le nombre de colonnes ? ");
    fflush(stdout);
    scanf("%d", pCol);

    tMatrice mat = matAllouer(*pLig, *pCol);

    int i, j;
    for (i = 0; i < *pLig; i++) {
        for (j = 0; j < *pCol; j++) {
            printf("Element [%d][%d] ? ", i, j);
            fflush(stdout);
            scanf("%hhu", &mat[i][j]);
        }
    }
    printf("\n");

    return mat;
}
void matAfficher(tMatrice mat, int lig, int col) {
    printf("(\n");
    for (int i = 0; i < lig; i++) {
        printf("       ");
        for (int j = 0; j < col; j++) {
            printf("%hhu ", mat[i][j]);
        }
        printf("\n");
    }
    printf(")\n");
}
void matLiberer(tMatrice * pmat, int lig) {
    for (int i = 0; i < lig; i++) {
        free((*pmat)[i]);
    }
    free(*pmat);
    *pmat = NULL;
}

int main() {
    int a, b;
    tMatrice mat = matLire(&a, &b);

    matAfficher(mat, a, b);

    matLiberer(&mat, a);
    return 0;
}