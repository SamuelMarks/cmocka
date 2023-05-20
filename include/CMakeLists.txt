project(cmocka-header C)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmocka_version.h.cmake
               ${CMAKE_CURRENT_BINARY_DIR}/cmocka_version.h
               @ONLY)

set(Header_Files "cmocka.h" "cmocka_pbc.h" "${CMAKE_CURRENT_BINARY_DIR}/cmocka_version.h")

if (MSVC_VERSION STRLESS "1600") # MSVC 2010
    # cmocka needs stdint.h to be `#include`able without patching cmocka
    file(COPY
            "${CMAKE_SOURCE_DIR}/include/cmocka_stdbool.h"
            "${CMAKE_SOURCE_DIR}/include/cmocka_stdint.h"
            DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
    file(RENAME "${CMAKE_CURRENT_BINARY_DIR}/cmocka_stdbool.h"
            "${CMAKE_CURRENT_BINARY_DIR}/stdbool.h")
    file(RENAME "${CMAKE_CURRENT_BINARY_DIR}/cmocka_stdint.h"
            "${CMAKE_CURRENT_BINARY_DIR}/stdint.h")
    list(APPEND Header_Files
            "${CMAKE_CURRENT_BINARY_DIR}/stdbool.h"
            "${CMAKE_CURRENT_BINARY_DIR}/stdint.h")
endif (MSVC_VERSION STRLESS "1600")

install(FILES
            ${Header_Files}
        DESTINATION
            ${CMAKE_INSTALL_INCLUDEDIR}
        COMPONENT
            ${PROJECT_NAME})
