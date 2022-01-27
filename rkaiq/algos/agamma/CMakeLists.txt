set(AGAMMA_SRC
    rk_aiq_algo_agamma_itf.cpp
    rk_aiq_uapi_agamma_int.cpp
    )

if (RKAIQ_HAVE_GAMMA_V1)
    list(APPEND AGAMMA_SRC rk_aiq_agamma_algo_v1.cpp)
endif()

if (RKAIQ_HAVE_GAMMA_V2)
    list(APPEND AGAMMA_SRC rk_aiq_agamma_algo_v2.cpp)
endif()

dec_algo(agamma rk_aiq_algo_agamma_itf.cpp ${AGAMMA_SRC})
