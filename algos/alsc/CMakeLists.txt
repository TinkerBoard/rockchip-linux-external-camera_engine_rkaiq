set(ALSC_SRC
    rk_aiq_algo_alsc_itf.cpp
    rk_aiq_alsc_algo.cpp
    rk_aiq_uapi_alsc_int.cpp
    )

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_algo_alsc_itf.cpp")
    add_library(rkaiq_alsc STATIC ${ALSC_SRC})
    set_target_properties(rkaiq_alsc PROPERTIES FOLDER "algos/alsc")
    set_target_properties(rkaiq_alsc PROPERTIES CLEAN_DIRECT_OUTPUT 1)
    set_target_properties(rkaiq_alsc PROPERTIES C_VISIBILITY_PRESET default)
    set_target_properties(rkaiq_alsc PROPERTIES CXX_VISIBILITY_PRESET default)
else()
    message(STATUS "Can NOT found ${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_algo_alsc_itf.cpp. Using lib")
    add_library(rkaiq_alsc STATIC IMPORTED)
    set_target_properties(rkaiq_alsc PROPERTIES IMPORTED_LOCATION
        "${PREFIX}rkaiq_alsc.${SUFFIX}")
    set_target_properties(rkaiq_alsc PROPERTIES IMPORTED_IMPLIB
        "${PREFIX}rkaiq_alsc.${SUFFIX}")
endif()
