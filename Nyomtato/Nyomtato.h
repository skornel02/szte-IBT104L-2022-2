#pragma once

#include "CommonTypes.h"

/**
 * @deprecated
 */
void print_char(char c);

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
void print_nyugta(int maxWidth, NYUGTA nyugta);
