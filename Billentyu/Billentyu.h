#pragma once

#include "Common.h"

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
 * Beolvassa a tétel darabszámát.
 * <br>
 * Ezt interaktívan a felhasználóval viszi végre.
 * <br>
 * Fontos:
 * <ul>
 * <li> A darabszám nem lehet negatív, sem nulla. </li>
 * <li> A maximum értéke a platform függő legnagyobb int érték. </li>
 * <li> A standard input / output feletti irányítást átveszi. </li>
 * </ul>
 *
 * @return Egy pozitív szám.
 * @author Horváth Gergely Zsolt
 */
int read_tetel_db();

/**
 * Beolvassa a tétel fogyasztói árát.
 * <br>
 * Ezt interaktívan a felhasználóval viszi végre.
 * <br>
 * Fontos:
 * <ul>
 * <li> A fogyasztói ár nem lehet negatív, sem nulla. </li>
 * <li> A maximum értéke a platform függő legnagyobb long int érték. </li>
 * <li> A standard input / output feletti irányítást átveszi. </li>
 * </ul>
 *
 * @return Egy pozitív (nagy) szám.
 * @author Horváth Gergely Zsolt
 */
long int read_tetel_ar();

typedef struct {
    int numbers[4];
    unsigned int numLength;
    char character;
}  CONTAINER;

typedef struct {
    CONTAINER* items;
    unsigned int size;
    unsigned int free;
} Array;

// TODO: Comment
Array create_array(unsigned int size);

// TODO: comment
char map_number_to_char(unsigned short number, unsigned short shift);

// Tömbkezelése
// Ha az előző karaktertől eltér, kezdjen új blokkot,
// vagy ha 1-7 esetén 3 a numlength, 8-9 esetén 4
void check_array(Array* array, int input, int lastNum);

void grow_array(Array* array);

// Ellenőrzi a számot
int is_correct_input(int input);

// String összefűzése, miután le lett zárva a tétel neve
char* join_tetel_nev(Array* array);