set(ASD_SRC
    rk_aiq_algo_asd_itf.cpp
    scene_detector.cpp
    rk_aiq_uapi_asd_int.cpp
    )

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_algo_asd_itf.cpp")
    add_library(rkaiq_asd STATIC ${ASD_SRC})
    set_target_properties(rkaiq_asd PROPERTIES FOLDER "algos/asd")
    set_target_properties(rkaiq_asd PROPERTIES CLEAN_DIRECT_OUTPUT 1)
    set_target_properties(rkaiq_asd PROPERTIES C_VISIBILITY_PRESET default)
    set_target_properties(rkaiq_asd PROPERTIES CXX_VISIBILITY_PRESET default)
else()
    message(STATUS "Can NOT found ${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_algo_asd_itf.cpp. Using lib")
    add_library(rkaiq_asd STATIC IMPORTED)
    set_target_properties(rkaiq_asd PROPERTIES IMPORTED_LOCATION
        "${PREFIX}rkaiq_asd.${SUFFIX}")
    set_target_properties(rkaiq_asd PROPERTIES IMPORTED_IMPLIB
        "${PREFIX}rkaiq_asd.${SUFFIX}")
endif()
