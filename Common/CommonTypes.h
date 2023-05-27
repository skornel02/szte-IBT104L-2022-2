#pragma once

typedef struct {
    char* f_nev;
    int f_db;
    long int f_ar;
} PSZ_TETEL;

typedef struct {
    long int f_ar;
} OSSZESITES;

typedef struct {
    int sorszam;
    PSZ_TETEL** tetelek;
    OSSZESITES* osszesites;
} NYUGTA;

typedef enum {
    NEV,
    DB,
    AR,
    ATMENET
} BEOLVASAS_ALLAPOT;