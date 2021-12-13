set (AE_SRC
    rk_aiq_algo_ae_itf.cpp
    rk_aiq_ae_algo.cpp
    rk_aiq_ae_algo_hdrecm.cpp
    rk_aiq_ae_algo_ecm.cpp
    rk_aiq_ae_algo_clm.cpp
    rk_aiq_ae_algo_ldm.cpp
    rk_aiq_ae_algo_pid.cpp
    rk_aiq_uapi_ae_int.cpp
    )

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_algo_ae_itf.cpp")
    add_library(rkaiq_ae STATIC ${AE_SRC})
    set_target_properties(rkaiq_ae PROPERTIES FOLDER "algos/ae")
    set_target_properties(rkaiq_ae PROPERTIES CLEAN_DIRECT_OUTPUT 1)
    set_target_properties(rkaiq_ae PROPERTIES C_VISIBILITY_PRESET default)
    set_target_properties(rkaiq_ae PROPERTIES CXX_VISIBILITY_PRESET default)
else()
    message(STATUS "Can NOT found ${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_algo_ae_itf.cpp. Using lib")
    add_library(rkaiq_ae STATIC IMPORTED)
    set_target_properties(rkaiq_ae PROPERTIES IMPORTED_LOCATION
        "${PREFIX}rkaiq_ae.${SUFFIX}")
    set_target_properties(rkaiq_ae PROPERTIES IMPORTED_IMPLIB
        "${PREFIX}rkaiq_ae.${SUFFIX}")
endif()

