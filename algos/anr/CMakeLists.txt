set(ANR_SRC
    rk_aiq_algo_anr_itf.cpp
    rk_aiq_anr_algo.cpp
    rk_aiq_anr_algo_bayernr.cpp
    rk_aiq_anr_algo_mfnr.cpp
    rk_aiq_anr_algo_uvnr.cpp
    rk_aiq_anr_algo_ynr.cpp
    rk_aiq_uapi_anr_int.cpp
    rk_aiq_anr_algo_gain.cpp
    )

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_algo_anr_itf.cpp")
    add_library(rkaiq_anr STATIC ${ANR_SRC})
    set_target_properties(rkaiq_anr PROPERTIES FOLDER "algos/anr")
    set_target_properties(rkaiq_anr PROPERTIES CLEAN_DIRECT_OUTPUT 1)
    set_target_properties(rkaiq_anr PROPERTIES C_VISIBILITY_PRESET default)
    set_target_properties(rkaiq_anr PROPERTIES CXX_VISIBILITY_PRESET default)
else()
    message(STATUS "Can NOT found ${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_algo_anr_itf.cpp. Using lib")
    add_library(rkaiq_anr STATIC IMPORTED)
    set_target_properties(rkaiq_anr PROPERTIES IMPORTED_LOCATION
        "${PREFIX}rkaiq_anr.${SUFFIX}")
    set_target_properties(rkaiq_anr PROPERTIES IMPORTED_IMPLIB
        "${PREFIX}rkaiq_anr.${SUFFIX}")
endif()
