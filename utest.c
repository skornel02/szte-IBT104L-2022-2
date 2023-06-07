//
// Created by Kornel on 6/7/2023.
//

#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

CU_SuiteInfo pnm_suites[] = {

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