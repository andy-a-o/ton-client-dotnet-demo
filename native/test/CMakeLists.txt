enable_testing()

include_directories(. ../src)

add_executable(test_test test.c)
target_link_libraries(test_test testlib)
add_test(test_test test_test)

if (WIN32)
    set(TEST_EXTERNAL_LIB_RUNTIME_FILES ${CMAKE_BINARY_DIR}/src/testlib.dll)

    foreach (file IN LISTS TEST_EXTERNAL_LIB_RUNTIME_FILES)
        add_custom_command(
                TARGET test_test POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different ${file} ${CMAKE_BINARY_DIR}/test
                COMMENT "Copying shared lib ${file} to ${CMAKE_BINARY_DIR}/test")
    endforeach ()

endif()
