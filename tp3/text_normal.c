#include <stdio.h>
#include <string.h>

int main() {
    char texte[81];
    printf("Entrez votre texte : ");
    fflush(stdout);

    char caractere;
    int indice_courant = 0;

    scanf("%c", &caractere);
    while (caractere != '\n' && indice_courant < 80) {
        texte[indice_courant] = caractere;
        indice_courant++;

        scanf("%c", &caractere);
    }

    texte[indice_courant] = '\0';

    printf("Votre texte est %s et contient %d caracteres\n", texte, indice_courant);

    char reversed[81];
    for (int i = 0; i < indice_courant; i++) {
        reversed[i] = texte[indice_courant - 1 - i];
    }
    reversed[indice_courant] = '\0';

    printf("Votre texte a l'envers donne %s\n", reversed);

    int est_palindrome = 1;
    int indice_a = 0;
    int indice_b = 0;

    while (est_palindrome && indice_a < indice_courant) {
        char a = texte[indice_a];
        char b = texte[indice_courant - 1 - indice_b];

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

    printf(est_palindrome
        ? "Ce texte est un palindrome\n"
        : "Ce texte n'est pas un palindrome\n"
    );
}
