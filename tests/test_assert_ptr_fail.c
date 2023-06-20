#include "config.h"

#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#if __STDC_VERSION__ < 199901L /* C99 */ || \
    defined(_MSC_VER) && _MSC_VER < 1600 /* MSVC 2010 */
#include <cmocka_stdint.h>
#else
#include <stdint.h>
#endif
#include <cmocka.h>

static void test_ptr_equal_fail(void **state)
{
    (void)state; /* unused */

    const char *my_pointer = "wurst";
    assert_ptr_equal(my_pointer, my_pointer + 1);
}

static void test_ptr_not_equal_fail(void **state)
{
    (void)state; /* unused */

    const char *my_pointer = "wurst";
    assert_ptr_not_equal(my_pointer, my_pointer);
}

static void test_null_fail(void **state)
{
    (void)state; /* unused */
    assert_null("wurst");
}

static void test_non_null_fail(void **state)
{
    (void)state; /* unused */
    const char *my_pointer = NULL;
    assert_non_null(my_pointer);
}

int main(void)
{
    const struct CMUnitTest ptr_tests[] = {
        cmocka_unit_test(test_ptr_equal_fail),
        cmocka_unit_test(test_ptr_not_equal_fail),
        cmocka_unit_test(test_null_fail),
        cmocka_unit_test(test_non_null_fail),
    };

    return cmocka_run_group_tests(ptr_tests, NULL, NULL);
}
