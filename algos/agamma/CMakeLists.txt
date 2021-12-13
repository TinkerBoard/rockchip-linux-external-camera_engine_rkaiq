set(AGAMMA_SRC
    rk_aiq_algo_agamma_itf.cpp
    rk_aiq_agamma_algo.cpp
    rk_aiq_uapi_agamma_int.cpp
    )

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_algo_agamma_itf.cpp")
    add_library(rkaiq_agamma STATIC ${AGAMMA_SRC})
    set_target_properties(rkaiq_agamma PROPERTIES FOLDER "algos/agamma")
    set_target_properties(rkaiq_agamma PROPERTIES CLEAN_DIRECT_OUTPUT 1)
    set_target_properties(rkaiq_agamma PROPERTIES C_VISIBILITY_PRESET default)
    set_target_properties(rkaiq_agamma PROPERTIES CXX_VISIBILITY_PRESET default)
else()
    message(STATUS "Can NOT found ${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_algo_agamma_itf.cpp. Using lib")
    add_library(rkaiq_agamma STATIC IMPORTED)
    set_target_properties(rkaiq_agamma PROPERTIES IMPORTED_LOCATION
        "${PREFIX}rkaiq_agamma.${SUFFIX}")
    set_target_properties(rkaiq_agamma PROPERTIES IMPORTED_IMPLIB
        "${PREFIX}rkaiq_agamma.${SUFFIX}")
endif()
