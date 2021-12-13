set(A3DLUT_SRC
    rk_aiq_algo_a3dlut_itf.cpp
    rk_aiq_a3dlut_algo.cpp
    rk_aiq_uapi_a3dlut_int.cpp
    )

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_algo_a3dlut_itf.cpp")
    add_library(rkaiq_a3dlut STATIC ${A3DLUT_SRC})
    set_target_properties(rkaiq_a3dlut PROPERTIES FOLDER "algos/a3dlut")
    set_target_properties(rkaiq_a3dlut PROPERTIES CLEAN_DIRECT_OUTPUT 1)
    set_target_properties(rkaiq_a3dlut PROPERTIES C_VISIBILITY_PRESET default)
    set_target_properties(rkaiq_a3dlut PROPERTIES CXX_VISIBILITY_PRESET default)
else()
    message(STATUS "Can NOT found ${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_algo_a3dlut_itf.cpp. Using lib")
    add_library(rkaiq_a3dlut STATIC IMPORTED)
    set_target_properties(rkaiq_a3dlut PROPERTIES IMPORTED_LOCATION
        "${PREFIX}rkaiq_a3dlut.${SUFFIX}")
    set_target_properties(rkaiq_a3dlut PROPERTIES IMPORTED_IMPLIB
        "${PREFIX}rkaiq_a3dlut.${SUFFIX}")
endif()
