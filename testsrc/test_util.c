#include <CUnit/Basic.h>
#include "util.h"

void test_min()
{
    CU_ASSERT_EQUAL(min(1, 2), 1);
    CU_ASSERT_EQUAL(min(-1, -2), -2);
    CU_ASSERT_EQUAL(min(10, 10), 10);
}

void test_max()
{
    CU_ASSERT_EQUAL(max(1, 2), 2);
    CU_ASSERT_EQUAL(max(-1, -2), -1);
    CU_ASSERT_EQUAL(max(5, 10), 10);
}

void test_clamp()
{
    CU_ASSERT_EQUAL(clamp(5, 0, 10), 5);
    CU_ASSERT_EQUAL(clamp(-1, 0, 1), 0);
    CU_ASSERT_EQUAL(clamp(0, 0, 1), 0);
    CU_ASSERT_EQUAL(clamp(10, 0, 2), 2);
    CU_ASSERT_EQUAL(clamp(4, -3, -2), -2);
}

void test_strdup()
{
    const char *expected = "asdf, foo, bar";
    const char *actual = strdup(expected);
    CU_ASSERT_STRING_EQUAL(actual, expected);
    free(actual);
}

CU_pSuite make_util_suite()
{
    CU_pSuite suite = CU_add_suite("Utils suite", NULL, NULL);
    if (suite != NULL) {
        CU_add_test(suite, "test min", test_min);
        CU_add_test(suite, "test max", test_max);
        CU_add_test(suite, "text clamp", test_clamp);
        CU_add_test(suite, "strdup", test_strdup);
    }
    return suite;
}
