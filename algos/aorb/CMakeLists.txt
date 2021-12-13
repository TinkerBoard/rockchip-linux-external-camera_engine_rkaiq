set(AORB_SRC
    rk_aiq_algo_aorb_itf.cpp
    orb_algos.cpp
    orb_algos_opencv.cpp
    )

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_algo_aorb_itf.cpp")
    add_library(rkaiq_aorb STATIC ${AORB_SRC})
    set_target_properties(rkaiq_aorb PROPERTIES FOLDER "algos/aorb")
    set_target_properties(rkaiq_aorb PROPERTIES CLEAN_DIRECT_OUTPUT 1)
    set_target_properties(rkaiq_aorb PROPERTIES C_VISIBILITY_PRESET default)
    set_target_properties(rkaiq_aorb PROPERTIES CXX_VISIBILITY_PRESET default)
else()
    message(STATUS "Can NOT found ${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_algo_aorb_itf.cpp. Using lib")
    add_library(rkaiq_aorb STATIC IMPORTED)
    set_target_properties(rkaiq_aorb PROPERTIES IMPORTED_LOCATION
        "${PREFIX}rkaiq_aorb.${SUFFIX}")
    set_target_properties(rkaiq_aorb PROPERTIES IMPORTED_IMPLIB
        "${PREFIX}rkaiq_aorb.${SUFFIX}")
endif()
