#include <test.hpp>
#include <uapi/string.hpp>
#include <kapi/cpuinfo.hpp>

void test_main() {
    // https://github.com/Hhro/lets_make_kernel/issues/25, regression test. 
    assert_test(memcmp(cpu_info.cpu_vendor_id(), "GenuineIntel", sizeof("GenuineIntel") - 1) == 0);
    report_success();
}