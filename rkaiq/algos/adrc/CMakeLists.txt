set(ADRC_SRC
    rk_aiq_algo_adrc_itf.cpp
    rk_aiq_uapi_adrc_int.cpp
    )

if (RKAIQ_HAVE_DRC_V1)
    list(APPEND ADRC_SRC rk_aiq_adrc_algo_v1.cpp)
endif()

if (RKAIQ_HAVE_DRC_V2)
    list(APPEND ADRC_SRC rk_aiq_adrc_algo_v2.cpp)
endif()

dec_algo(adrc rk_aiq_algo_adrc_itf.cpp ${ADRC_SRC})
