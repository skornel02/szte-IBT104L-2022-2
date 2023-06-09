#include "Billentyu.h"
#include <stdio.h>
#include <stdlib.h>

char read_char() {
    char c;
    scanf(" %c", &c);
    getchar();
    return c;
}

char* read_tetel_nev() {
    char* tetel_nev = (char*)malloc(100 * sizeof(char));
    printf("Kerem adja meg a tetel nevet: ");
    scanf("%s", tetel_nev);
    return tetel_nev;
}

int read_tetel_db() {
    int tetel_db;
    printf("Kerem adja meg a tetel darabszamat: ");
    scanf("%d", &tetel_db);
    return tetel_db;
}

long int read_tetel_ar() {
    long int tetel_ar;
    printf("Kerem adja meg a tetel arat: ");
    scanf("%ld", &tetel_ar);
    return tetel_ar;
}
