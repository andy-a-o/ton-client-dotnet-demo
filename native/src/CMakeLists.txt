include_directories(.)

add_library(testlib SHARED test.c)

set_target_properties(testlib PROPERTIES
        PUBLIC_HEADER "../include/test.h"
        C_VISIBILITY_PRESET hidden
        COMPILE_DEFINITIONS "TEST_DLL;TEST_DLL_EXPORTS"
        VERSION 1.0.0
        SOVERSION 1)
