add_library(proc_uptime proc_uptime.c)
target_include_directories(proc_uptime
        PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/src>
        $<INSTALL_INTERFACE:include>)

add_executable(uptime uptime.c)
target_compile_options(uptime
                       PRIVATE
                           ${DEFAULT_C_COMPILE_FLAGS}
                           -D_GNU_SOURCE
                           -D_XOPEN_SOURCE=600)
target_link_libraries(uptime proc_uptime)

set_property(TARGET
                 uptime
             PROPERTY
                 LINK_FLAGS
                     "${DEFAULT_LINK_FLAGS}")

add_cmocka_test(test_uptime
                SOURCES test_uptime.c
                COMPILE_OPTIONS ${DEFAULT_C_COMPILE_FLAGS} -D_GNU_SOURCE -D_XOPEN_SOURCE=600
                LINK_LIBRARIES cmocka::cmocka)
set_property(TARGET
                 test_uptime
             PROPERTY
                 LINK_FLAGS
                    "${DEFAULT_LINK_FLAGS} -Wl,--wrap=uptime")
