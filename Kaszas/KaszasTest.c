#include <CUnit/CUnit.h>
#include "Kaszas.h"
#include "Billentyu.h"
#include <stdio.h>

/**
 * A teszt kimenet max szélessége.
 * <br>
 * Szöveg típusú
 */
#define TEST_WIDTH "25"

static void print_text_on_writer(FILE* file, char* text) {
    for (int i = 0; text[i] != '\0'; ++i) {
        int chCode = map_char_to_number(text[i]);
        int chOffset = map_char_to_offset(text[i]);
        for (int j = 0; j < chOffset; j++) {
            fprintf(file, "%d\n", chCode);
        }
    }
    fprintf(file, "0\n");
}

static void add_item(FILE* file, char* name, int quantity, int price) {
    print_text_on_writer(file, name);
    fprintf(file, "%d\n", quantity);
    fprintf(file, "%d\n", price);
    fprintf(file, "i\n");
}

static void write_command(FILE* file, char command) {
    fprintf(file, "%c\n", command);
}

static void test_kaszas() {
    FILE* input = fopen("KaszasTestInput.txt", "w");
    CU_ASSERT_PTR_NOT_NULL_FATAL(input)

    add_item(input, "kenyer", 2, 200);
    write_command(input, 'y'); // save
    write_command(input, '1'); // add new
    add_item(input, "tej", 1, 300);
    write_command(input, 'y'); // save
    write_command(input, '1'); // add new
    add_item(input, "sajtttt", 1, 500);
    write_command(input, 'N'); // decline
    write_command(input, '2'); // print

    write_command(input, '3');
    add_item(input, "sajt", 1, 500);
    write_command(input, 'y'); // save
    write_command(input, '2'); // print

    write_command(input, '4'); //exit

    fclose(input);
    freopen("KaszasTestInput.txt", "r", stdin);

    int result = program(2, (char*[]){"Kaszas.exe", TEST_WIDTH});

    FILE* nyugta1 = fopen("1.txt", "r");
    CU_ASSERT_PTR_NOT_NULL_FATAL(nyugta1)

    FILE* nyugta2 = fopen("2.txt", "r");
    CU_ASSERT_PTR_NOT_NULL_FATAL(nyugta2)

    CU_ASSERT_EQUAL(result, 0)
}

/**
 * A special test when the first input is not saved and the user immediately exits.
 */
static void string_regression_test() {
    FILE* input = fopen("KaszasTestInput.txt", "w");
    CU_ASSERT_PTR_NOT_NULL_FATAL(input)

    add_item(input, "kenyer", 2, 200);
    write_command(input, 'N'); // save
    write_command(input, '4'); // add new

    fclose(input);
    freopen("KaszasTestInput.txt", "r", stdin);

    int result = program(2, (char*[]){"Kaszas.exe", TEST_WIDTH});

    CU_ASSERT_EQUAL(result, 0)
}

CU_TestInfo kaszas_tests[] = {
    {"integration_test_kaszas_app",               test_kaszas},
    {"string_regression_test",                    string_regression_test},
    CU_TEST_INFO_NULL
};

