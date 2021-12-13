set(AGAIN_V1_SRC
    rk_aiq_again_algo_itf.cpp
    rk_aiq_again_algo_gain.cpp
    rk_aiq_again_algo.cpp
    rk_aiq_uapi_again_int.cpp
    )

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_again_algo_itf.cpp")
    add_library(rkaiq_again_v1 STATIC ${AGAIN_V1_SRC})
    set_target_properties(rkaiq_again_v1 PROPERTIES FOLDER "algos/again")
    set_target_properties(rkaiq_again_v1 PROPERTIES CLEAN_DIRECT_OUTPUT 1)
    set_target_properties(rkaiq_again_v1 PROPERTIES C_VISIBILITY_PRESET default)
    set_target_properties(rkaiq_again_v1 PROPERTIES CXX_VISIBILITY_PRESET default)
else()
    message(STATUS "Can NOT found ${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_again_algo_itf.cpp. Using lib")
    add_library(rkaiq_again_v1 STATIC IMPORTED)
    set_target_properties(rkaiq_again_v1 PROPERTIES IMPORTED_LOCATION
        "${PREFIX}rkaiq_again_v1.${SUFFIX}")
    set_target_properties(rkaiq_again_v1 PROPERTIES IMPORTED_IMPLIB
        "${PREFIX}rkaiq_again_v1.${SUFFIX}")
endif()
