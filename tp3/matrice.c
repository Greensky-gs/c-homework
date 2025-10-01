#include <stdio.h>
#include <math.h>

#define EPSILON 10e-10

int main() {
    int ordre;
    printf("Entrez l'ordre de la matrice (max 10) : ");
    fflush(stdout);

    scanf("%d", &ordre);
    if (ordre <= 0 || ordre > 10) {
        printf("Ordre invalide (entre 1 et 10)\n");
        return 1;
    }

    double matrice[10][10];

    for (int i = 0; i < ordre; i++) {
        printf("Ligne %d : ", i + 1);
        fflush(stdout);

        for (int j = 0; j < ordre; j++) {
            scanf("%lf", &matrice[i][j]);
        }
    }

    int i = 0;
    int j = 0;
    int est_symetrique = 1;

    while (est_symetrique && i < ordre) {
        j = 0;
        while (est_symetrique && j < ordre) {
            // if (matrice[i][j] != matrice[j][i]) { // Condition question 1
            //     est_symetrique = 0;
            // }
            if (fabs(matrice[i][j] - matrice[j][i]) >= EPSILON) {
                est_symetrique = 0;
            }
            j++;
        }
        i++;
    }

    if (est_symetrique) {
        printf("Cette matrice est symetrique\n");
    } else {
        printf("Cette matrice n'est pas symetrique\n");
    }

    return 0;
}