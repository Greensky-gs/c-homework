#include <stdio.h>
#include <stdlib.h>

typedef unsigned char tArrayType;
typedef tArrayType** tMat;

int calculateChar(int i, int base) {
    return (base + 1) + (i % 7);
}

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
            scanf("%hhu", &(*(*(matrice + i) + j)));
            // &matrice[i][j]
        }
    }

    printf("\x1b[0m");
    return matrice;
}
void libererMatrice(tMat * matrice) {
    free(*(matrice)[0]);
    free(*matrice);

    *matrice = NULL;
}

tMat triangle(int n) {
	tMat mat = matAllouer(n, n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j || j == 0) {
				mat[i][j] = 1;
			} else {
				mat[i][j] = 0;
			}
		}
	}

	for (int i = 1; i < n; i++) {
		for (int j = 1; j < i; j++) {
			mat[i][j] = mat[i - 1][j - 1] + mat[i-1][j];
		}
	}

	return mat;
}

void afficherMat(tMat matrice, int lignes, int colonnes) {
    for (int i = 0; i < lignes; i++) {
        printf("    ");
        for (int j = 0; j < colonnes; j++) {
            if (*(*(matrice + i) + j) != 0) printf("\x1b[%dm%4d\x1b[0m ", calculateChar(i + j, 90), *(*(matrice + i) + j));
        }
        printf("\n");
    }
}


int main() {
	int lignes;

	printf("Entrez le nombre de lignes à afficher : ");
	fflush(stdout);

	scanf("%d", &lignes);

	tMat t = triangle(lignes);
	afficherMat(t, lignes, lignes);

	libererMatrice(&t);
}
