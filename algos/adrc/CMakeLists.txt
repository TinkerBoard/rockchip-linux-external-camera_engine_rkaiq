set(ADRC_SRC
    rk_aiq_algo_adrc_itf.cpp
    rk_aiq_adrc_algo.cpp
    rk_aiq_uapi_adrc_int.cpp
    )

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_algo_adrc_itf.cpp")
    add_library(rkaiq_adrc STATIC ${ADRC_SRC})
    set_target_properties(rkaiq_adrc PROPERTIES FOLDER "algos/adrc")
    set_target_properties(rkaiq_adrc PROPERTIES CLEAN_DIRECT_OUTPUT 1)
    set_target_properties(rkaiq_adrc PROPERTIES C_VISIBILITY_PRESET default)
    set_target_properties(rkaiq_adrc PROPERTIES CXX_VISIBILITY_PRESET default)
else()
    message(STATUS "Can NOT found
    ${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_algo_adrc_itf.cpp. Using lib")
    add_library(rkaiq_adrc STATIC IMPORTED)
    set_target_properties(rkaiq_adrc PROPERTIES IMPORTED_LOCATION
        "${PREFIX}rkaiq_adrc.${SUFFIX}")
    set_target_properties(rkaiq_adrc PROPERTIES IMPORTED_IMPLIB
        "${PREFIX}rkaiq_adrc.${SUFFIX}")
endif()
