#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int askRepeats(long long * repeats) {
    printf("Entrez le nombre de repetitions : \x1b[96m");
    fflush(stdout);

    scanf("%lld", repeats);
    while (*repeats < 0) {
        printf("\x1b[0mPour mon pc, veuillez saisir un entier entre 1 et 10^10 : \x1b[96m");
        fflush(stdout);

        scanf("%lld", repeats);
    }
    printf("\x1b[0m");

    return 0;
}

int generateRandomPos(double * a, double * b) {
    *a = (double) (rand() + 1) / RAND_MAX;
    *b = (double) (rand() +1) / RAND_MAX;

    return 0;
}

// Implémentation de la méthode de Monte-Carlo
int main() {
    srand(time(NULL));
    // On approxime pi/4

    long long repeats = 10000000000;
    askRepeats(&repeats);

    long int inside = 0;
    int i = 0;

    while (i < repeats) {
        double x, y;
        generateRandomPos(&x, &y);

        if (x * x + y * y <= 1) {
            inside++;
        }

        i++;
    }

    long double fourth_pi = (long double) inside / repeats;
    long double pi = fourth_pi * 4;

    printf("Nombre de points dans le cercle : \x1b[34m%ld\x1b[0m.\nNombre total de points          : \x1b[34m%lld\x1b[0m.\n", inside, repeats);
    printf("Une valeur approchee de \x1b[32mpi\x1b[0m avec \x1b[34m%lld\x1b[0m repetitions est : \x1b[33m%.30Lf\x1b[0m\n", repeats, pi);
}