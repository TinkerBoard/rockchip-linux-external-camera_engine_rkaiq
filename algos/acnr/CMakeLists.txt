set(ACNR_V1_SRC
    rk_aiq_acnr_algo_itf_v1.cpp
    rk_aiq_acnr_algo_cnr_v1.cpp
    rk_aiq_acnr_algo_v1.cpp
    rk_aiq_uapi_acnr_int_v1.cpp
    )

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_acnr_algo_itf_v1.cpp")
    add_library(rkaiq_acnr_v1 STATIC ${ACNR_V1_SRC})
    set_target_properties(rkaiq_acnr_v1 PROPERTIES FOLDER "algos/acnr")
    set_target_properties(rkaiq_acnr_v1 PROPERTIES CLEAN_DIRECT_OUTPUT 1)
    set_target_properties(rkaiq_acnr_v1 PROPERTIES C_VISIBILITY_PRESET default)
    set_target_properties(rkaiq_acnr_v1 PROPERTIES CXX_VISIBILITY_PRESET default)
else()
    message(STATUS "Can NOT found ${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_acnr_algo_itf_v1.cpp. Using lib")
    add_library(rkaiq_acnr_v1 STATIC IMPORTED)
    set_target_properties(rkaiq_acnr_v1 PROPERTIES IMPORTED_LOCATION
        "${PREFIX}rkaiq_acnr_v1.${SUFFIX}")
    set_target_properties(rkaiq_acnr_v1 PROPERTIES IMPORTED_IMPLIB
        "${PREFIX}rkaiq_acnr_v1.${SUFFIX}")
endif()
