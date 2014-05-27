#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "bfscan.h"

static void test_scan_fwd(void **state)
{
    (void) state; // Unused
}

int main(void)
{
    const UnitTest tests[] = {
        unit_test(test_scan_fwd),
    };

    return run_tests(tests);
}
