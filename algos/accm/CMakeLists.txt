set(ACCM_SRC
    rk_aiq_algo_accm_itf.cpp
    rk_aiq_accm_algo.cpp
    rk_aiq_uapi_accm_int.cpp
    )

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_algo_accm_itf.cpp")
    add_library(rkaiq_accm STATIC ${ACCM_SRC})
    set_target_properties(rkaiq_accm PROPERTIES FOLDER "algos/accm")
    set_target_properties(rkaiq_accm PROPERTIES CLEAN_DIRECT_OUTPUT 1)
    set_target_properties(rkaiq_accm PROPERTIES C_VISIBILITY_PRESET default)
    set_target_properties(rkaiq_accm PROPERTIES CXX_VISIBILITY_PRESET default)
else()
    message(STATUS "Can NOT found ${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_algo_accm_itf.cpp. Using lib")
    add_library(rkaiq_accm STATIC IMPORTED)
    set_target_properties(rkaiq_accm PROPERTIES IMPORTED_LOCATION
        "${PREFIX}rkaiq_accm.${SUFFIX}")
    set_target_properties(rkaiq_accm PROPERTIES IMPORTED_IMPLIB
        "${PREFIX}rkaiq_accm.${SUFFIX}")
endif()
