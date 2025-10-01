#include <stdio.h>
#include <string.h>

int consonne(char c) {
    char consonnes[] = "bcdfghjklmnpqrstvwxz";

    for (int i = 0; i < 20; i++) {
        if (consonnes[i] == c) {
            return 1;
        }
    }
    return 0;
}
int consonneMAJ(char c) {
    char consonnes[] = "BCDFGHJKLMNPQSRTVWXZ";

    for (int i = 0; i < 20; i++) {
        if (consonnes[i] == c) {
            return 1;
        }
    }
    return 0;
}
int voyelle(char c) {
    char voyelles[] = "aeiuoy";

    for (int i = 0; i < 20; i++) {
        if (voyelles[i] == c) {
            return 1;
        }
    }
    return 0;
}
int voyelleMAJ(char c) {
    char voyelles[] = "AEIOUY";

    for (int i = 0; i < 20; i++) {
        if (voyelles[i] == c) {
            return 1;
        }
    }
    return 0;
}
int main() {
    char texte[81];
    printf("Entrez votre texte : \x1b[36m");
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

    FILE *fp;
    fp = fopen("./temp.txt", "w");

    fprintf(fp, "Votre texte est %s et contient %d caracteres\n", texte, indice_courant); 

    char reversed[81];
    for (int i = 0; i < indice_courant; i++) {
        reversed[i] = texte[indice_courant - 1 - i];
    }
    reversed[indice_courant] = '\0';

    fprintf(fp, "Votre texte a l'envers donne %s\n", reversed);

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

    fprintf(fp, est_palindrome
        ? "Ce texte est un palindrome\n"
        : "Ce texte n'est pas un palindrome\n"
    );

    fclose(fp);
    FILE *reader;
    reader = fopen("./temp.txt", "r");

    char ligne[4096];

    while (fgets(ligne, 4096, reader)) {
        for (int i = 0; i < strlen(ligne); i++) {
            int colorCode = voyelle(ligne[i]) || voyelleMAJ(ligne[i]) ? 91 : consonne(ligne[i]) || consonneMAJ(ligne[i]) ? 96 : 93;
            printf("\x1b[%dm%c\x1b[0m", colorCode, ligne[i]);
        }
    }

    fclose(reader);
    remove("./temp.txt");
}
