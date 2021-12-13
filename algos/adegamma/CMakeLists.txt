set(ADEGAMMA_SRC
    rk_aiq_algo_adegamma_itf.cpp
    rk_aiq_adegamma_algo.cpp
    rk_aiq_uapi_adegamma_int.cpp
    )

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_algo_adegamma_itf.cpp")
    add_library(rkaiq_adegamma STATIC ${ADEGAMMA_SRC})
    set_target_properties(rkaiq_adegamma PROPERTIES FOLDER "algos/adegamma")
    set_target_properties(rkaiq_adegamma PROPERTIES CLEAN_DIRECT_OUTPUT 1)
    set_target_properties(rkaiq_adegamma PROPERTIES C_VISIBILITY_PRESET default)
    set_target_properties(rkaiq_adegamma PROPERTIES CXX_VISIBILITY_PRESET default)
else()
    message(STATUS "Can NOT found ${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_algo_adegamma_itf.cpp. Using lib")
    add_library(rkaiq_adegamma STATIC IMPORTED)
    set_target_properties(rkaiq_adegamma PROPERTIES IMPORTED_LOCATION
        "${PREFIX}rkaiq_adegamma.${SUFFIX}")
    set_target_properties(rkaiq_adegamma PROPERTIES IMPORTED_IMPLIB
        "${PREFIX}rkaiq_adegamma.${SUFFIX}")
endif()
