#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Entrez le nombre de valeurs que vous voulez : ");
    fflush(stdout);
    int taille;

    scanf("%d", &taille);

    while (taille <= 0) {
        printf("Valeur invalide, veuillez reessayer : ");
        fflush(stdout);
        scanf("%d", &taille);
    }

    double * valeurs = malloc(taille * sizeof(double));
    int indice_courant = 0;

    printf("Entrez la liste de vos reels, separes par des espaces.\nLe programme vous dira quand vous aurez termine, continuez de saisir des valeurs tant que ce n'est pas fait\n");
    while (indice_courant < taille) {
        double entree;
        int resultat = scanf("%lf", &entree);

        if (resultat == 1) {
            valeurs[indice_courant] = entree;
            indice_courant++;
        }
    }

    printf("Affichage de vos valeurs : \n");
    for (int i = 0; i < taille; i++) {
        printf("%lf ; ", valeurs[i]);
    }
    printf("\n");

    free(valeurs);
}