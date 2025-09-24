#include <stdio.h>

int main_sans_notes() {
    printf("Entrez le nombre de valeurs :");
    fflush(stdout);

    int nombre;
    scanf("%d", &nombre);
    if (nombre < 0) {
        printf("Nombre de caractères invalide.\n");
        return 0;
    }

    double somme = 0;
    for (int i = 0; i < nombre; i++) {
        printf("Entrez le réel numéro %d\n", i + 1);
        double entree;
        scanf("%lf", &entree);

        somme += entree;
    }

    double moyenne = somme / nombre;

    printf("La moyenne est %lf\n", moyenne);
}

int main() { // Avec notes
    printf("Entrez le nombre de valeurs :");
    fflush(stdout);

    int nombre;
    scanf("%d", &nombre);
    if (nombre < 0) {
        printf("Nombre de caractères invalide.\n");
        return 0;
    }

    int somme = 0;
    for (int i = 0; i < nombre; i++) {
        printf("Entrez le caractère numéro %d :\n", i + 1);
        int entree;

        scanf("%d", &entree);

        while (0 > entree ||  entree > 20) {
            printf("Réel erronné, essayez à nouveau\n");
            scanf("%d", &entree);
        }

        somme += entree;
    }

    double moyenne = somme / (double)nombre;
    printf("La moyenne est %lf\n", moyenne);
}