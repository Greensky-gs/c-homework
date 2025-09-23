#include <stdio.h>
#define CELLSIZE 4

int main() {
    int a = -1;
    int b = -1;

    while (a < 0 || b < 0) {
        if (a >= 0) {
            printf("Entrez la valeur de b : ");
        } else {
            printf("Entrez la valeur de a : ");
        }

        fflush(stdout);

        int input;
        scanf("%d", &input);

        if (input > 18 || input < 0) {
            printf("Valeur invalide, ressayez (entre 0 et 18)\n");
        } else {
            if (a >= 0) {
                b = input;
            } else {
                a = input;
            }
        }
    }

    printf("   x |");
    for (int i = 0; i <= b; i++) {
        printf("%4d", i);
    }
    printf("\n  ");
    for (int i = 0; i <= (b + 2) * CELLSIZE; i++) {
        printf("-");
    }
    printf("\n");
    for (int i = 0; i <= a; i++) {
        printf("%4d |", i);
        for (int j = 0; j <= b; j++) {
            printf("%4d", i * j);
        }
        printf("\n");
    }
}
