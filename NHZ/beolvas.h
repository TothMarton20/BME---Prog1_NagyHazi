#ifndef BEOLVAS_H_INCLUDED
#define BEOLVAS_H_INCLUDED

typedef struct {
    int azon;
    char indulas[4];
    char erkezes[4];
    int maxhely;
} Adat;

typedef struct {
    int szam;
    char nev[100];
    int ulohely;
    char menu[13];
    struct Kiadatok *kov;
} Kiadatok;

Adat* beolvas();

int randomszam();

void foglalas(Kiadatok *lista);

void helyekbeolvas(int index);

void modosit(int sor, int hely);

void foglaltsag(int azon);

Kiadatok* foglalaskeszites(Kiadatok *lista, Kiadatok *uj);

Kiadatok *listabaolvas(Kiadatok *lista);

void foglalastorlese(Kiadatok *lista, int i);

#endif
