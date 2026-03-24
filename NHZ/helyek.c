#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int azon;
    char indulas[3];
    char erkezes[3];
    int maxhely;
} Adat;

void helyek(int meret, int hossz, char *fajlnev) {
    FILE *fajl = fopen(fajlnev, "w");

    if (fajl == NULL) {
        perror("Hiba a fájl megnyitásakor");
        return;
    }
    int szam=0;

    for (int i = 0; i < meret; i++) {
        fprintf(fajl, "%d ", i + 1);

        for (int j = 1; j <=hossz; j++) {
            fprintf(fajl, "%d ", szam);
        }

        fprintf(fajl, "\n");
    }
    fclose(fajl);
}
