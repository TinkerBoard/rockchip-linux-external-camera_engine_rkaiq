set(AYNR_V2_SRC
    rk_aiq_aynr_algo_itf_v2.cpp
    rk_aiq_aynr_algo_ynr_v2.cpp
    rk_aiq_aynr_algo_v2.cpp
    rk_aiq_uapi_aynr_int_v2.cpp
    exp_data.c
    math_err.c
    math_errf.c
    pow.c
    pow_log_data.c
    )

dec_algo_v(aynr 2 rk_aiq_aynr_algo_itf_v2.cpp ${AYNR_V2_SRC})
