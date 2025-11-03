#include <stdio.h>

void convert(int seconds, int * hours, int * mins, int * secs) {
    *hours = 0;
    *mins = 0;
    *secs = 0;

    *hours = seconds / 3600;
    seconds -= *hours * 3600;

    *mins = seconds / 60;
    seconds -= *mins * 60;

    *secs = seconds;
}
void convertToTab(int seconds, int tab[]) {
    convert(seconds, &tab[0], &tab[1], &tab[2]);
}

int main() {
    printf("Entrez une durée en secondes : ");
    fflush(stdout);

    int res;
    scanf("%d", &res);

    int conversion[3];
    
    convertToTab(res, conversion);
    printf("%dh %dm %ds\n", conversion[0], conversion[1], conversion[2]);
}