set(AIE_SRC
    rk_aiq_algo_aie_itf.cpp
    rk_aiq_algo_aie_int.cpp
    )

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_algo_aie_itf.cpp")
    add_library(rkaiq_aie STATIC ${AIE_SRC})
    set_target_properties(rkaiq_aie PROPERTIES FOLDER "algos/aie")
    set_target_properties(rkaiq_aie PROPERTIES CLEAN_DIRECT_OUTPUT 1)
    set_target_properties(rkaiq_aie PROPERTIES C_VISIBILITY_PRESET default)
    set_target_properties(rkaiq_aie PROPERTIES CXX_VISIBILITY_PRESET default)
else()
    message(STATUS "Can NOT found ${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_algo_aie_itf.cpp. Using lib")
    add_library(rkaiq_aie STATIC IMPORTED)
    set_target_properties(rkaiq_aie PROPERTIES IMPORTED_LOCATION
        "${PREFIX}rkaiq_aie.${SUFFIX}")
    set_target_properties(rkaiq_aie PROPERTIES IMPORTED_IMPLIB
        "${PREFIX}rkaiq_aie.${SUFFIX}")
endif()


