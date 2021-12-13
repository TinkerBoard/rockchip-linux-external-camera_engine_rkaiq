set(AWB_SRC
    color_space_convert.cpp
    fixfloat.cpp
    rk_aiq_algo_awb_itf.cpp
    rk_aiq_awb_algo_caga.cpp
    rk_aiq_awb_algo_com1.cpp
    rk_aiq_awb_algo_com2.cpp
    rk_aiq_awb_algo_sgc.cpp
    rk_aiq_awb_algo_v200.cpp
    rk_aiq_awb_algo_v200.h
    rk_aiq_awb_algo_v201.cpp
    rk_aiq_algo_awb_itf.cpp
    rk_aiq_uapi_awb_int.cpp
    rk_aiq_uapiv2_awb_int.cpp
    )

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_algo_awb_itf.cpp")
    add_library(rkaiq_awb STATIC ${AWB_SRC})
    set_target_properties(rkaiq_awb PROPERTIES FOLDER "algos/awb")
    set_target_properties(rkaiq_awb PROPERTIES CLEAN_DIRECT_OUTPUT 1)
    set_target_properties(rkaiq_awb PROPERTIES C_VISIBILITY_PRESET default)
    set_target_properties(rkaiq_awb PROPERTIES CXX_VISIBILITY_PRESET default)
else()
    message(STATUS "Can NOT found ${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_algo_awb_itf.cpp. Using lib")
    add_library(rkaiq_awb STATIC IMPORTED)
    set_target_properties(rkaiq_awb PROPERTIES IMPORTED_LOCATION
        "${PREFIX}rkaiq_awb.${SUFFIX}")
    set_target_properties(rkaiq_awb PROPERTIES IMPORTED_IMPLIB
        "${PREFIX}rkaiq_awb.${SUFFIX}")
endif()

