#include <stdio.h>

int main() {
    char text[81];
    int indice_courant = 0;

    printf("Entrez votre texte (max 80 caracteres) :");
    fflush(stdout);

    char input;
    scanf("%c", &input);

    while (input != '\n' && indice_courant < 80) {
        text[indice_courant] = input;
        indice_courant++;

        scanf("%c", &input);
    }
    text[indice_courant] = '\0';

    printf("Le texte saisi est \x1b[31m%s\x1b[0m, et il y a %d caracteres\n", text, indice_courant);

    char reversed[81];
    for (int i = indice_courant - 1; i >= 0; i--) {
        reversed[indice_courant - 1 - i] = text[i];
    }
    reversed[indice_courant] = '\0';

    printf("Le texte inversed est \x1b[32m%s\x1b[0m\n", reversed);

    int est_palindrome = 1;
    int indice_a = 0;
    int indice_b = 0;

    while (est_palindrome && indice_a < indice_courant) {
        char a = text[indice_a];
        char b = reversed[indice_b];

        if (a == ' ') {
            indice_a++;
        } else if (b == ' ') {
            indice_b++;
        } else if (a != b) {
            est_palindrome = 0;
        } else {
            indice_a++;
            indice_b++;
        }
    }

    if (est_palindrome) {
        printf("Votre phrase est un palindrome, bravo\n");
    } else {
        printf("Votre phrase n'est pas un palindrome, dommage\n");
    }
    return 0;
}