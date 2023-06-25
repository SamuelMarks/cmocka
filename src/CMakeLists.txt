project(cmocka-library C)

set(CMOCKA_PLATFORM_INCLUDE CACHE PATH "Path to include directory for cmocka_platform.h")
mark_as_advanced(CMOCKA_PLATFORM_INCLUDE)

set(CMOCKA_LINK_LIBRARIES
    ${CMOCKA_REQUIRED_LIBRARIES}
    CACHE INTERNAL "cmocka link libraries"
)

set(cmocka_SRCS
    cmocka.c
)

if (WIN32)
    set(cmocka_SRCS
        ${cmocka_SRCS}
        cmocka.def
    )
    set_source_files_properties(cmocka.def PROPERTIES HEADER_FILE_ONLY TRUE)
endif (WIN32)

add_library(cmocka ${cmocka_SRCS})

target_include_directories(cmocka
                           PRIVATE
                               ${CMOCKA_PLATFORM_INCLUDE}
                               ${cmocka_BINARY_DIR}
                           PUBLIC
                               $<BUILD_INTERFACE:${cmocka-header_SOURCE_DIR}>
                               $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include>
                               $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
                               $<INSTALL_INTERFACE:include>)

target_compile_options(cmocka
                       PRIVATE
                           ${DEFAULT_C_COMPILE_FLAGS}
                           -DHAVE_CONFIG_H)

target_compile_definitions(cmocka
                           PRIVATE
                               _GNU_SOURCE
                               _XOPEN_SOURCE=700)

if (CMOCKA_PLATFORM_INCLUDE)
    target_compile_options(cmocka
                           PRIVATE
                               -DCMOCKA_PLATFORM_INCLUDE)
endif()

target_link_libraries(cmocka PRIVATE ${CMOCKA_LINK_LIBRARIES})
set_target_properties(cmocka PROPERTIES
                      DEFINE_SYMBOL         CMOCKA_EXPORTS
                      VERSION               ${LIBRARY_VERSION}
                      SOVERSION             ${LIBRARY_SOVERSION}
                      LINK_FLAGS            "${DEFAULT_LINK_FLAGS}"
                      C_STANDARD            90
)
set(CMAKE_C_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN YES)

add_library(cmocka::cmocka ALIAS cmocka)

install(TARGETS cmocka
        EXPORT cmocka-targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        COMPONENT ${PROJECT_NAME})

include(GNUInstallDirs)
include(GenerateExportHeader)
set(_export_file "${CMAKE_CURRENT_BINARY_DIR}/cmocka_export.h")
generate_export_header(
        cmocka::cmocka
        EXPORT_FILE_NAME "${_export_file}"
        BASE_NAME "CMOCKA"
)

install(FILES
        "${_export_file}"
        DESTINATION
        "${CMAKE_INSTALL_INCLUDEDIR}"
        COMPONENT
        ${PROJECT_NAME})

install(EXPORT cmocka-targets
        NAMESPACE cmocka::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/cmocka)

if (UNIT_TESTING)
    # Internal library
    add_library(cmocka-static STATIC ${cmocka_SRCS})

    target_include_directories(cmocka-static
                               PRIVATE
                                   ${CMOCKA_PLATFORM_INCLUDE}
                                   ${cmocka_BINARY_DIR}
                               PUBLIC
                                   ${cmocka-header_SOURCE_DIR})


    target_compile_options(cmocka-static
                           PRIVATE
                               ${DEFAULT_C_COMPILE_FLAGS}
                               -DHAVE_CONFIG_H)

    target_compile_definitions(cmocka-static
                               PRIVATE
                                   _GNU_SOURCE
                                   _XOPEN_SOURCE=700)

    if (CMOCKA_PLATFORM_INCLUDE)
        target_compile_options(cmocka-static
                               PRIVATE
                                   -DCMOCKA_PLATFORM_INCLUDE)
    endif()

    target_link_libraries(cmocka-static PRIVATE ${CMOCKA_LINK_LIBRARIES})

    add_library(cmocka::static ALIAS cmocka-static)
endif()
