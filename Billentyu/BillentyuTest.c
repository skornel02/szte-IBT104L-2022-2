#include "BillentyuTest.h"
#include "Billentyu.h"

#include <CUnit/CUnit.h>
#include <stdlib.h>

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

static void test_read_tetel_nev_long() {
    FILE* input = fopen("BillenytuTest.txt", "w");
    CU_ASSERT_PTR_NOT_NULL_FATAL(input);

    write_input(input, "55777886755544415577788675554440"); // add name then ok

    fclose(input);
    freopen("BillenytuTest.txt", "r", stdin);

    char* result = read_tetel_nev();

    CU_ASSERT_STRING_EQUAL_FATAL(result, "krumpli krumpli")

    free(result);
}

static void test_map_number_to_char() {
    char result = map_number_to_char(2, 1); // 2-es szám, 1 db

    CU_ASSERT_EQUAL(result, 'a');
}

static void test_read_char() {
    FILE* input = fopen("BillenytuTest.txt", "w");
    CU_ASSERT_PTR_NOT_NULL_FATAL(input);

    write_input(input, "1");

    fclose(input);
    freopen("BillenytuTest.txt", "r", stdin);

    char result = read_char();
    CU_ASSERT_EQUAL(result, '1');
}

static void test_read_tetel_num() {
    FILE* input = fopen("BillenytuTest.txt", "w");
    CU_ASSERT_PTR_NOT_NULL_FATAL(input);

    fprintf(input, "%s\n", "200");

    fclose(input);
    freopen("BillenytuTest.txt", "r", stdin);

    int result = read_tetel_num();
    CU_ASSERT_EQUAL(result, 200);
}

CU_TestInfo billentyu_tests[] = {
        {"read_tetel_nev_short",               test_read_tetel_nev_short},
        {"read_tetel_nev_medium",               test_read_tetel_nev_medium},
        {"test_read_tetel_nev_long",               test_read_tetel_nev_long},
        {"test_map_number_to_char",               test_map_number_to_char},
        {"test_read_char",               test_read_char},
        {"test_read_tetel_num",               test_read_tetel_num},
        CU_TEST_INFO_NULL
};
