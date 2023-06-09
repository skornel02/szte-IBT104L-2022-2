//
// Created by Kornel on 6/7/2023.
//

#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include "NyomtatoTest.h"
#include "CommonTest.h"

CU_SuiteInfo pnm_suites[] = {
        {"Nyomtato", NULL, NULL, NULL, NULL, nyomtato_tests},
        {"Common", NULL, NULL, NULL, NULL, common_tests},
        CU_SUITE_INFO_NULL
};

int main() {
    if (CU_initialize_registry() != CUE_SUCCESS) {
        return -1;
    };
    if (CU_register_suites(pnm_suites) != CUE_SUCCESS) {
        return -1;
    };
    CU_basic_set_mode(CU_BRM_NORMAL);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}