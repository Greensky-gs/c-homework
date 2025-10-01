#include <stdio.h>

int main() {
    printf("Entrez le nombre de valeurs :");
    fflush(stdout);

    int size;
    scanf("%d", &size);
    if (size <= 0 || size > 100) {
        printf("Taille invalide (entre 1 et 100)\n");
        return 1;
    }

    int somme = 0;
    int values[100];
    int indice_courant = 0;

    printf("Entrez la liste des entiers :\n");
    while (indice_courant < size) {
        int input;
        scanf("%d", &input);

        values[indice_courant++] = input;
        somme += input;
    }

    double moyenne = (double)somme / size;
    printf("La moyenne de vos %d valeurs est %lf\n", size, moyenne);

    printf("Les valeurs superieures a la moyenne sont : ");
    for (int i = 0; i < size; i++) {
        if (values[i] > moyenne) {
            printf(" %d ", values[i]);
        }
    }

    printf("\n");
}