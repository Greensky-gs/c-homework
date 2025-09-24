#include <stdio.h>

int main() {
    printf("Entrez votre texte :");
    fflush(stdout);

    int lettres = 0;
    int voyelles = 0;

    char toc_toc_entrez;
    scanf("%c", &toc_toc_entrez);

    while (toc_toc_entrez != '#') {
        if (toc_toc_entrez == '\n') {
            continue;
        }

        if (!(('a' <= toc_toc_entrez && toc_toc_entrez <= 'z') || toc_toc_entrez == ' ')) {
            printf("Ce caractère n'est pas valide. J'arrète tout : %c\n", toc_toc_entrez);
            lettres = -1;
            break;
        }
        lettres++;

        if (toc_toc_entrez == 'a' || toc_toc_entrez == 'e' || toc_toc_entrez == 'i' || toc_toc_entrez == 'o' || toc_toc_entrez == 'u' || toc_toc_entrez == 'y') {
            voyelles++;
        }

        scanf("%c", &toc_toc_entrez);
    }

    if (lettres >= 0) {
        printf("Il y a %d caractères (de la bruyère) et %d voyelles\n", lettres, voyelles);
    }

    return 0;
}