set(AGIC_SRC
    rk_aiq_algo_agic_itf.cpp
    rk_aiq_algo_agic.cpp
    rk_aiq_uapi_agic_int.cpp
    )

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_algo_agic_itf.cpp")
    add_library(rkaiq_agic STATIC ${AGIC_SRC})
    set_target_properties(rkaiq_agic PROPERTIES FOLDER "algos/agic")
    set_target_properties(rkaiq_agic PROPERTIES CLEAN_DIRECT_OUTPUT 1)
    set_target_properties(rkaiq_agic PROPERTIES C_VISIBILITY_PRESET default)
    set_target_properties(rkaiq_agic PROPERTIES CXX_VISIBILITY_PRESET default)
else()
    message(STATUS "Can NOT found ${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_algo_agic_itf.cpp. Using lib")
    add_library(rkaiq_agic STATIC IMPORTED)
    set_target_properties(rkaiq_agic PROPERTIES IMPORTED_LOCATION
        "${PREFIX}rkaiq_agic.${SUFFIX}")
    set_target_properties(rkaiq_agic PROPERTIES IMPORTED_IMPLIB
        "${PREFIX}rkaiq_agic.${SUFFIX}")
endif()

