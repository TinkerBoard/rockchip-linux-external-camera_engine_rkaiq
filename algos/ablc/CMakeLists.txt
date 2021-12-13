set(ABLC_SRC
    rk_aiq_algo_ablc_itf.cpp
    rk_aiq_ablc_algo.cpp
    rk_aiq_uapi_ablc_int.cpp
    )

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_algo_ablc_itf.cpp")
    add_library(rkaiq_ablc STATIC ${ABLC_SRC})
    set_target_properties(rkaiq_ablc PROPERTIES FOLDER "algos/ablc")
    set_target_properties(rkaiq_ablc PROPERTIES CLEAN_DIRECT_OUTPUT 1)
    set_target_properties(rkaiq_ablc PROPERTIES C_VISIBILITY_PRESET default)
    set_target_properties(rkaiq_ablc PROPERTIES CXX_VISIBILITY_PRESET default)
else()
    message(STATUS "Can NOT found ${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_algo_ablc_itf.cpp. Using lib")
    add_library(rkaiq_ablc STATIC IMPORTED)
    set_target_properties(rkaiq_ablc PROPERTIES IMPORTED_LOCATION
        "${PREFIX}rkaiq_ablc.${SUFFIX}")
    set_target_properties(rkaiq_ablc PROPERTIES IMPORTED_IMPLIB
        "${PREFIX}rkaiq_ablc.${SUFFIX}")
endif()
