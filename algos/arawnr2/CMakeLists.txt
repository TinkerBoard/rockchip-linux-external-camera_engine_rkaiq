set(ARAWNR_V2_SRC
    rk_aiq_abayernr_algo_itf_v2.cpp
    rk_aiq_abayernr_algo_bayernr_v2.cpp
    rk_aiq_abayernr_algo_v2.cpp
    rk_aiq_uapi_abayernr_int_v2.cpp
    )

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_abayernr_algo_itf_v2.cpp")
    add_library(rkaiq_arawnr_v2 STATIC ${ARAWNR_V2_SRC})
    set_target_properties(rkaiq_arawnr_v2 PROPERTIES FOLDER "algos/arawnr2")
    set_target_properties(rkaiq_arawnr_v2 PROPERTIES CLEAN_DIRECT_OUTPUT 1)
    set_target_properties(rkaiq_arawnr_v2 PROPERTIES C_VISIBILITY_PRESET default)
    set_target_properties(rkaiq_arawnr_v2 PROPERTIES CXX_VISIBILITY_PRESET default)
else()
    message(STATUS "Can NOT found ${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_abayernr_algo_itf_v2.cpp. Using lib")
    add_library(rkaiq_arawnr_v2 STATIC IMPORTED)
    set_target_properties(rkaiq_arawnr_v2 PROPERTIES IMPORTED_LOCATION
        "${PREFIX}rkaiq_arawnr_v2.${SUFFIX}")
    set_target_properties(rkaiq_arawnr_v2 PROPERTIES IMPORTED_IMPLIB
        "${PREFIX}rkaiq_arawnr_v2.${SUFFIX}")
endif()
