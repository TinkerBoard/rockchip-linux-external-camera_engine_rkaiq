set(ATMO_SRC
    rk_aiq_algo_atmo_itf.cpp
    rk_aiq_atmo_algo.cpp
    rk_aiq_uapi_atmo_int.cpp
    )

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_algo_atmo_itf.cpp")
    add_library(rkaiq_atmo STATIC ${ATMO_SRC})
    set_target_properties(rkaiq_atmo PROPERTIES FOLDER "algos/atmo")
    set_target_properties(rkaiq_atmo PROPERTIES CLEAN_DIRECT_OUTPUT 1)
    set_target_properties(rkaiq_atmo PROPERTIES C_VISIBILITY_PRESET default)
    set_target_properties(rkaiq_atmo PROPERTIES CXX_VISIBILITY_PRESET default)
else()
    message(STATUS "Can NOT found ${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_algo_atmo_itf.cpp. Using lib")
    add_library(rkaiq_atmo STATIC IMPORTED)
    set_target_properties(rkaiq_atmo PROPERTIES IMPORTED_LOCATION
        "${PREFIX}rkaiq_atmo.${SUFFIX}")
    set_target_properties(rkaiq_atmo PROPERTIES IMPORTED_IMPLIB
        "${PREFIX}rkaiq_atmo.${SUFFIX}")
endif()
