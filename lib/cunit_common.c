#include "cunit_common.h"
#include "stdlib.h"
#include "stdio.h"
#include "CUnit/Basic.h"

void ts_init(c_unit_test_suite_t* ts, const char* description)
{
    memset(ts, 0x00, sizeof(c_unit_test_suite_t));
    strcpy(ts->description, description);
}

void ts_add_utest(c_unit_test_suite_t* ts, void (*utest_func)(void), const char* utest_description)
{
    c_unit_test_t* utest = &(ts->test_array[ts->nb_c_unit_test]);

    utest->func = utest_func;
    strcpy(utest->description, utest_description);

    (ts->nb_c_unit_test)++;
}

int register_ts(c_unit_test_suite_t *ts)
{
    CU_pSuite pSuite = NULL;
    int ix_utest;

    pSuite = CU_add_suite(ts->description, NULL, NULL);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* add the tests to the suite */
    for (ix_utest=0 ; ix_utest<ts->nb_c_unit_test ; ix_utest++)
    {
        c_unit_test_t* utest = &(ts->test_array[ix_utest]);
        if (NULL == CU_add_test(pSuite, utest->description, utest->func))
        {
            CU_cleanup_registry();
            return CU_get_error();
        }
    }

    return 0;
}
