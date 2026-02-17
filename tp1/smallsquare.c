#include <stdio.h>

int main() {
    printf("Bonjour, bienvenue dans le super calculateur de carre. Entrez n'importe quel entier et je vous calcule son carre :\n> ");
    fflush(stdout);

    unsigned char input;
    scanf("%hhu", &input);

    unsigned char square = input * input;

    printf("Le carre de %d est %d\n", input, square);
    return 0;
}


/* 
Avec 8 on obtient 64
Avec 16 on obtient 256

C'est parce qu'une variable de type char est encodée sur 8 bits, et 256 dépasse la limite des 255 nombres que l'on peut encoder sur 8 bits, donc ça fait 0

*/