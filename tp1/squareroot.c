#include <stdio.h>
#include <math.h>

int main() {
    printf("Bonjour, bienvenue dans le super calculateur de racines. Entrez n'importe quel réel et je vous calcule sa racine :\n> ");
    fflush(stdout);

    double input;
    scanf("%lf", &input);

    if (input < 0) {
        printf("%f est un réel négatif\n", input);
        return 0;
    }

    double root = sqrt(input);

    printf("La racine de %lf est %lf\n", input, root);
    return 0;
}