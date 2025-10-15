#include <stdio.h>

#define MAX 80
#define CARACTERE_TERMINAISON '\0'

int Lecture(char * ch, int NbCarMax) {
    char entree;
    int indice = 0;

    scanf("%c", &entree);
    while (entree != '\n' && indice < NbCarMax) {
        ch[indice] = entree;
        // *(ch + indice) = entree;
        indice++;

        scanf("%c", &entree);
    }

    ch[indice] = CARACTERE_TERMINAISON;
    // *(ch + indice) = '\0';
    return indice;
}

int Longueur(char * ch) {
    int taille = 0;
    while (ch[taille] != '\0') {
        taille++;
    }
    return taille;
}

void Copie(char * destination, char * Source) {
    int indice = 0; 
    while (Source[indice] != '\0') {
        destination[indice] = Source[indice];
        indice++;
    }
    destination[indice] = CARACTERE_TERMINAISON;
}

int Differentes(char *ch1, char *ch2) {
    int indice = 0;
    int differentes = 0;
    while (ch1[indice] != '\0' && ch2[indice] != '\0' && !differentes) {
        if (ch1[indice] != ch2[indice]) differentes = 1;
        indice++;
    }
    if (ch1[indice] != ch2[indice]) return 1;
    return differentes;
}

#define destintoin destination
void Ajout(char * destination, char * source) {
    int tailleDest = Longueur(destination);
    int indiceDeLaSource = 0;

    while (source[indiceDeLaSource] != '\0') {
        destintoin[tailleDest + indiceDeLaSource] = source[indiceDeLaSource];
        indiceDeLaSource++;
    }

    destintoin[tailleDest + indiceDeLaSource] = '\0';
}


int main() {
    printf("Test de Lecture\n---------------\n");
    printf("Tapez une chaine d'au plus %d caracteres : ", MAX);
    char ch1[MAX + 1];
    int n;
    
    n = Lecture(ch1, MAX);
    printf("La chaine \"%s\" a ete lue ; elle contient %d caracteres.\n", ch1, n);
    
    printf("\nTest de Longueur\n----------------\n");
    printf("La chaine \"%s\" contient %d caracteres.\n", ch1, Longueur(ch1));
    
    printf("\nTest de copie\n-------------\n");
    char ch2[2 * MAX + 1];
    Copie(ch2, ch1);

    printf("ch1=\"%s\", ch2=\"%s\"\n", ch1, ch2);
    
    printf("\nTest de Differentes\n-------------------\n");
    char ch3[MAX + 1] = "o";
    while (Differentes(ch3, "n")) {
        printf("Tapez une premiere chaine : ");
        Lecture(ch1, MAX);
        printf("Tapez une seconde chaine : ");
        Lecture(ch2, MAX);

        if (Differentes(ch1,ch2)) printf("%s et %s ne contiennent pas les mêmes caracteres.\n", ch1, ch2);
        else printf("%s et %s contiennent les memes caracteres.\n", ch1, ch2);
        printf("Voulez-vous continuer le test de Differentes (tapez n pour arreter) : ");
        Lecture(ch3, 1);
    }
        
    printf("\nTest de Ajout\n-------------\n");
    Copie(ch3,"o");
    while (Differentes(ch3,"n")) {
        printf("Tapez une premiere chaine : ");
        Lecture(ch1, MAX);
        printf("Tapez une seconde chaine : ");
        Lecture(ch2, MAX);

        printf("Ajout de la premiere chaine a la seconde :\n");
        Ajout(ch2, ch1);

        printf("ch1=\"%s\", ch2=\"%s\"\n", ch1, ch2);

        printf("Voulez-vous continuer le test de Ajout (tapez n pour arreter) : ");
        Lecture(ch3,1);
    }
        
    return 0;
}