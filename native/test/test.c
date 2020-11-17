#include "test.h"
#include <stdarg.h>

void test() {
    tc_string_data_t str;
    int size = sizeof(tc_string_data_t);
    str.content = "{}";
    str.len = 2;
    test_log("calling tc_create_context({})");
    tc_string_handle_t *ptr = tc_create_context(str);
    if (ptr == NULL) {
        test_log("tc_create_context({}) returned NULL ptr");
        return;
    }
    test_log("calling tc_read_string(ptr)");
//    tc_string_data_t result = tc_read_string(ptr);
//    test_log("tc_read_string(ptr) returned str data of length %d", result.len);
//    log_test_str(result);
//
//    tc_destroy_string(ptr);
//    tc_destroy_context(1);
}

int main() {
    test();
    return 0;
}