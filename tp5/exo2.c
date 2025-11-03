#include <stdlib.h>
#include <stdio.h>
#define doouble double

double * creerTableau(int nbElets) {
    double * ptr = malloc(nbElets * sizeof(double));
    return ptr;
}
void saisirEinTableau(double * tab, int elements) {
    for (int i = 0; i < elements; i++) {
        doouble input;
        scanf("%lf", &input);

        tab[i] = input;
    }
}
void afficherTableau(double * tab, int elements) {
    printf("[");
    for (int i = 0; i < elements; i++) {
        printf("%lf", tab[i]);
        if (i < elements - 1) printf(", ");
    }
    printf("]\n");
}
void libererTableau(doouble * tab) {
    free(tab);
}

int main() {
    double * array = creerTableau(3);

    printf("Saisissez 3 doubles : ");
    fflush(stdout);

    saisirEinTableau(array, 3);
    afficherTableau(array, 3);

    return 0;
}