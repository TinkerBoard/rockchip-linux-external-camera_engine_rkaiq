set(AEIS_SRC
    eis_loader.cpp
    scaler_service.cpp
    remap_backend.cpp
    imu_service.cpp
    eis_algo_service.cpp
    rk_aiq_uapi_aeis_int.cpp
    rk_aiq_algo_aeis_itf.cpp
    )

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_algo_aeis_itf.cpp")
    add_library(rkaiq_aeis STATIC ${AEIS_SRC})
    set_target_properties(rkaiq_aeis PROPERTIES FOLDER "algos/aeis")
    set_target_properties(rkaiq_aeis PROPERTIES CLEAN_DIRECT_OUTPUT 1)
    set_target_properties(rkaiq_aeis PROPERTIES C_VISIBILITY_PRESET default)
    set_target_properties(rkaiq_aeis PROPERTIES CXX_VISIBILITY_PRESET default)
else()
    message(STATUS "Can NOT found ${CMAKE_CURRENT_SOURCE_DIR}/rk_aiq_algo_aeis_itf.cpp. Using lib")
    add_library(rkaiq_aeis STATIC IMPORTED)
    set_target_properties(rkaiq_aeis PROPERTIES IMPORTED_LOCATION
        "${PREFIX}rkaiq_aeis.${SUFFIX}")
    set_target_properties(rkaiq_aeis PROPERTIES IMPORTED_IMPLIB
        "${PREFIX}rkaiq_aeis.${SUFFIX}")
endif()

add_library(dvs_gyro SHARED IMPORTED GLOBAL)
set_target_properties(dvs_gyro PROPERTIES
    IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/lib/libdvs_gyro.so"
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}")
