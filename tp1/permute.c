#include <stdio.h>

int main() {
    int a = 0, b = 0;
    printf("Entrez l'entier a: \n");

    scanf("%d", &a);
    printf("Entrez l'entier b: \n");

    scanf("%d", &b);

   // int c = a;
    //a = b;
    //b = c;

    a=a+b-(b=a);

    printf("A: %d, B: %d\n", a, b);
    return 0;
}
