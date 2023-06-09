#include "Billentyu.h"

#include <CUnit/CUnit.h>

static void test_read_tetel_nev() {
    // TODO: Átirányítani standard inputot és úgy tesztenlni fgv-t

    FILE *fp;
    char str[] = "7\n7\n7\n7\n2\n5\n8\nx\n";

    fp = fopen( "test.txt" , "w" );
    fwrite(str , 1 , sizeof(str) , fp );
    fclose(fp);

    freopen("test.txt", "r", stdin);

    char* sajt = "sajt";
    CU_ASSERT_EQUAL(read_tetel_nev(), sajt);
}

CU_TestInfo nyomtato_tests[] = {
        {"read_tetel_nev",               test_read_tetel_nev},
 //       {"number_length",              test_number_length},
        CU_TEST_INFO_NULL
};
