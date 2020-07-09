#ifndef TEST_H
#define TEST_H

/**
 * Reports error and exits immediately on test. 
 **/
void report_error();

/**
 * Reports success and exits immediately on test. 
 **/
void report_success();

/**
 * Reports error and exits immediately when cond is false on test.
 * 
 * @param cond Test condition. 
 **/
static inline void assert_test(bool cond) {
    if (!cond)
        report_error();
}

/**
 * Main test function. Should be defined(implemented) per all test codes.
 * NOTE: All test functions should call report_success or report_error on exit.
 **/
void test_main();

#endif