#include "test.h"
#include <stdarg.h>

void test() {
    test_string_data_t str;
    int size = sizeof(test_string_data_t);
    str.content = "{}";
    str.len = 2;
    test_log("calling test_create_context({})");
    test_string_handle_t *ptr = test_create_context(str);
    if (ptr == NULL) {
        test_log("test_create_context({}) returned NULL ptr");
        return;
    }
    test_log("calling test_read_string(ptr)");
//    test_string_data_t result = test_read_string(ptr);
//    test_log("test_read_string(ptr) returned str data of length %d", result.len);
//    log_test_str(result);
//
//    test_destroy_string(ptr);
//    test_destroy_context(1);
}

int main() {
    test();
    return 0;
}