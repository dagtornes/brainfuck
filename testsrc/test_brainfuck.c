#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "bfscan.h"

void test_program_back(const char *program, int start_ip, int expect_ip)
{
    int found_ip = scan_back(start_ip, program);
    assert_int_equal(found_ip, expect_ip);
}

static void test_programs_back(void **state)
{
    test_program_back("[]", 1, 0);
    test_program_back("[[]]", 3, 1);
    test_program_back("[[]]", 2, 1);
    test_program_back("[1[34]678]", 9, 0);
}

void test_program_fwd(const char *program, int start_ip, int expect_ip)
{
    int found_ip = scan_fwd(start_ip, program);
    assert_int_equal(found_ip, expect_ip);
}

static void test_programs_fwd(void **state)
{
    test_program_fwd("[]", 0, 1);
    test_program_fwd("[[]]", 0, 3);
    test_program_fwd("[.]", 0, 2);
    test_program_fwd("[.[].]", 0, 5);
    test_program_fwd("[[]]", 1, 2);
}

int main(void)
{
    const UnitTest tests[] = {
        unit_test(test_programs_fwd),
        unit_test(test_programs_back),
    };

    return run_tests(tests);
}
