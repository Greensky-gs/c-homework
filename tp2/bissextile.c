#include <stdio.h>

int main() {
    int annee;
    printf("Entrez une annee :\n");

    scanf("%d", &annee);

    printf((annee % 4 == 0 && annee % 100 != 0) || annee % 400 == 0 ? "%d est bissextile" : "%d n'est pas bissextile", annee);

    return 0;
}