#include <CUnit/CUnit.h>
#include "Kaszas.h"
#include <stdio.h>

/**
 * A teszt kimenet max szélessége.
 * <br>
 * Szöveg típusú
 */
#define TEST_WIDTH "25"

static void add_item(FILE* file, char* name, int quantity, int price) {
    fprintf(file, "%s\n", name);
    fprintf(file, "%d\n", quantity);
    fprintf(file, "%d\n", price);
    fprintf(file, "i\n");
}

static void write_command(FILE* file, char command) {
    fprintf(file, "%c\n", command);
}

static void test_kaszas() {
    FILE* input = fopen("KaszasTestInput.txt", "w");
    CU_ASSERT_PTR_NOT_NULL_FATAL(input);

    add_item(input, "Kenyer", 2, 200);
    write_command(input, 'i'); // save
    write_command(input, '1'); // add new
    add_item(input, "Tej", 1, 300);
    write_command(input, 'i'); // save
    write_command(input, '1'); // add new
    add_item(input, "Sajtttt", 1, 500);
    write_command(input, 'n'); // decline
    write_command(input, '2'); // print

    FILE* nyugta1 = fopen("1.txt", "r");
    CU_ASSERT_PTR_NOT_NULL_FATAL(nyugta1)


    write_command(input, '3');
    add_item(input, "Sajt", 1, 500);
    write_command(input, 'i'); // save
    write_command(input, '2'); // print

    FILE* nyugta2 = fopen("2.txt", "r");
    CU_ASSERT_PTR_NOT_NULL_FATAL(nyugta2)

    write_command(input, '4'); //exit

    fclose(input);
    freopen("KaszasTestInput.txt", "r", stdin);

    int result = program(2, (char*[]){"Kaszas.exe", TEST_WIDTH});

    CU_ASSERT_EQUAL(result, 0)
}

CU_TestInfo kaszas_tests[] = {
    {"integration_test_kaszas_app",               test_kaszas},
    CU_TEST_INFO_NULL
};

