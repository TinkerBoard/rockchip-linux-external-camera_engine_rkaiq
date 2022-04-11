set(ASHARP_V33_SRC
    rk_aiq_asharp_algo_itf_v33.cpp
    rk_aiq_asharp_algo_sharp_v33.cpp
    rk_aiq_asharp_algo_v33.cpp
    rk_aiq_uapi_asharp_int_v33.cpp
    exp_data.c
    math_err.c
    math_errf.c
    pow.c
    pow_log_data.c
    )

dec_algo_v(asharp 33 rk_aiq_asharp_algo_itf_v33.cpp ${ASHARP_V33_SRC})
