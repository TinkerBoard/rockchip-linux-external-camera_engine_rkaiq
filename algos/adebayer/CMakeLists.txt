set(ADEBAYER_SRC
    rk_aiq_algo_adebayer_itf.cpp
    rk_aiq_algo_adebayer.cpp
    rk_aiq_uapi_adebayer_int.cpp
    )

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_algo_adebayer_itf.cpp")
    add_library(rkaiq_adebayer STATIC ${ADEBAYER_SRC})
    set_target_properties(rkaiq_adebayer PROPERTIES FOLDER "algos/adebayer")
    set_target_properties(rkaiq_adebayer PROPERTIES CLEAN_DIRECT_OUTPUT 1)
    set_target_properties(rkaiq_adebayer PROPERTIES C_VISIBILITY_PRESET default)
    set_target_properties(rkaiq_adebayer PROPERTIES CXX_VISIBILITY_PRESET default)
else()
    message(STATUS "Can NOT found ${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_algo_adebayer_itf.cpp. Using lib")
    add_library(rkaiq_adebayer STATIC IMPORTED)
    set_target_properties(rkaiq_adebayer PROPERTIES IMPORTED_LOCATION
        "${PREFIX}rkaiq_adebayer.${SUFFIX}")
    set_target_properties(rkaiq_adebayer PROPERTIES IMPORTED_IMPLIB
        "${PREFIX}rkaiq_adebayer.${SUFFIX}")
endif()

