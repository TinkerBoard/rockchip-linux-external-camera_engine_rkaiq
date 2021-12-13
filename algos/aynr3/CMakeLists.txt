set(AYNR_V3_SRC
    rk_aiq_aynr_algo_itf_v3.cpp
    rk_aiq_aynr_algo_ynr_v3.cpp
    rk_aiq_aynr_algo_v3.cpp
    rk_aiq_uapi_aynr_int_v3.cpp
    )

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_aynr_algo_itf_v3.cpp")
    add_library(rkaiq_aynr_v3 STATIC ${AYNR_V3_SRC})
    set_target_properties(rkaiq_aynr_v3 PROPERTIES FOLDER "algos/aynr3")
    set_target_properties(rkaiq_aynr_v3 PROPERTIES CLEAN_DIRECT_OUTPUT 1)
    set_target_properties(rkaiq_aynr_v3 PROPERTIES C_VISIBILITY_PRESET default)
    set_target_properties(rkaiq_aynr_v3 PROPERTIES CXX_VISIBILITY_PRESET default)
else()
    message(STATUS "Can NOT found ${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_aynr_algo_itf_v3.cpp. Using lib")
    add_library(rkaiq_aynr_v3 STATIC IMPORTED)
    set_target_properties(rkaiq_aynr_v3 PROPERTIES IMPORTED_LOCATION
        "${PREFIX}rkaiq_aynr_v3.${SUFFIX}")
    set_target_properties(rkaiq_aynr_v3 PROPERTIES IMPORTED_IMPLIB
        "${PREFIX}rkaiq_aynr_v3.${SUFFIX}")
endif()
