#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
    #include <windows.h>
#endif
#include "beolvas.h"
#include "helyek.h"
#include "debugmalloc.h"
#include <stdbool.h>
#include <time.h>
#include <string.h>

int main(void){
#ifdef _WIN32
    SetConsoleCP(1250);
    SetConsoleOutputCP(1250);
#endif

#define MAX_FOGLALASOK 100

    struct Adat{
    int azon;
    char indulas[4];
    char erkezes[4];
    int maxhely;
    };

    typedef struct {
    int szam;
    char nev[100];
    int ulohely;
    char menu[13];
    struct Kiadatok *kov;
    } Kiadatok;

    int be;

    Kiadatok* lista=NULL;
    lista=listabaolvas(lista);

    Adat *t = NULL;
    t = beolvas();
    if (t == NULL) {
        printf("Hiba tortent a fajl beolvasasakor.\n");
    }

    printf("Üdvözlöm a repülõjegy vásárlási menüben, kérem válasszon az alábbi menüpontokbol.\n");
    printf("(A menü használatához gépelje be a billenyûzetrõl a menü sorszámát majd nyomjon egy ENTER gombot)\n\n");

    do{
        printf("1. Járat keresése\n");
        printf("2. Repülojegy foglalás vagy törlése\n");
        printf("3. Jaratok ulohely terkepe\n");
        printf("4. Kilépés\n");
        printf("Kérem a választását: ");
        scanf("%d", &be);

        switch(be){
///----------------------------------------------------------------------------------------------------
            case 1:
                printf("Járat keresése\n\n");

                char beind[4];
                char beerk[4];
                int inderk;
                int van=0;

                helyek(90, 100, "helyek.txt");

                printf("Adja meg hogy pontosan mit keres(1-3): \n");
                printf("1. Indulási reptér keresése.\n");
                printf("2. Érkezési reptér keresése.\n");
                printf("3. Kilépés a fomenübe.\n");
                printf("Kérem a választását: ");
                scanf("%d",&inderk);

                switch(inderk){

                case 1:
                    printf("Adja meg az indulási reptér kódját: ");
                    scanf("%3s", beind);

                    printf("A keresett járatok: \n");
                    for(int i=0;i<90;i++){
                        if(strcmp(beind, t[i].indulas) == 0){
                            printf("%s ",t[i].indulas);
                            printf("%s\n",t[i].erkezes);
                            van++;
                        }
                    }
                    if(van>0)
                        printf("\n");
                    if(van==0)
                        printf("-\n\n");

                    break;

                case 2:
                    van=0;
                    printf("Adja meg az érkezési reptér kódját: ");
                    scanf("%3s", beerk);

                    printf("A keresett járatok: \n");
                    for(int i=0;i<90;i++){
                        if(strcmp(beerk, t[i].erkezes) == 0){
                            printf("%s ",t[i].indulas);
                            printf("%s\n",t[i].erkezes);
                            van++;
                        }
                    }
                    if(van>0)
                        printf("\n");
                    if(van==0)
                        printf("-\n\n");

                    break;

                case 3:
                    break;

                default:
                    printf("A tartományon belüli számot adjon meg!\n\n");
                    break;
                }

                break;
///----------------------------------------------------------------------------------------------------
            case 2:
                printf("\nRepülojegy foglalás\n");

                int fog;

                printf("1. Foglalás\n");
                printf("2. Törlés\n");
                printf("3. Kilépés a fomenübe");
                printf("Kérem adja meg, hogy foglalni vagy törölni szeretne-e: ");
                scanf("%d", &fog);

                switch(fog){

                    case 1:
                        printf("Foglalás indítása\n\n");
                        int a;
                        int sorok = 0;
                        char *ind[4], erk[4];
                        int van1, van2;
                        van1=van2=0;
                        printf("Adja meg az indulasi repter azonositojat: ");
                        scanf("%s", &ind);
                        printf("Adja meg az erkezesi repter azonositojat: ");
                        scanf("%s", &erk);

                        for(int i=0;i<90;i++){
                            if(strcmp(t[i].indulas, ind) == 0){
                                van1=1;
                            }
                        }
                        if(van1==0){
                            printf("Nem létezo repteret adott meg!\n\n");
                            break;
                        }

                        for(int i=0;i<90;i++){
                            if(strcmp(t[i].erkezes, erk) == 0){
                                van2=1;
                            }
                        }
                        if(van2==0){
                            printf("Nem létezo repteret adott meg!\n\n");
                            break;
                        }

                        for(int i = 0; i < 90; i++) {
                            if((strcmp(t[i].indulas, ind) == 0) && (strcmp(t[i].erkezes, erk) == 0)) {
                                a=i;
                                break;
                            }
                        }

                        Kiadatok *uj = (Kiadatok*)malloc(sizeof(Kiadatok));

                        uj->szam=randomszam();
                        printf("Adja meg a vezetéknevét: ");
                        scanf("%s", &uj->nev);
                        printf("Adja meg a az ulohelyet: ");
                        scanf("%d", &uj->ulohely);
                        printf("Adja meg melyik menut szeretné(normál, vega, laktózmentes): ");
                        scanf("%s", &uj->menu);
                        uj->kov = NULL;

                        lista=foglalaskeszites(lista, uj);

                        modosit(a, uj->ulohely);
                        foglaltsag(a);

                        break;

                    case 2:
                        printf("Törlés indítása\n\n");
                        int idx=1;
                        int szam;
                        Kiadatok* mozgo;
                        for(mozgo = lista; mozgo != NULL; mozgo = mozgo->kov)
                            printf("%d. %d %s %d %s\n", idx++, mozgo->szam, mozgo->nev, mozgo->ulohely, mozgo->menu);

                        printf("\n\nAdja meg hogy hanyadik foglalást töröljük a rendszerbol: ");
                        scanf("%d", &szam);

                        foglalastorlese(lista, szam);

                        break;

                    case 3:
                        break;

                    default:
                        printf("A tartományon belüli számot adjon meg.");
                        break;
        }
                break;
///----------------------------------------------------------------------------------------------------
            case 3:
                printf("Jaratok ulohely terkepe\n\n");

                int azonosito;
                char fogind[4], fogerk[4];
                printf("Adja meg az indulasi repter azonositojat: ");
                scanf("%s", &fogind);
                printf("Adja meg az erkezesi repter azonositojat: ");
                scanf("%s", &fogerk);

                for(int i = 0; i < 90; i++) {
                    if((strcmp(t[i].indulas, fogind) == 0) && (strcmp(t[i].erkezes, fogerk) == 0)) {
                        azonosito=i;
                        azonosito++;
                        break;
                    }
                }

                helyekbeolvas(azonosito);

                break;
///----------------------------------------------------------------------------------------------------
            case 4:
                printf("A kilépést választotta.\nViszontlátásra!\n\n");
                break;

            default:
                printf("A tartományon belüli számot adjon meg!\n");
                break;
        }

    }while(be!=4);


    foglalas(lista);
    listafelszab(lista);
    free(t);
    return 0;
}
