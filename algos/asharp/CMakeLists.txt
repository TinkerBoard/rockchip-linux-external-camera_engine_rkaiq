set(ASHARP_SRC
    rk_aiq_algo_asharp_itf.cpp
    rk_aiq_asharp_algo.cpp
    rk_aiq_asharp_algo_edgefilter.cpp
    rk_aiq_asharp_algo_sharp.cpp
    rk_aiq_uapi_asharp_int.cpp
    )

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_algo_asharp_itf.cpp")
    add_library(rkaiq_asharp STATIC ${ASHARP_SRC})
    set_target_properties(rkaiq_asharp PROPERTIES FOLDER "algos/asharp")
    set_target_properties(rkaiq_asharp PROPERTIES CLEAN_DIRECT_OUTPUT 1)
    set_target_properties(rkaiq_asharp PROPERTIES C_VISIBILITY_PRESET default)
    set_target_properties(rkaiq_asharp PROPERTIES CXX_VISIBILITY_PRESET default)
else()
    message(STATUS "Can NOT found ${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_algo_asharp_itf.cpp. Using lib")
    add_library(rkaiq_asharp STATIC IMPORTED)
    set_target_properties(rkaiq_asharp PROPERTIES IMPORTED_LOCATION
        "${PREFIX}rkaiq_asharp.${SUFFIX}")
    set_target_properties(rkaiq_anr PROPERTIES IMPORTED_IMPLIB
        "${PREFIX}rkaiq_asharp.${SUFFIX}")
endif()
