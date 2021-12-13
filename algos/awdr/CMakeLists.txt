set(AWDR_SRC
    rk_aiq_algo_awdr_itf.cpp
    )

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_algo_awdr_itf.cpp")
    add_library(rkaiq_awdr STATIC ${AWDR_SRC})
    set_target_properties(rkaiq_awdr PROPERTIES FOLDER "algos/awdr")
    set_target_properties(rkaiq_awdr PROPERTIES CLEAN_DIRECT_OUTPUT 1)
    set_target_properties(rkaiq_awdr PROPERTIES C_VISIBILITY_PRESET default)
    set_target_properties(rkaiq_awdr PROPERTIES CXX_VISIBILITY_PRESET default)
else()
    message(STATUS "Can NOT found ${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_algo_awdr_itf.cpp. Using lib")
    add_library(rkaiq_awdr STATIC IMPORTED)
    set_target_properties(rkaiq_awdr PROPERTIES IMPORTED_LOCATION
        "${PREFIX}rkaiq_awdr.${SUFFIX}")
    set_target_properties(rkaiq_awdr PROPERTIES IMPORTED_IMPLIB
        "${PREFIX}rkaiq_awdr.${SUFFIX}")
endif()
