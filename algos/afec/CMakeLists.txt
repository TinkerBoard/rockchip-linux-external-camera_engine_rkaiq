set(AFEC_SRC
    rk_aiq_algo_afec_itf.cpp
    rk_aiq_uapi_afec_int.cpp
    )

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_algo_afec_itf.cpp")
    add_library(rkaiq_afec STATIC ${AFEC_SRC})
    set_target_properties(rkaiq_afec PROPERTIES FOLDER "algos/afec")
    set_target_properties(rkaiq_afec PROPERTIES CLEAN_DIRECT_OUTPUT 1)
    set_target_properties(rkaiq_afec PROPERTIES C_VISIBILITY_PRESET default)
    set_target_properties(rkaiq_afec PROPERTIES CXX_VISIBILITY_PRESET default)
else()
    message(STATUS "Can NOT found ${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_algo_afec_itf.cpp. Using lib")
    add_library(rkaiq_afec STATIC IMPORTED)
    set_target_properties(rkaiq_afec PROPERTIES IMPORTED_LOCATION
        "${PREFIX}rkaiq_afec.${SUFFIX}")
    set_target_properties(rkaiq_afec PROPERTIES IMPORTED_IMPLIB
        "${PREFIX}rkaiq_afec.${SUFFIX}")
endif()
