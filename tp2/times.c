#include <stdio.h>
#include <string.h>     
#define CELLSIZE 4


int main() {
    int a = -1;
    int b = -1;

    while (a < 0 || b < 0) {
        if (a >= 0) {
            printf("Entrez la valeur de B :");
        } else {
            printf("Entrez la valeur de A :");
        }
        fflush(stdout);

        int input;
        scanf("%d", &input);

        if (input > 18 || input < 0) {
            printf("Veuillez saisir un entier entre 0 et 18");
        } else {
            if (a > 0) {
                b = input;
            } else {
                a = input;
            }
        }
    }

    FILE *fp;
    fp = fopen("./temp.txt", "w");

    fprintf(fp, "   x |");

    for (int i = 0; i <= b; i++) {
        fprintf(fp, "%4d", i);
    }
    fprintf(fp, "\n  ");
    for (int i = 0; i <= (b + 2) * CELLSIZE; i++) {
        fprintf(fp, "-");
    }
    fprintf(fp, "\n");
    for (int i = 0; i <= a; i++) {
        fprintf(fp, "%4d |", i);
        for (int j = 0; j <= b; j++) {
            fprintf(fp, "%4d", i * j);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
    FILE *reader;
    reader = fopen("./temp.txt", "r");

    char ligne[100];

    // Read the content and print it
    while(fgets(ligne, 100, reader)) {
        for (int i = 0; i < strlen(ligne); i++) {
            int colorCode = 91 + i % 6;
            printf("\x1b[%dm%c\x1b[0m", colorCode, ligne[i]);
        }
    };

    fclose(reader);

    remove("./temp.txt");
}