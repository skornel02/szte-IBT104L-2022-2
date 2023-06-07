﻿#include "Billentyu.h"
#include "Nyomtato.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * A program belépési pontja.
 *
 * Feladatai:
 * <ol>
 * <li> Beolvassa biztonságosan az első paraméteren lévő számot,
 *         ami a max szélességet lenne hivatott jelölni. </li>
 * <li> Üdvözli a felhasználót egy kellemes britt akcentussal. </li>
 * <li> Egy betöltési animáció után elindul a program működése. </li>
 *
 * </ol>
 *
 * Program működése:
 * <ol>
 * <li> A felhasználó tételt rögzíthet.
 * Itt egy állapotgépet használni, ami tudja, hogy épp milyen adatviteli ponton vagyunk.
 * @enum BEOLVASAS_ALLAPOT
 * </li>
 * <li>
 *      Tétel felvitele után, amikor átmeneti állapot van,
 *      akkor a felhasználónak lehetősége van a programból:
 *      <ul>
 *          <li> kilépni </li>
 *          <li> új tételt felvinni </li>
 *          <li> a nyugtát kinyomtatni, ami után új nyugta kezdődik </li>
 *      </ul>
 * </li>
 * </ol>
*/
int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Légyszíves adj meg egy maximum szélességet a nyomtatónak! pl.: "
               "'./%s 50'\n",
               argv[0]);
        return 1;
    }

    char* endptr;
    long int number = strtol(argv[1], &endptr, 10);

    if (*endptr != '\0') {
        fprintf(stderr, "A megadott paraméter szám nem helyes egész érték!\n");
        return 1;
    } else if (number < 10) {
        fprintf(
            stderr,
            "A megadott paraméter túl kicsi (legalább 10 széles legyen)!\n");
        return 1;
    }

    int maxWidth = number > INT_MAX ? INT_MAX : (int)number;
    printf("A beállított max szélesség: %d\n\n", maxWidth);

    printf(
        "Good day to you, fine sir/madam! \nWelcome to our trusty transaction "
        "contraption. \nKindly brace yourself for an experience smoother than "
        "a well-aged cup of Yorkshire tea. \nSo, how may we assist you today? "
        "\nNeed a pound or two for the trolley? \nOr mayhaps you're here for a "
        "robust rendezvous with your account details? \nFear not, this humble "
        "machine is at your service, ready to assist faster than a fox running "
        "late for tea. \nMind the buttons now, they're a bit ticklish!\n");

    int nyugtaCount = 1;
    BEOLVASAS_ALLAPOT allapot = NEV;

    for (;;) {
        NYUGTA nyugta;
        nyugta.sorszam = nyugtaCount++;
        nyugta.tetelCount = 0;
        nyugta.tetelek = NULL;
        nyugta.osszesites = NULL;

        PSZ_TETEL* tetel = malloc(sizeof(PSZ_TETEL));
        tetel->f_nev = NULL;
        tetel->f_db = 0;
        tetel->f_ar = 0;

        while (allapot != KOVETKEZO) {
            switch (allapot) {
            default:
                fprintf(stderr, "Hiba történt beolvasás közben, elérhetetlen "
                                "kódrészlet!\n");
                return 1;
            case NEV:
                printf("Kérem a tétel nevét: ");

                // Remove the old name if it exists
                if (tetel->f_nev != NULL) {
                    free(tetel->f_nev);
                }

                tetel->f_nev = read_tetel_nev();
                allapot = DB;
                break;
            case DB:
                printf("Kérem a darabszámot: ");
                tetel->f_db = read_tetel_db();
                allapot = AR;
                break;
            case AR:
                printf("Kérem az árat: ");
                tetel->f_ar = read_tetel_ar();
                allapot = MENTES;
                break;
            case MENTES:
                printf("A tétel neve: %s\n", tetel->f_nev);
                printf("A darabszám: %d\n", tetel->f_db);
                printf("Az ár: %ld\n", tetel->f_ar);
                printf("Kérem ellenőrizze a fenti adatokat és válassza meg a "
                       "következő műveletet!\n");
                printf("Szeretné menteni az adatokat? (i/N)\n");

                char inputSaveChar = '\0';
                while (inputSaveChar != 'i' && inputSaveChar != 'N') {
                    if (inputSaveChar != '\0') {
                        printf("Kérem i vagy N betűt adjon meg!\n");
                    }
                    inputSaveChar = read_char();
                }

                if (inputSaveChar == 'i') {
                    // save existing
                    nyugta.tetelek =
                        realloc(nyugta.tetelek,
                                sizeof(PSZ_TETEL*) * (nyugta.tetelCount + 1));
                    nyugta.tetelek[nyugta.tetelCount] = tetel;
                    nyugta.tetelCount++;

                    // create new
                    tetel = malloc(sizeof(PSZ_TETEL));
                }

                allapot = ATMENET;
            case ATMENET:
                printf("--------------------\n");
                printf("Kérem válassza meg a következő műveletet!\n");
                printf("1. Új érték felvitele\n");
                printf("2. Nyugta nyomtatás \n");
                printf("3. Új nyugta kezdés\n");
                printf("4. Kilépés\n");

                char inputAtmenetChar = '\0';
                while (inputAtmenetChar != '1' && inputAtmenetChar != '2' &&
                       inputAtmenetChar != '3' && inputAtmenetChar != '4') {
                    if (inputAtmenetChar != '\0') {
                        printf("Kérem a menüpont számai közül válasszon!\n");
                    }
                    inputAtmenetChar = read_char();
                }

                if (inputAtmenetChar == '1') {
                    allapot = NEV;
                } else if (inputAtmenetChar == '2') {
                    // calculate osszesites

                    print_nyugta(maxWidth, &nyugta);
                } else if (inputAtmenetChar == '3') {
                    allapot = KOVETKEZO;
                } else {
                    printf(
                        "\n\nWell, there we are then. \nJob done and dusted, "
                        "smoother than a fresh jar of Marmite, wouldn't you "
                        "say? \nThank you kindly for using our services. "
                        "\nWe've been more chuffed than a bobby with a fresh "
                        "truncheon to assist you today. \nRemember, next time "
                        "you're in a pickle, or simply need a quid or two, our "
                        "trusty machine will be right here waiting. \nJust "
                        "don't forget to pop by and say 'ello! \nCheerio now, "
                        "and off you trot. \nMind the gap and keep calm and "
                        "carry on, as they say!");
                    exit(0);
                }

                break;
            }
        }

        // free nyugta
        nyugtaCount++;
        allapot = NEV;
        for (int i = 0; i < nyugta.tetelCount; i++) {
            free(nyugta.tetelek[i]);
        }
        free(nyugta.tetelek);
    }
}
