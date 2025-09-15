#include <stdio.h>
#include <stdlib.h>

int repetition_un() {
    int somme = 0;
    while (1) {
        printf("Entrez un entier (ou un entier negatif pour proceder au calcul) :\n> ");
        fflush(stdout);

        int entier;
        scanf("%d", &entier);

        if (entier < 0) break;

        somme+=entier;
    }

    printf("Le total du calcul est : %d\n", somme);
    return somme;
}
int repetition_deux() {
    int etoiles;
    printf("Entrez un entier positif (nombre d'etoiles) :\n> ");
    fflush(stdout);

    scanf("%d", &etoiles);

    for (int i = 0; i < etoiles; i++) {
        printf("*");
    }
    printf("\n");
    return etoiles;
}

void clear_screen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int main() {
    printf("Choisissez une des repetitions : 1 ou 2\n> ");
    fflush(stdout);

    int choix;
    scanf("%d", &choix);

    if (choix == 1) {
        clear_screen();
        repetition_un();
    } else if (choix == 2) {
        clear_screen();
        repetition_deux();
    } else {
        printf("Choix invalide. Echec critique.\n");
    }

    return 0;
}