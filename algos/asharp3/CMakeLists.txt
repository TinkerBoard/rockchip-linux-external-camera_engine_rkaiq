set(ASHARP_V3_SRC
    rk_aiq_asharp_algo_itf_v3.cpp
    rk_aiq_asharp_algo_sharp_v3.cpp
    rk_aiq_asharp_algo_v3.cpp
    rk_aiq_uapi_asharp_int_v3.cpp
    )

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_asharp_algo_itf_v3.cpp")
    add_library(rkaiq_asharp_v3 STATIC ${ASHARP_V3_SRC})
    set_target_properties(rkaiq_asharp_v3 PROPERTIES FOLDER "algos/asharp3")
    set_target_properties(rkaiq_asharp_v3 PROPERTIES CLEAN_DIRECT_OUTPUT 1)
    set_target_properties(rkaiq_asharp_v3 PROPERTIES C_VISIBILITY_PRESET default)
    set_target_properties(rkaiq_asharp_v3 PROPERTIES CXX_VISIBILITY_PRESET default)
else()
    message(STATUS "Can NOT found ${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_asharp_algo_itf_v3.cpp. Using lib")
    add_library(rkaiq_asharp_v3 STATIC IMPORTED)
    set_target_properties(rkaiq_asharp_v3 PROPERTIES IMPORTED_LOCATION
        "${PREFIX}rkaiq_asharp_v3.${SUFFIX}")
    set_target_properties(rkaiq_asharp_v3 PROPERTIES IMPORTED_IMPLIB
        "${PREFIX}rkaiq_asharp_v3.${SUFFIX}")
endif()
