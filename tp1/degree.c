#include <stdio.h>

int main() {
    printf("Entrez une température (entiere) en degres Farenheit :\n");

    int faren;
    scanf("%d", &faren);


    int celsius = (5.0 / 9) * (faren - 32);

    printf("%d degres farenheit vallent %d degres celsius\n", faren, celsius);

    return 0;
}