set(AUVNR_V1_SRC
    rk_aiq_auvnr_algo_itf_v1.cpp
    rk_aiq_auvnr_algo_uvnr_v1.cpp
    rk_aiq_auvnr_algo_v1.cpp
    rk_aiq_uapi_auvnr_int_v1.cpp
    )

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_auvnr_algo_itf_v1.cpp")
    add_library(rkaiq_auvnr_v1 STATIC ${AUVNR_V1_SRC})
    set_target_properties(rkaiq_auvnr_v1 PROPERTIES FOLDER "algos/auvnr")
    set_target_properties(rkaiq_auvnr_v1 PROPERTIES CLEAN_DIRECT_OUTPUT 1)
    set_target_properties(rkaiq_auvnr_v1 PROPERTIES C_VISIBILITY_PRESET default)
    set_target_properties(rkaiq_auvnr_v1 PROPERTIES CXX_VISIBILITY_PRESET default)
else()
    message(STATUS "Can NOT found ${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_auvnr_algo_itf_v1.cpp. Using lib")
    add_library(rkaiq_auvnr_v1 STATIC IMPORTED)
    set_target_properties(rkaiq_auvnr_v1 PROPERTIES IMPORTED_LOCATION
        "${PREFIX}rkaiq_auvnr_v1.${SUFFIX}")
    set_target_properties(rkaiq_auvnr_v1 PROPERTIES IMPORTED_IMPLIB
        "${PREFIX}rkaiq_auvnr_v1.${SUFFIX}")
endif()
