#pragma once

#include <stdint.h>
#include <stdbool.h>

#if defined _WIN32 || defined __CYGWIN__
    #define TEST_HELPER_DLL_IMPORT __declspec(dllimport)
    #define TEST_HELPER_DLL_EXPORT __declspec(dllexport)
    #define TEST_HELPER_DLL_LOCAL
#else
#if __GNUC__ >= 4
    #define TEST_HELPER_DLL_IMPORT __attribute__ ((visibility ("default")))
    #define TEST_HELPER_DLL_EXPORT __attribute__ ((visibility ("default")))
    #define TEST_HELPER_DLL_LOCAL  __attribute__ ((visibility ("hidden")))
#else
    #define TEST_HELPER_DLL_IMPORT
    #define TEST_HELPER_DLL_EXPORT
    #define TEST_HELPER_DLL_LOCAL
#endif // __GNUC__ >= 4
#endif // defined _WIN32 || defined __CYGWIN__

// Now we use the generic helper definitions above to define TEST_API and TEST_INTERNAL.
// TEST_API is used for the public API symbols. It either DLL imports or DLL exports (or does nothing for static build)
// TEST_INTERNAL is used for non-api symbols.

#ifdef TEST_DLL // defined if TEST is compiled as a DLL
#ifdef TEST_DLL_EXPORTS // defined if we are building the TEST DLL (instead of using it)
    #define TEST_API TEST_HELPER_DLL_EXPORT
#else
    #define TEST_API TEST_HELPER_DLL_IMPORT
#endif // TEST_DLL_EXPORTS
    #define TEST_INTERNAL TEST_HELPER_DLL_LOCAL
#else // TEST_DLL is not defined: this means TEST is a static lib.
    #define TEST_API
    #define TEST_INTERNAL
#endif // TEST_DLL

typedef struct {
    const char *content;
    uint32_t len;
} test_string_data_t;

typedef struct test_string_handle_t test_string_handle_t;

enum test_response_types_t {
    test_response_success = 0,
    test_response_error = 1,
    test_response_nop = 2,
    test_response_custom = 100,
};

typedef void (*test_response_handler_t)(
        uint32_t request_id,
        test_string_data_t params_json,
        uint32_t response_type,
        bool finished);

#ifdef __cplusplus
extern "C"
{
#endif

TEST_API void test_log(const char *fmt, ...);

TEST_API test_string_handle_t *test_create_context(test_string_data_t config);

TEST_API void test_destroy_context(uint32_t context);

TEST_API void test_request(
        uint32_t context,
        test_string_data_t function_name,
        test_string_data_t function_params_json,
        uint32_t request_id,
        test_response_handler_t response_handler);

TEST_API test_string_handle_t *test_request_sync(
        uint32_t context,
        test_string_data_t function_name,
        test_string_data_t function_params_json);

TEST_API test_string_data_t test_read_string(const test_string_handle_t *handle);
TEST_API void test_read_string_tmp(const test_string_handle_t *handle);

TEST_API void test_destroy_string(const test_string_handle_t *handle);

TEST_API void log_test_str(test_string_data_t str);

#ifdef __cplusplus
} // extern "C"
#endif