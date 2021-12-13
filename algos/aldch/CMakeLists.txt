set(ALDCH_SRC
    rk_aiq_algo_aldch_itf.cpp
    rk_aiq_uapi_aldch_int.cpp
    )

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_algo_aldch_itf.cpp")
    add_library(rkaiq_aldch STATIC ${ALDCH_SRC})
    set_target_properties(rkaiq_aldch PROPERTIES FOLDER "algos/aldch")
    set_target_properties(rkaiq_aldch PROPERTIES CLEAN_DIRECT_OUTPUT 1)
    set_target_properties(rkaiq_aldch PROPERTIES C_VISIBILITY_PRESET default)
    set_target_properties(rkaiq_aldch PROPERTIES CXX_VISIBILITY_PRESET default)
else()
    message(STATUS "Can NOT found ${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_algo_aldch_itf.cpp. Using lib")
    add_library(rkaiq_aldch STATIC IMPORTED)
    set_target_properties(rkaiq_aldch PROPERTIES IMPORTED_LOCATION
        "${PREFIX}rkaiq_aldch.${SUFFIX}")
    set_target_properties(rkaiq_aldch PROPERTIES IMPORTED_IMPLIB
        "${PREFIX}rkaiq_aldch.${SUFFIX}")
endif()
