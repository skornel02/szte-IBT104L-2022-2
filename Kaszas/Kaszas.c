#include <stdio.h>
#include "Billentyu.h"
#include "Nyomtato.h"

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
int main(int argc, char* argv[])
{
    // TODO: check arg count = 1, save it as int. !!Potential security breach
    int maxWidth = 100;

    // TODO: Greet the user with a nice british accent.

    BEOLVASAS_ALLAPOT allapot = NEV;

    // TODO: Start with the first item

    PSZ_TETEL a;
    a.f_db = 10;
	print_char(read_char());
    print_char(test_char());
	printf("Szia vilag! %d\n", a.f_db);
	return 0;
}