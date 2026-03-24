#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "beolvas.h"
#include "debugmalloc.h"


///----------------------------------------------------------------------------------------------------

Adat* beolvas() {
    FILE* file = fopen("repulojaratok.txt", "r");
    if (file == NULL) {
        perror("A fajl megnyitasa sikertelen.");
        return NULL;
    }

    Adat* adatok = NULL;
    int meret = 0;

    while (1) {
        adatok = (Adat*)realloc(adatok, (meret + 1) * sizeof(Adat));

        if (fscanf(file, "%d %4s %4s %d", &adatok[meret].azon, adatok[meret].indulas, adatok[meret].erkezes, &adatok[meret].maxhely) != 4) {
            if (feof(file)) {
                break;
            } else {
                perror("Hiba a fajl beolvasasakor");
                free(adatok);
                fclose(file);
                return NULL;
            }
        }

        meret++;
    }

    fclose(file);

    return adatok;
}

///----------------------------------------------------------------------------------------------------

int randomszam() {
    srand((unsigned int)time(NULL));

    int number = 0;
    for (int i = 0; i < 5; ++i) {
        number = number * 10 + rand() % 10;
    }

    return number;
}

///----------------------------------------------------------------------------------------------------

void foglalas(Kiadatok *lista){
    FILE *f = fopen("foglalasok.txt", "w");

    Kiadatok *mozgo;

    for(mozgo = lista; mozgo != NULL; mozgo = mozgo->kov)
        fprintf(f, "%d %s %d %s\n", mozgo->szam, mozgo->nev, mozgo->ulohely, mozgo->menu);


    fclose(f);
}

///----------------------------------------------------------------------------------------------------

void helyekbeolvas(int index) {
    FILE* file = fopen("helyek.txt", "r");
    if (file == NULL) {
        printf("A fajl megnyitasa sikertelen.\n");
        return;
    }

    int sorSzam;
    int talalt = 0;

    while (fscanf(file, "%d", &sorSzam) == 1) {
        int szamok[100];

        for (int i = 0; i < 100; ++i) {
            if (fscanf(file, "%d", &szamok[i]) != 1) {
                printf("Hiba a fajl beolvasasakor.\n");
                fclose(file);
                return;
            }
        }

        if (sorSzam == index) {
            talalt = 1;
            for (int i = 0; i < 100; ++i) {
                printf("%d %d",i+1, szamok[i]);
                printf("\n");
            }
            printf("\n");
        }
    }

    if (talalt==1) {
        printf("Nincs ilyen azonosito a fajlban.\n");
    }

    fclose(file);
}

///----------------------------------------------------------------------------------------------------

void modosit(int sor, int hely) {
    FILE* file = fopen("helyek.txt", "r");
    if (file == NULL) {
        printf("A fajl megnyitasa sikertelen.\n");
        return;
    }

    int tomb[90][101];

    for (int i = 0; i < 90; i++) {
        for (int j = 0; j < 101; j++) {
            fscanf(file, "%d ", &tomb[i][j]);
        }
        fscanf(file,"\n");
    }
    fclose(file);

    if(tomb[sor][hely]==1){
        printf("A hely mar foglalt keressen masikat.\n\n");
        return 0;
    }

    tomb[sor][hely]=1;

    FILE* f = fopen("helyek.txt", "w");

    for (int i = 0; i < 90; i++) {
        for (int j = 0; j < 101; j++) {
            fprintf(f, "%d ", tomb[i][j]);
        }
        fprintf(f,"\n");
    }

    fclose(f);
}


///----------------------------------------------------------------------------------------------------

void foglaltsag(int azon) {
    FILE *file = fopen("foglaltsag.txt", "r");
    if (file == NULL) {
        printf("A fajl megnyitasa sikertelen.\n");
        return;
    }

    int tomb[90][2];

    for (int i = 0; i < 90; i++) {
        for (int j = 0; j < 2; j++) {
            fscanf(file, "%d ", &tomb[i][j]);
        }
        fscanf(file,"\n");
    }
    fclose(file);

    if(tomb[azon][1]==100){
        printf("Megtelt a repülo, nem tud helyet foglalni.\n\n");
        return 0;
    }

    tomb[azon][1]+=1;

    FILE* f = fopen("foglaltsag.txt", "w");

    for (int i = 0; i < 90; i++) {
        for (int j = 0; j < 2; j++) {
            fprintf(f, "%d ", tomb[i][j]);

        }
        fprintf(f,"\n");
    }

    fclose(f);
}

///----------------------------------------------------------------------------------------------------

Kiadatok* foglalaskeszites(Kiadatok *lista, Kiadatok *uj) {
    if (lista == NULL) {
        return uj;
    } else {
        Kiadatok *mozgo = lista;
        while (mozgo->kov != NULL) {
            mozgo = mozgo->kov;
        }
        mozgo->kov = uj;
        return lista;
    }
}

///----------------------------------------------------------------------------------------------------

Kiadatok *listabaolvas(Kiadatok *lista) {
    FILE *f = fopen("foglalasok.txt", "r");
    if (f == NULL) {
        printf("A fajl megnyitasa sikertelen.\n");
        return lista;
    }

    Kiadatok *uj = (Kiadatok *)malloc(sizeof(Kiadatok));


    while (fscanf(f, "%d %100s %d %10s", &(uj->szam), uj->nev, &(uj->ulohely), uj->menu) == 4) {
    uj->kov = NULL;

    lista = foglalaskeszites(lista, uj);

    uj = (Kiadatok *)malloc(sizeof(Kiadatok));
    }

    free(uj);
    fclose(f);
    return lista;
}

///----------------------------------------------------------------------------------------------------

void foglalastorlese(Kiadatok *lista, int i){
    Kiadatok *lemarado = NULL;
    Kiadatok *mozgo = lista;
    int szamlalo = 1;

    while (mozgo != NULL && szamlalo != i){
        lemarado = mozgo;
        mozgo = mozgo->kov;
        szamlalo++;
    }

    if (mozgo == NULL) {

    } else if (lemarado == NULL) {
        lista = mozgo->kov;
        free(mozgo);
    } else {
        lemarado->kov = mozgo->kov;
        free(mozgo);
    }

    printf("\nA törlés megtörtént!\n\n");
}

///----------------------------------------------------------------------------------------------------

void listafelszab(Kiadatok *lista){
    Kiadatok *iter = lista;
    while( iter != NULL) {
        Kiadatok *kov = iter->kov;
        free(iter);
        iter = kov;
    }
}
