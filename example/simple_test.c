#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#if __STDC_VERSION__ < 199901L /* C99 */ || \
    defined(_MSC_VER) && _MSC_VER < 1600 /* MSVC 2010 */
#include <cmocka_stdint.h>
#else
#include <stdint.h>
#endif
#include <cmocka.h>

/* A test case that does nothing and succeeds. */
static void null_test_success(void **state) {
    (void) state; /* unused */
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(null_test_success),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
