set(ACGC_SRC
    rk_aiq_algo_acgc_itf.cpp
    )

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_algo_acgc_itf.cpp")
    add_library(rkaiq_acgc STATIC ${ACGC_SRC})
    set_target_properties(rkaiq_acgc PROPERTIES FOLDER "algos/acgc")
    set_target_properties(rkaiq_acgc PROPERTIES CLEAN_DIRECT_OUTPUT 1)
    set_target_properties(rkaiq_acgc PROPERTIES C_VISIBILITY_PRESET default)
    set_target_properties(rkaiq_acgc PROPERTIES CXX_VISIBILITY_PRESET default)
else()
    message(STATUS "Can NOT found ${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_algo_acgc_itf.cpp. Using lib")
    add_library(rkaiq_acgc STATIC IMPORTED)
    set_target_properties(rkaiq_acgc PROPERTIES IMPORTED_LOCATION
        "${PREFIX}rkaiq_acgc.${SUFFIX}")
    set_target_properties(rkaiq_acgc PROPERTIES IMPORTED_IMPLIB
        "${PREFIX}rkaiq_acgc.${SUFFIX}")
endif()
