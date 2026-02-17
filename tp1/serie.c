#include <stdio.h>

int main() {
    double max, min;

    for (int i = 0; i < 5; i++) {
        printf("Entrez le reel %d :\n", i + 1);

        double input;
        scanf("%lf", &input);

        if (i == 0) {
            max = input;
            min = input;
            continue;
        }

        if (input > max) {
            max = input;
        }
        if (input < min) {
            min = input;
        }
    }

    printf("Vous avez saisi 5 reels :\nLe minimum est %lf\nLe maximum est %lf\n", min, max);
}