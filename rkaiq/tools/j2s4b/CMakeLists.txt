cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
set(CMAKE_C_FLAGS -m32)
set(CMAKE_CXX_FLAGS -m32)
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_compile_options(-fPIC -Wall -Wno-error -O0 -g)
add_compile_options(-Wno-unused-variable
    -Wno-unused-but-set-variable
    -Wno-unused-function
    -Wno-misleading-indentation
    -Wno-unused-label
    -Wno-format-truncation
    -fno-strict-aliasing)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(GitVersion)

PROJECT(j2s4b)

set(ROOT_PROJ_DIR ${PROJECT_SOURCE_DIR}/../..)

include_directories(
    src
    src/j2s4b
    include
    ${ROOT_PROJ_DIR}/include/iq_parser_v2/j2s/
    ${ROOT_PROJ_DIR}/build/linux/output/arm
    )

set(CXX_SRCS
    ${ROOT_PROJ_DIR}/iq_parser_v2/j2s/cJSON.cpp
    ${ROOT_PROJ_DIR}/iq_parser_v2/j2s/cJSON_Utils.cpp
    src/j2s4b/j2s.cpp
    src/j2s4b/j2s4b_utils.cpp
    src/main.cpp)

ADD_EXECUTABLE(j2s4b ${CXX_SRCS})
add_version_info(TARGET j2s4b)

install(TARGETS j2s4b DESTINATION oem)
