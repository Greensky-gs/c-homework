#include <stdio.h>

int main() {
    printf("Entrez une annee :\n");
    
    int annee;
    scanf("%d", &annee);
    
    printf(annee % 400 == 0 || (annee % 4 == 0 && annee % 100 != 0) ?  "%d est bissextile\n" : "%d n'est pas bissextile\n" , annee);
    return 0;
}
