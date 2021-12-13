set(ADPCC_SRC
    rk_aiq_algo_adpcc_itf.cpp
    rk_aiq_adpcc_algo.cpp
    rk_aiq_uapi_adpcc_int.cpp
    )

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_algo_adpcc_itf.cpp")
    add_library(rkaiq_adpcc STATIC ${ADPCC_SRC})
    set_target_properties(rkaiq_adpcc PROPERTIES FOLDER "algos/adpcc")
    set_target_properties(rkaiq_adpcc PROPERTIES CLEAN_DIRECT_OUTPUT 1)
    set_target_properties(rkaiq_adpcc PROPERTIES C_VISIBILITY_PRESET default)
    set_target_properties(rkaiq_adpcc PROPERTIES CXX_VISIBILITY_PRESET default)
else()
    message(STATUS "Can NOT found ${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_algo_adpcc_itf.cpp. Using lib")
    add_library(rkaiq_adpcc STATIC IMPORTED)
    set_target_properties(rkaiq_adpcc PROPERTIES IMPORTED_LOCATION
        "${PREFIX}rkaiq_adpcc.${SUFFIX}")
    set_target_properties(rkaiq_adpcc PROPERTIES IMPORTED_IMPLIB
        "${PREFIX}rkaiq_adpcc.${SUFFIX}")
endif()
