set(ADHAZ_SRC
    rk_aiq_algo_adhaz_itf.cpp
    rk_aiq_uapi_adehaze_int.cpp
    )

if (RKAIQ_HAVE_DEHAZE_V1)
    list(APPEND ADHAZ_SRC rk_aiq_adehaze_algo_v1.cpp)
endif()

if (RKAIQ_HAVE_DEHAZE_V2)
    list(APPEND ADHAZ_SRC rk_aiq_adehaze_algo_v2.cpp)
endif()

if (RKAIQ_HAVE_DEHAZE_V3)
    list(APPEND ADHAZ_SRC rk_aiq_adehaze_algo_v3.cpp)
endif()

dec_algo(adehaze rk_aiq_algo_adhaz_itf.cpp ${ADHAZ_SRC})
