set(AMERGE_SRC
    rk_aiq_algo_amerge_itf.cpp
    rk_aiq_uapi_amerge_int.cpp
    )

if (RKAIQ_HAVE_MERGE_V1)
    list(APPEND AMERGE_SRC rk_aiq_amerge_algo_v1.cpp)
endif()

if (RKAIQ_HAVE_MERGE_V2)
    list(APPEND AMERGE_SRC rk_aiq_amerge_algo_v2.cpp)
endif()

dec_algo(amerge rk_aiq_algo_amerge_itf.cpp ${AMERGE_SRC})
