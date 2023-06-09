#pragma once

#include "Common.h"
#include <stdio.h>

/**
 * Lérehoz egy [azon].txt fájlt, ami tartalmazza a tételeket és
 * az összesítest egy nyugtában.
 *
 * A következő elvárásoknak felel meg:
 *  - A nyugta címét középre zárja.
 *  - A tételek nevét, a darabszámot és az összeget kiírjuk
 *      - Ha a tétel neve túl hosszú, akkor több sorba törjük.
 *      - Ha a darabszám vagy az összeg túl hosszú (egy sorba nem fér ki),
 *      akkor az kilóg a txtből.
 *      - A név és darabszám balra van zárva
 *      - Az összeg mindig jobbra van zárva.
 *  - Kiírja az összesítést jobbra zárva.
 *
 * @param maxWidth Maximum szélesség-e a lapnak
 * @param nyugta A nyugta
 * @author Vass Kinga
 */
void print_nyugta(int maxWidth, NYUGTA* nyugta);

/**
 * Megszámolja a számjegyek számát
 * @param number A szám
 * @return Hány számjegyű a szám
 * @author Vass Kinga
 */
int getNumbersLength(long int number);

static void print_title(FILE* fp, int maxWidth, int sorszam);
static void print_separator(FILE* fp, int maxWidth);
static void print_tetelek(FILE* fp, int maxWidth, int tetelAmount,
                          PSZ_TETEL** tetelek);
static void print_total(FILE* fp, int maxWidth, long int osszesites);

/**
 * Feltölti a fájlt egy adott karakterrel.
 *
 * @param fp A fájl
 * @param padding Mennyi karakterrel töltsük fel
 * @param character Milyen karakterrel töltsük fel
 */
#define PAD_FILE_WITH_CHAR(fp, padding, character) \
    for (int i = 0; i < (padding); i++) { \
        fprintf(fp, "%c", character); \
    }

/**
 * Kitölti a fájlt üres karakterrel.
 *
 * @param fp A fájl
 * @param padding Hány karakterrel töltsük ki
 */
#define PAD_FILE(fp, padding) PAD_FILE_WITH_CHAR(fp, padding, ' ')
