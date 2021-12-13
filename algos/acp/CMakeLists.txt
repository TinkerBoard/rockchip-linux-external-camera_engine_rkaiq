set(ACP_SRC
    rk_aiq_algo_acp_itf.cpp
    rk_aiq_uapi_acp_int.cpp
    )

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_algo_acp_itf.cpp")
    add_library(rkaiq_acp STATIC ${ACP_SRC})
    set_target_properties(rkaiq_acp PROPERTIES FOLDER "algos/acp")
    set_target_properties(rkaiq_acp PROPERTIES CLEAN_DIRECT_OUTPUT 1)
    set_target_properties(rkaiq_acp PROPERTIES C_VISIBILITY_PRESET default)
    set_target_properties(rkaiq_acp PROPERTIES CXX_VISIBILITY_PRESET default)
else()
    message(STATUS "Can NOT found ${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_algo_acp_itf.cpp. Using lib")
    add_library(rkaiq_acp STATIC IMPORTED)
    set_target_properties(rkaiq_acp PROPERTIES IMPORTED_LOCATION
        "${PREFIX}rkaiq_acp.${SUFFIX}")
    set_target_properties(rkaiq_acp PROPERTIES IMPORTED_IMPLIB
        "${PREFIX}rkaiq_acp.${SUFFIX}")
endif()

