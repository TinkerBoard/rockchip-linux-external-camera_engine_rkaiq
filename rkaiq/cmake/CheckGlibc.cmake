# - Check glibc version
# CHECK_GLIBC_VERSION()
#
# Once done this will define
#
#   GLIBC_VERSION - glibc version
#
macro (CHECK_GLIBC_VERSION)
    execute_process (
        COMMAND ${CMAKE_C_COMPILER} -print-file-name=libc.so.6
        OUTPUT_VARIABLE GLIBC
        OUTPUT_STRIP_TRAILING_WHITESPACE)

    get_filename_component (GLIBC_PATH ${GLIBC} REALPATH)
    get_filename_component (GLIBC_VERSION ${GLIBC_PATH} NAME)
    string (REPLACE "libc-" "" GLIBC_VERSION ${GLIBC_VERSION})
    string (REPLACE ".so" "" GLIBC_VERSION ${GLIBC_VERSION})
    if (NOT GLIBC_VERSION MATCHES "^[0-9.]+$")
        set(C_LIBRARY_NAME "uclibc")
        message (WARNING "Unknown glibc version, assumming it is ${C_LIBRARY_NAME}")
    else()
        set(C_LIBRARY_NAME "glibc")
        message (STATUS "glibc version: ${GLIBC_VERSION}")
    endif (NOT GLIBC_VERSION MATCHES "^[0-9.]+$")
endmacro (CHECK_GLIBC_VERSION)
