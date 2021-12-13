set(AMERGE_SRC
    rk_aiq_algo_amerge_itf.cpp
    rk_aiq_amerge_algo.cpp
    rk_aiq_uapi_amerge_int.cpp
    )

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_algo_amerge_itf.cpp")
    add_library(rkaiq_amerge STATIC ${AMERGE_SRC})
    set_target_properties(rkaiq_amerge PROPERTIES FOLDER "algos/amerge")
    set_target_properties(rkaiq_amerge PROPERTIES CLEAN_DIRECT_OUTPUT 1)
    set_target_properties(rkaiq_amerge PROPERTIES C_VISIBILITY_PRESET default)
    set_target_properties(rkaiq_amerge PROPERTIES CXX_VISIBILITY_PRESET default)
else()
    message(STATUS "Can NOT found ${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_algo_amerge_itf.cpp. Using lib")
    add_library(rkaiq_amerge STATIC IMPORTED)
    set_target_properties(rkaiq_amerge PROPERTIES IMPORTED_LOCATION
        "${PREFIX}rkaiq_amerge.${SUFFIX}")
    set_target_properties(rkaiq_amerge PROPERTIES IMPORTED_IMPLIB
        "${PREFIX}rkaiq_amerge.${SUFFIX}")
endif()
