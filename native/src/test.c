#include "test.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

#define LOG_FILENAME "test.log"
#define LOG_MEM_STR_FORMAT_BUFFER_SIZE 2048

struct test_string_handle_t {
    const char *str;
    int len;
};

char *mem_copy_str(const char *ptr) {
    size_t length = strlen(ptr);
    char *copy = malloc((length + 1) * sizeof(char));
    strncpy(copy, ptr, length + 1);
    return copy;
}

char *mem_copy_str_data(test_string_data_t str) {
    size_t length = str.len;
    char *copy = calloc((length + 1), sizeof(char));
    strncpy(copy, str.content, length);
    return copy;
}

void test_log(const char *fmt, ...) {
    va_list args;
            va_start(args, fmt);
    char buffer[LOG_MEM_STR_FORMAT_BUFFER_SIZE];
    vsnprintf(buffer, LOG_MEM_STR_FORMAT_BUFFER_SIZE, fmt, args);
            va_end(args);

    FILE *f = fopen(LOG_FILENAME, "a");
    fprintf(f, "%s\n", buffer);
    fclose(f);

    printf("Logged to %s: %s\n", LOG_FILENAME, buffer);
}

void log_test_str(test_string_data_t str) {
    char *data = mem_copy_str_data(str);
    test_log(data);
    free(data);
}

test_string_handle_t *test_create_context() {
    test_log("test_create_context called");
    test_string_handle_t *p = calloc(1, sizeof(test_string_handle_t));
    p->str = mem_copy_str("{\"result\":1}");
    p->len = strlen(p->str);
    test_log("len = %d", p->len);
    test_log("returning result %d (%d, \"%s\") from test_create_context()", p, p->str, p->str);
    return p;
}

void test_destroy_context(uint32_t context) {
    test_log("test_destroy_context called with argument: %d", context);
}

void test_request(
        uint32_t context,
        test_string_data_t function_name,
        test_string_data_t function_params_json,
        uint32_t request_id,
        test_response_handler_t response_handler) {
    char *name = mem_copy_str_data(function_name);
    char *params = mem_copy_str_data(function_params_json);
    test_log("test_request called with arguments: (%d, \"%s\", \"%s\", %d, %d)",
             context,
             name, params,
             request_id, response_handler);
    free(name);
    free(params);
}

test_string_handle_t *test_request_sync(
        uint32_t context,
        test_string_data_t function_name,
        test_string_data_t function_params_json) {

    char *name = mem_copy_str_data(function_name);
    char *params = mem_copy_str_data(function_params_json);
    test_log("test_request_sync called with arguments: (%d, \"%s\", \"%s\")",
             context,
             name, params);
    free(name);
    free(params);

    test_string_handle_t *p = calloc(1, sizeof(test_string_handle_t));
    p->str = mem_copy_str("{\"result\":\"OK\"}");
    p->len = strlen(p->str);
    test_log("returning result %d (\"%s\") from test_request_sync()", p, p->str);
    return p;
}

test_string_data_t test_read_string(const test_string_handle_t *handle) {
    test_log("test_read_string called with arguments: %d", handle);
    test_log("handle->str: %d", handle->str);
    test_log("handle->len: %d", handle->len);
    test_string_data_t result;
    result.content = handle->str;
    result.len = handle->len;
    char *copy = mem_copy_str_data(result);
    test_log("test_read_string returning \"%s\"", copy);
    free(copy);
    test_log("test_read_string done");
    return result;
}

void test_read_string_tmp(const test_string_handle_t *handle) {
    test_log("test_read_string_tmp called with arguments: %d", handle);
    test_log("handle->str: %d", handle->str);
    test_log("handle->len: %d", handle->len);
    test_string_data_t result;
    result.content = handle->str;
    result.len = handle->len;
    char *copy = mem_copy_str_data(result);
    test_log("test_read_string_tmp returning \"%s\"", copy);
    free(copy);
    test_log("test_read_string_tmp done");
}

void test_destroy_string(const test_string_handle_t *handle) {
    test_log("called test_destroy_string with argument: %d (\"%s\")", handle, handle->str);
    free((void *) handle->str);
    free((void *) handle);
}
