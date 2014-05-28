#include <CUnit/Basic.h>
#include "bfscan.h"

CU_pSuite make_util_suite();

void test_programs_back()
{
    CU_ASSERT_EQUAL(scan_back(1, "[]"), 0);
    CU_ASSERT_EQUAL(scan_back(3, "[[]]"), 0);
    CU_ASSERT_EQUAL(scan_back(2, "[[]]"), 1);
    CU_ASSERT_EQUAL(scan_back(9, "[1[34]678]"), 0);
}

void test_programs_fwd()
{
    CU_ASSERT_EQUAL(scan_fwd(0, "[]"), 1);
    CU_ASSERT_EQUAL(scan_fwd(0, "[[]]"), 3);
    CU_ASSERT_EQUAL(scan_fwd(0, "[.]"), 2);
    CU_ASSERT_EQUAL(scan_fwd(0, "[.[].]"), 5);
    CU_ASSERT_EQUAL(scan_fwd(1, "[[]]"), 2);
}

void test_programs_unbalanced()
{
    CU_ASSERT_EQUAL(scan_fwd(0, "["), -1);
}

CU_pSuite make_scan_suite()
{
    CU_pSuite suite = CU_add_suite("Scan suite", NULL, NULL);
    if (suite != NULL) {
        CU_add_test(suite, "test fwd scan", test_programs_fwd);
        CU_add_test(suite, "test back scan", test_programs_back);
        CU_add_test(suite, "test unbalanced scan", test_programs_unbalanced);
    }
    return suite;
}

int main(void)
{
    if (CU_initialize_registry() != CUE_SUCCESS) {
        return CU_get_error();
    }

    CU_pSuite scan_suite = make_scan_suite();
    if (scan_suite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_pSuite util_suite = make_util_suite();
    if (util_suite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }


    CU_basic_set_mode(CU_BRM_NORMAL);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
