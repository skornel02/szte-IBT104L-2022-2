#include "BillentyuTest.h"
#include "Billentyu.h"

#include <CUnit/CUnit.h>

static void write_input(FILE* file, char* input) {
    for (int i = 0; input[i] != '\0'; ++i) {
        fprintf(file, "%c\n", input[i]);
    }
}

static void test_read_tetel_nev_short() {
    FILE* input = fopen("BillenytuTest.txt", "w");
    CU_ASSERT_PTR_NOT_NULL_FATAL(input);

    write_input(input, "20"); // add name then ok

    fclose(input);
    freopen("BillenytuTest.txt", "r", stdin);

    char* result = read_tetel_nev();

    CU_ASSERT_STRING_EQUAL_FATAL(result, "a")
}

static void test_read_tetel_nev_medium() {
    FILE* input = fopen("BillenytuTest.txt", "w");
    CU_ASSERT_PTR_NOT_NULL_FATAL(input);

    write_input(input, "77772580"); // add name then ok

    fclose(input);
    freopen("BillenytuTest.txt", "r", stdin);

    char* result = read_tetel_nev();

    CU_ASSERT_STRING_EQUAL_FATAL(result, "sajt")
}

CU_TestInfo billentyu_tests[] = {
        {"read_tetel_nev_short",               test_read_tetel_nev_short},
        {"read_tetel_nev_medium",               test_read_tetel_nev_medium},
        CU_TEST_INFO_NULL
};
