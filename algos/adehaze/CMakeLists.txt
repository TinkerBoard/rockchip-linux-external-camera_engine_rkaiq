set(ADHAZ_SRC
    rk_aiq_algo_adhaz_itf.cpp
    rk_aiq_adehaze_algo.cpp
    rk_aiq_uapi_adehaze_int.cpp
    )

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_algo_adhaz_itf.cpp")
    add_library(rkaiq_adhaz STATIC ${ADHAZ_SRC})
    set_target_properties(rkaiq_adhaz PROPERTIES FOLDER "algos/adehaze")
    set_target_properties(rkaiq_adhaz PROPERTIES CLEAN_DIRECT_OUTPUT 1)
    set_target_properties(rkaiq_adhaz PROPERTIES C_VISIBILITY_PRESET default)
    set_target_properties(rkaiq_adhaz PROPERTIES CXX_VISIBILITY_PRESET default)
else()
    message(STATUS "Can NOT found ${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_algo_adhaz_itf.cpp. Using lib")
    add_library(rkaiq_adhaz STATIC IMPORTED)
    set_target_properties(rkaiq_adhaz PROPERTIES IMPORTED_LOCATION
        "${PREFIX}rkaiq_adhaz.${SUFFIX}")
    set_target_properties(rkaiq_adhaz PROPERTIES IMPORTED_IMPLIB
        "${PREFIX}rkaiq_adhaz.${SUFFIX}")
endif()
