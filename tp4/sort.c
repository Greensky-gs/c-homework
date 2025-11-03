#include <stdio.h>

void afficherTab(int tab[], int elements) {
    printf("[");
    for (int i = 0; i < elements; i++) {
        printf("%d ", tab[i]);
    }
    printf("]\n");
}

int min(int tab[], int elements, int ** p) {
    int minimum = tab[0];
    *p = tab;
    for (int i = 1; i < elements; i++) {
        if (tab[i] < minimum) {
            minimum = tab[i];
            *p = &tab[i];
        };
    }

    return minimum;
}

int max(int tab[], int elements, int ** p) {
    int maximum = tab[0];
    *p = tab;
    for (int i = 1; i < elements; i++) {
        if (tab[i] > maximum) {
            maximum = tab[i];
            *p = &tab[i];
        };
    }

    return maximum;
}

void minMax(int tab[], int elements, int ** pmin, int ** pmax) {
    min(tab, elements, pmin);
    max(tab, elements, pmax);
}

int supprimerVal(int tab[], int *pNbElements, int occur) {
    int suppresses = 0;

    int i = 0;
    while (i < *pNbElements) {
        if (tab[i] == occur) {
            for (int j = i; j < *pNbElements - suppresses - 1; j++) {
                int temp = tab[j];
                tab[j] = tab[j + 1];
                tab[j + 1] = temp;
            }
            tab[i + 1] = 0;
            suppresses++;
        }
        i++;
    }

    *pNbElements = *pNbElements - suppresses;
    return suppresses;
}

int main() {
    int test[5] = { 1, 2, 5, 4, 5 };

    int * m;
    int * M;
    minMax(test, 5, &m, &M);

    printf("%d, %d\n", *m, *M);

    afficherTab(test, 5);
    int elements = 5;
    int res = supprimerVal(test, &elements, 5);
    printf("%d\n", res);
    afficherTab(test, elements);
}