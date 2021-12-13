set(ASHARP_V4_SRC
    rk_aiq_asharp_algo_itf_v4.cpp
    rk_aiq_asharp_algo_sharp_v4.cpp
    rk_aiq_asharp_algo_v4.cpp
    rk_aiq_uapi_asharp_int_v4.cpp
    )

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_asharp_algo_itf_v4.cpp")
    add_library(rkaiq_asharp_v4 STATIC ${ASHARP_V4_SRC})
    set_target_properties(rkaiq_asharp_v4 PROPERTIES FOLDER "algos/asharp4")
    set_target_properties(rkaiq_asharp_v4 PROPERTIES CLEAN_DIRECT_OUTPUT 1)
    set_target_properties(rkaiq_asharp_v4 PROPERTIES C_VISIBILITY_PRESET default)
    set_target_properties(rkaiq_asharp_v4 PROPERTIES CXX_VISIBILITY_PRESET default)
else()
    message(STATUS "Can NOT found ${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_asharp_algo_itf_v4.cpp. Using lib")
    add_library(rkaiq_asharp_v4 STATIC IMPORTED)
    set_target_properties(rkaiq_asharp_v4 PROPERTIES IMPORTED_LOCATION
        "${PREFIX}rkaiq_asharp_v4.${SUFFIX}")
    set_target_properties(rkaiq_asharp_v4 PROPERTIES IMPORTED_IMPLIB
        "${PREFIX}rkaiq_asharp_v4.${SUFFIX}")
endif()
