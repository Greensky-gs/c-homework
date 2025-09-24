#include <stdio.h>

// Maximum : 95 lignes
int main() {
    printf("Entrez le nombre de ligjnes :");
    fflush(stdout);

    int lignes;
    scanf("%d", &lignes);

    for (int i = 0; i < lignes; i++) {
        int nombre_etoiles = 2 * i + 1;
        int espaces = lignes - (i + 1);

        for (int j = 0; j < espaces; j++) {
            printf(" ");
        }
        for (int j = 0; j < nombre_etoiles; j++) {
            printf("*");
        }

        printf("\n");
    }
}