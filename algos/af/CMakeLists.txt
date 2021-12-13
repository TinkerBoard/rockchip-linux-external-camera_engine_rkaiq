set(AF_SRC
    rk_aiq_algo_af_itf.cpp
    af.cpp
    af_search.cpp
    af_trigger.cpp
    af_utils.cpp
    rk_aiq_uapi_af_int.cpp
    )

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_algo_af_itf.cpp")
    add_library(rkaiq_af STATIC ${AF_SRC})
    set_target_properties(rkaiq_af PROPERTIES FOLDER "algos/af")
    set_target_properties(rkaiq_af PROPERTIES CLEAN_DIRECT_OUTPUT 1)
    set_target_properties(rkaiq_af PROPERTIES C_VISIBILITY_PRESET default)
    set_target_properties(rkaiq_af PROPERTIES CXX_VISIBILITY_PRESET default)
else()
    message(STATUS "Can NOT found ${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_algo_af_itf.cpp. Using lib")
    add_library(rkaiq_af STATIC IMPORTED)
    set_target_properties(rkaiq_af PROPERTIES IMPORTED_LOCATION
        "${PREFIX}rkaiq_af.${SUFFIX}")
    set_target_properties(rkaiq_af PROPERTIES IMPORTED_IMPLIB
        "${PREFIX}rkaiq_af.${SUFFIX}")
endif()
