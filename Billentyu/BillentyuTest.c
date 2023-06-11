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

    CU_ASSERT_STRING_EQUAL(result, "a")

    free(result);
}

static void test_read_tetel_nev_medium() {
    FILE* input = fopen("BillenytuTest.txt", "w");
    CU_ASSERT_PTR_NOT_NULL_FATAL(input);

    write_input(input, "77772580"); // add name then ok

    fclose(input);
    freopen("BillenytuTest.txt", "r", stdin);

    char* result = read_tetel_nev();

    CU_ASSERT_STRING_EQUAL(result, "sajt")

    free(result);
}

static void test_read_tetel_nev_long() {
    FILE* input = fopen("BillenytuTest.txt", "w");
    CU_ASSERT_PTR_NOT_NULL_FATAL(input);

    write_input(input, "55777886755544415577788675554440"); // add name then ok

    fclose(input);
    freopen("BillenytuTest.txt", "r", stdin);

    char* result = read_tetel_nev();
    char* expected = "krumpli krumpli";

    printf("%s = %s\n", result, expected);
    CU_ASSERT_STRING_EQUAL(result, expected)

    free(result);
}

static void test_read_tetel_nev_very_long() {
    FILE* input = fopen("BillenytuTest.txt", "w");
    CU_ASSERT_PTR_NOT_NULL_FATAL(input);

    write_input(input, "55777886755544415577788675554441557778867555444155777886755544415577788675554441557778867555444155777886755544415577788675554440"); // add name then ok

    fclose(input);
    freopen("BillenytuTest.txt", "r", stdin);

    char* result = read_tetel_nev();
    char* expected = "krumpli krumpli krumpli krumpli krumpli krumpli krumpli krumpli";

    printf("%s = %s\n", result, expected);
    CU_ASSERT_STRING_EQUAL(result, expected)

    free(result);
}

static void test_map_number_to_char() {
    for (char ch = 'a'; ch <= 'z'; ++ch) {
        char result = map_number_to_char(map_char_to_number(ch), map_char_to_offset(ch)); // 2-es szám, 1 db
        printf("Testing %c -> %d,%d (%c)\n", ch, map_char_to_number(ch), map_char_to_offset(ch), result);
        CU_ASSERT_EQUAL(result, ch);
    }

    char ch = ' ';
    char result = map_number_to_char(map_char_to_number(ch), map_char_to_offset(ch)); // 2-es szám, 1 db
    printf("Testing %c -> %d,%d (%c)\n", ch, map_char_to_number(ch), map_char_to_offset(ch), result);
    CU_ASSERT_EQUAL(result, ch);
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

static void test_is_correct_input() {
    CU_ASSERT_TRUE(is_correct_input('1'));
    CU_ASSERT_TRUE(is_correct_input('9'));
}

static void test_incorrect_input() {
    CU_ASSERT_FALSE(is_correct_input('0'));
}

CU_TestInfo billentyu_tests[] = {
        {"read_tetel_nev_short",               test_read_tetel_nev_short},
        {"read_tetel_nev_medium",               test_read_tetel_nev_medium},
        {"test_read_tetel_nev_long",               test_read_tetel_nev_long},
        {"test_read_tetel_nev_very_long",   test_read_tetel_nev_very_long},
        {"test_map_number_to_char",               test_map_number_to_char},
        {"test_read_char",               test_read_char},
        {"test_read_tetel_num",               test_read_tetel_num},
        {"test_is_correct_input",               test_is_correct_input},
        {"test_incorrect_input",               test_incorrect_input},
        CU_TEST_INFO_NULL
};
