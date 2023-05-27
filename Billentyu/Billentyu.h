#pragma once

#include "CommonTypes.h"

/**
 * @deprecated
 */
char read_char();

/**
 * @deprecated
 */
char test_char();

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
