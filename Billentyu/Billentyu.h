#pragma once

#include "Common.h"

/**
 * Struct, ami képes eltárolni az együtt kezelendő számjegyeket,
 * illetve az általa tartalmazott számjegyek számát.
 */
typedef struct {
    int numbers[4];
    unsigned int numLength;
    char character;
}  CONTAINER;

/**
 * Tartalmaz egy tömböt, illetve a tartalmazott elemek számát
 * és a szabad helyet is.
 */
typedef struct {
    CONTAINER* items;
    int size;
    int free;
} Array;

/**
 * Beolvas egy karaktert.
 *
 * @return egy karakter.
 * @author Horváth Gergely
 */
char read_char();

/**
 * Beolvassa a tétel nevét.
 * <br>
 * Ezt interaktívan a felhasználóval viszi végre.
 * <br>
 * Fontos:
 * <ul>
 * <li> A tétel neve nem lehet üres. </li>
 * <li> A standard input / output feletti irányítást átveszi. </li>
 * <li> Csak angol abc kisbetűit tartalmazhatja a tétel neve. </li>
 * </ul>
 *
 * @return Visszatér egy pointerrel, ami egy heapen található szövegre (char array) mutat.
 * @author Horváth Gergely Zsolt
 */
char* read_tetel_nev();

/**
 * Beolvas egy a tételhez tartozó számot.
 * <br>
 * Ezt interaktívan a felhasználóval viszi végre.
 * <br>
 * Fontos:
 * <ul>
 * <li> A szám nem lehet negatív, sem nulla. </li>
 * <li> A maximum értéke 999.999.999; ennél nagyobb tételszám / ár estén a Ka$$za prémium verziója használatos. </li>
 * <li> A standard input / output feletti irányítást átveszi. </li>
 * </ul>
 *
 * @return Egy pozitív szám.
 * @author Horváth Gergely Zsolt
 */
int read_tetel_num();

/**
 * Létrehoz egy a telefonbillentyűzet szerű bemenet tárolására alkalmas tömböt.
 * @param size A tömb mérete.
 * @return Egy adott hosszúságú tömb.
 * @author Horváth Gergely Zsolt
 */
Array create_array(int size);

/**
 * Számot karakterré konvertál.
 * @param number Hanyas szám.
 * @param shift Hány darab van megadva a számból.
 * @return Az angol abc egy kisbetűje vagy szóköz.
 * @author Horváth Gergely Zsolt
 */
char map_number_to_char(unsigned short number, unsigned short shift);

/**
 * Ez az eljárás teszi lehetővé, hogy három (7-9 esetén négy) szám egy karakternek számítson.
 * @param array Az ellenőrizendő tömb.
 * @param input A felhazsnáló által megadott bemenet.
 * @param lastNum A legutóbbi bemenet.
 * @author Horváth Gergely Zsolt
 */
void check_array(Array *array, int input, int lastNum);

// Tömb növelése, ha nincs már hely
/**
 * A tömb megnövelése, ha nincs már benne hely.
 * @param array A megnövelni kívánt tömb.
 * @author Horváth Gergely Zsolt
 */
void grow_array(Array *array);

/**
 * Ellenőrzi, hogy a megadott feltételeknek eleget tesz-e a felhasználói bemenet.
 * @param input Az ellenőrizendő szám.
 * @return 0, ha helytelen a szám, 1 ha helyes.
 * @author Horváth Gergely Zsolt
 */
int is_correct_input(char input);

// String összefűzése, miután le lett zárva a tétel neve
/**
 * A lezárt tétel nevének összefűzése.
 * @param array A tömb, ami a név karaktereit tárolja.
 * @return Az összefűzött név.
 * @author Horváth Gergely Zsolt
 */
char* join_tetel_nev(Array *array);

/**
 * Ellenőrzi, hogy a megadott szám pozitív-e. Ha helytelen a szám, tájékoztatást ad.
 * @param input Az ellenőrizendő szám.
 * @return 0, ha nempozitív, 1 ha pozitív.
 * @author Horváth Gergely Zsolt
 */
int check_num(long int input);

/**
 * Beolvas egy pozitív egész számot.
 * @return
 * @author Horváth Gergely Zsolt
 */
long int scan_num();

/**
 * Kiírja a megadott számokat a képernyőre.
 * @param array A számokat tartalmazó tömb.
 * @author Horváth Gergely Zsolt
 */
void print_numbers(Array *array);

/**
 * Kiírja a megadott karaktereket a képernyőre.
 * @param array A karaktereket tartalmazó tömb.
 * @author Horváth Gergely Zsolt
 */
void print_characters(Array *array);

/**
 * Kirajzol a képernyőre egy billenytűzetet.
 * @author Horváth Gergely Zsolt
 */
void print_keyboard();