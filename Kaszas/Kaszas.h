#pragma once

#include "Common.h"

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
 *
 * @authors Horváth Gergely
 * @authors Stefán Kornél
 * @authors Vass Kinga
*/
int main(int argc, char* argv[]);

/**
 * Kiírunk egy kellemesen britt üdvözlő üzenetet.
 * <br>
 * Sajnos csak idegennyelven beszél a gép, de cserébe ízléses a humora.
 *
 * @author titok
 */
static void print_greeting();

/**
 * Kiírjuk a felhasználónak, hogy most kell eldöntenie, hogy menteni szeretné-e
 * az általa létrehozott bejegyzést, vagy elvetni.
 */
static void print_save_prompt(PSZ_TETEL* tetel);

/**
 * Beolvassuk a felhasználótól, hogy menteni szeretné-e az általa létrehozott
 * bejegyzést, vagy elvetni.
 * @return boolean, hogy menteni szeretné-e az általa létrehozott bejegyzést, vagy elvetni.
 */
static int input_should_save();

/**
 * Kiírja a felhasználónak, hogy mik a következő műveletek, amiket elvégezhet.
 */
static void print_next_action();

/**
 * Kiírunk egy hasonlóan kellemes elbocsátó szép üzenetet..
 * <br>
 * Sajnos ez is csak anglisztikus akkordonok hangzik fel.
 *
 * @author titok
 */
static void print_goodbye();
