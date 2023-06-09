#include "CommonTest.h"
#include "Common.h"
#include <stdlib.h>

static void test_free_nyugta_without_osszesites() {
    PSZ_TETEL **tetelek = malloc(sizeof(PSZ_TETEL*) * 2);
    PSZ_TETEL *tetel1 = malloc(sizeof(PSZ_TETEL));
    tetel1->f_nev = malloc(sizeof(char) * 7);
    strncpy(tetel1->f_nev, "tetel1", 7);
    tetel1->f_db = 1;
    tetel1->f_ar = 1;
    PSZ_TETEL *tetel2 = malloc(sizeof(PSZ_TETEL));
    tetel2->f_nev = malloc(sizeof(char) * 7);
    strncpy(tetel2->f_nev, "tetel2", 7);
    tetel2->f_db = 2;
    tetel2->f_ar = 2;
    tetelek[0] = tetel1;
    tetelek[1] = tetel2;

    NYUGTA nyugta;
    nyugta.tetelCount = 2;
    nyugta.tetelek = tetelek;

    free_nyugta_members(&nyugta);
}

static void test_calculate_osszesites() {
    int ar1 = 420;
    int ar2 = 720;

    PSZ_TETEL **tetelek = malloc(sizeof(PSZ_TETEL*) * 2);
    PSZ_TETEL *tetel1 = malloc(sizeof(PSZ_TETEL));
    tetel1->f_nev = "tetel1";
    tetel1->f_db = 1;
    tetel1->f_ar = ar1;
    PSZ_TETEL *tetel2 = malloc(sizeof(PSZ_TETEL));
    tetel2->f_nev = "tetel2";
    tetel2->f_db = 2;
    tetel2->f_ar = ar2;
    tetelek[0] = tetel1;
    tetelek[1] = tetel2;

    long int osszesites = calculate_osszesites(tetelek, 2);
    CU_ASSERT_EQUAL(osszesites, ar1 + ar2);

    free(tetelek);
    free(tetel1);
    free(tetel2);
}

static void test_free_nyugta() {
    PSZ_TETEL **tetelek = malloc(sizeof(PSZ_TETEL*) * 2);
    PSZ_TETEL *tetel1 = malloc(sizeof(PSZ_TETEL));
    tetel1->f_nev = malloc(sizeof(char) * 7);
    strncpy(tetel1->f_nev, "tetel1", 7);
    tetel1->f_db = 1;
    tetel1->f_ar = 1;
    PSZ_TETEL *tetel2 = malloc(sizeof(PSZ_TETEL));
    tetel2->f_nev = malloc(sizeof(char) * 7);
    strncpy(tetel2->f_nev, "tetel2", 7);
    tetel2->f_db = 2;
    tetel2->f_ar = 2;
    tetelek[0] = tetel1;
    tetelek[1] = tetel2;

    NYUGTA nyugta;
    nyugta.tetelCount = 2;
    nyugta.tetelek = tetelek;
    nyugta.osszesites = calculate_osszesites(tetelek, 2);

    free_nyugta_members(&nyugta);
}

static void test_add_tetel_to_nyugta() {
    NYUGTA nyugta;
    nyugta.tetelCount = 0;
    nyugta.tetelek = NULL;

    PSZ_TETEL * tetel1 = malloc(sizeof(PSZ_TETEL));
    tetel1->f_nev = "tetel1";
    tetel1->f_db = 1;
    tetel1->f_ar = 1;

    PSZ_TETEL * tetel2 = malloc(sizeof(PSZ_TETEL));
    tetel2->f_nev = "tetel2";
    tetel2->f_db = 1;
    tetel2->f_ar = 1;

    CU_ASSERT_EQUAL(nyugta.tetelCount, 0);
    CU_ASSERT_PTR_NULL(nyugta.tetelek);

    add_tetel_to_nyugta(&nyugta, tetel1);
    CU_ASSERT_EQUAL(nyugta.tetelCount, 1);
    CU_ASSERT_PTR_NOT_NULL(nyugta.tetelek);
    CU_ASSERT_EQUAL(nyugta.tetelek[0], tetel1)

    add_tetel_to_nyugta(&nyugta, tetel2);
    CU_ASSERT_EQUAL(nyugta.tetelCount, 2);
    CU_ASSERT_PTR_NOT_NULL(nyugta.tetelek);
    CU_ASSERT_EQUAL(nyugta.tetelek[0], tetel1)

    free(tetel1);
    free(tetel2);
    free(nyugta.tetelek);
}

CU_TestInfo common_tests[] = {
        {"free_nyugta_members_without_osszesites",  test_free_nyugta_without_osszesites},
        {"calculate_osszesites",                    test_calculate_osszesites},
        {"free_nyugta_members",                     test_free_nyugta},
        {"add_tetel_to_nyugta",                     test_add_tetel_to_nyugta},
        CU_TEST_INFO_NULL
};
