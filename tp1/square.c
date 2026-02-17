#include <stdio.h>

int main() {
    printf("Bonjour, bienvenue dans le super calculateur de carre. Entrez n'importe quel entier et je vous calcule son carre :\n> ");
    fflush(stdout);

    int input;
    scanf("%d", &input);

    int square = input * input;

    printf("Le carre de %d est %d\n", input, square);
    return 0;
}