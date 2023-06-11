#include "CommonTest.h"
#include "NyomtatoTest.h"
#include "Kaszas/KaszasTest.h"
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

CU_SuiteInfo pnm_suites[] = {
        {"Nyomtato", NULL, NULL, NULL, NULL, nyomtato_tests},
        {"Common", NULL, NULL, NULL, NULL, common_tests},
        {"Kaszas", NULL, NULL, NULL, NULL, kaszas_tests},
        CU_SUITE_INFO_NULL
};

/**
 * Ez a fő program, ami a teszteket futtatja.
 * <br>
 * A tesztek futtathatóak kézzel is (preferált), vagy
 * lehetőség van a `make test` paranccsal is futtatni.
 *
 * @author Stefán Kornél
 */
int main() {
    if (CU_initialize_registry() != CUE_SUCCESS) {
        return -1;
    };
    if (CU_register_suites(pnm_suites) != CUE_SUCCESS) {
        return -1;
    };
#ifdef DEBUG
    CU_basic_set_mode(CU_BRM_VERBOSE);
#else
    CU_basic_set_mode(CU_BRM_NORMAL);
#endif
    CU_basic_run_tests();
    unsigned int errorCount =  CU_get_number_of_failures();
    CU_cleanup_registry();
    return errorCount == 0 ? 0 : -1;
}
