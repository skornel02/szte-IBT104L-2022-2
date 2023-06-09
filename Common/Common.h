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
    int tetelCount;
    OSSZESITES* osszesites;
} NYUGTA;

/**
 * A program állapotát irányító véges állapotgép állapotai.
 *
 * <br/>
 * Ezen állapotgép állapot váltásai lineárisak.
 * <ul>
 * <li>NEV => DB</li>
 * <li>DB => AR</li>
 * <li>AR => MENTES</li>
 * <li>MENTES => ATMENET</li>
 * <li>ATMENET => KOVETKEZO</li>
 * <li>KOVETKEZO => NEV</li>
 * </ul>
 * Az összes többi átmenet tiltott.
 *
 * @author Stefán Kornél
 */
typedef enum {
    NEV,
    DB,
    AR,
    MENTES,
    ATMENET,
    KOVETKEZO
} BEOLVASAS_ALLAPOT;

/**
 * Összegzi a nyugta tételeinek árát.
 *
 * @param tetelek A tételek tömbje
 * @param tetelCount A tömb elemeinek száma
 * @return Az összegzés
 * @author Stefán Kornél
 */
OSSZESITES *calculate_osszesites(PSZ_TETEL** tetelek, int tetelCount);

/**
 * Felszabadítja a nyugta tömb értékeit biztonságosan.
 * <br>
 * A nyugta NEM kerül felszaabadításra!
 *
 * @param nyugta A nyugta referenciája.
 * @author Stefán Kornél
 */
void free_nyugta_members(NYUGTA *nyugta);

/**
 * Hozzáadja a tételt a nyugtához.
 * <br>
 * Ezt úgy éri el, hogy újraméretezi a már meglévő tömböt.
 * (A realloc miatt a NULL-ra is értelmezett.)
 *
 * @param nyugta A nyugta referenciája.
 * @param tetel A tétel referenciája.
 * @author Stefán Kornél
 */
void add_tetel_to_nyugta(NYUGTA* nyugta, PSZ_TETEL* tetel);