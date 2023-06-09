#include "Nyomtato.h"
#include "Common.h"

#include <CUnit/CUnit.h>
#include <malloc.h>

#define REALISTIC_MIN_WIDTH 12

/**
 * Teszteljük, hogy a nyugta fájlok tényleg létrejönnek-e.
 * <br>
 * Továbbá azt, hogy egy realisztikus méret esetén a nyugta
 * fájlokban lévő oszlopok száma megfelelő-e.
 */
static void test_print_nyugta() {
    for (int width = 1; width < 25 ; width++) {
        NYUGTA nyugta;
        nyugta.sorszam = width;

        nyugta.tetelCount = 2;
        nyugta.tetelek = malloc(sizeof(PSZ_TETEL *) * nyugta.tetelCount);
        nyugta.tetelek[0] = malloc(sizeof(PSZ_TETEL));
        nyugta.tetelek[0]->f_nev = "Kifliaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
        nyugta.tetelek[0]->f_db = 2;
        nyugta.tetelek[0]->f_ar = 50;
        nyugta.tetelek[1] = malloc(sizeof(PSZ_TETEL));
        nyugta.tetelek[1]->f_nev = "Pogacsa";
        nyugta.tetelek[1]->f_db = 2;
        nyugta.tetelek[1]->f_ar = 50;

        nyugta.osszesites = 100;

        print_nyugta(width, &nyugta);

        free(nyugta.tetelek[0]);
        free(nyugta.tetelek[1]);
        free(nyugta.tetelek);

        char filename[30];
        sprintf(filename, "%d.txt", nyugta.sorszam);
        FILE *fp = fopen(filename, "r");
        CU_ASSERT_PTR_NOT_NULL(fp);

        if (REALISTIC_MIN_WIDTH <= width) {
            char line[100];
            while (fgets(line, 100, fp)) {
                CU_ASSERT_EQUAL_FATAL(strlen(line), width + 2)
            }
        }
    }
}

static void test_number_length() {
    CU_ASSERT_EQUAL(getNumbersLength(0), 1);
    CU_ASSERT_EQUAL(getNumbersLength(1), 1);
    CU_ASSERT_EQUAL(getNumbersLength(10), 2);
    CU_ASSERT_EQUAL(getNumbersLength(100), 3);
    CU_ASSERT_EQUAL(getNumbersLength(1000), 4);
    CU_ASSERT_EQUAL(getNumbersLength(10000), 5);
    CU_ASSERT_EQUAL(getNumbersLength(100000), 6);
    CU_ASSERT_EQUAL(getNumbersLength(1000000), 7);
    CU_ASSERT_EQUAL(getNumbersLength(10000000), 8);
    CU_ASSERT_EQUAL(getNumbersLength(100000000), 9);
    CU_ASSERT_EQUAL(getNumbersLength(1000000000), 10);
    CU_ASSERT_EQUAL(getNumbersLength(10000000000), 11);
    CU_ASSERT_EQUAL(getNumbersLength(100000000000), 12);
    CU_ASSERT_EQUAL(getNumbersLength(1000000000000), 13);
    CU_ASSERT_EQUAL(getNumbersLength(10000000000000), 14);
    CU_ASSERT_EQUAL(getNumbersLength(100000000000000), 15);
    CU_ASSERT_EQUAL(getNumbersLength(1000000000000000), 16);
    CU_ASSERT_EQUAL(getNumbersLength(10000000000000000), 17);
    CU_ASSERT_EQUAL(getNumbersLength(100000000000000000), 18);
    CU_ASSERT_EQUAL(getNumbersLength(1000000000000000000), 19);
}

CU_TestInfo nyomtato_tests[] = {
        {"print_nyugta",               test_print_nyugta},
        {"number_length",              test_number_length},
        CU_TEST_INFO_NULL
};
