set(AR2Y_SRC
    rk_aiq_algo_ar2y_itf.cpp
    )

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_algo_ar2y_itf.cpp")
    add_library(rkaiq_ar2y STATIC ${AR2Y_SRC})
    set_target_properties(rkaiq_ar2y PROPERTIES FOLDER "algos/ar2y")
    set_target_properties(rkaiq_ar2y PROPERTIES CLEAN_DIRECT_OUTPUT 1)
    set_target_properties(rkaiq_ar2y PROPERTIES C_VISIBILITY_PRESET default)
    set_target_properties(rkaiq_ar2y PROPERTIES CXX_VISIBILITY_PRESET default)
else()
    message(STATUS "Can NOT found ${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_algo_ar2y_itf.cpp. Using lib")
    add_library(rkaiq_ar2y STATIC IMPORTED)
    set_target_properties(rkaiq_ar2y PROPERTIES IMPORTED_LOCATION
        "${PREFIX}rkaiq_ar2y.${SUFFIX}")
    set_target_properties(rkaiq_ar2y PROPERTIES IMPORTED_IMPLIB
        "${PREFIX}rkaiq_ar2y.${SUFFIX}")
endif()
