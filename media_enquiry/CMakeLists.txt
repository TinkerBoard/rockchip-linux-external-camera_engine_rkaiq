if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING
        "Choose the type of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel."
        FORCE)
endif()

cmake_minimum_required(VERSION 2.8)

PROJECT(media_enquiry)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(BuildOptions)
include(CompileOptions)
include(GNUInstallDirs)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMakeTargets")

set(ADD_RK_AIQ true)
option(ENABLE_IIO_API "Enable IIO API for EIS algorithm" OFF)

set(RK_AIQ_SOURCE_DIR ${PROJECT_SOURCE_DIR}/../rk_aiq)
message("rkaiq src path" ${RK_AIQ_SOURCE_DIR})

if(ADD_RK_AIQ)
    add_compile_options(-Os)
    add_compile_options(-DADD_RK_AIQ)
    if(NOT ARCH STREQUAL "fpga")
        add_compile_options(-fstack-protector-strong -D_FORTIFY_SOURCE=2)
    else ()
        add_compile_options(-DARCH_FPGA)
    endif()
    set(RK_AIQ_LIB_DIR ${RK_AIQ_SOURCE_DIR}/build/linux/output/${ARCH}/all_lib/${CMAKE_BUILD_TYPE})
    message("rkaiq lib path" ${RK_AIQ_LIB_DIR})
    set(RK_AIQ_INCLUDE_DIR
		#${RK_AIQ_SOURCE_DIR}
        ${RK_AIQ_SOURCE_DIR}/include/
        ${RK_AIQ_SOURCE_DIR}/include/uAPI2
        ${RK_AIQ_SOURCE_DIR}/include/xcore/
        ${RK_AIQ_SOURCE_DIR}/include/algos/
        ${RK_AIQ_SOURCE_DIR}/include/common/
        ${RK_AIQ_SOURCE_DIR}/include/iq_parser/
        ${RK_AIQ_SOURCE_DIR}/include/iq_parser_v2/
        #${FPGA_RGA_INCLUDE_PATH}/include/
        )
    set(RK_AIQ_LIB rkaiq)
endif()

if (ARCH STREQUAL "aarch64")
    set(RK_DRM_LIB_DIR ${PROJECT_SOURCE_DIR}/media_enquiry/libs/arm64/)
elseif (ARCH STREQUAL "arm")
    set(RK_DRM_LIB_DIR
        ${PROJECT_SOURCE_DIR}/media_enquiry/libs/arm32/
        )
endif()

SET(RK_DRM_LIB drm)
if(NOT ARCH STREQUAL "fpga")
    set(RK_RGA_LIB rga)
endif()

if (ENABLE_IIO_API)
    set(IIO_LIB_DIR ${PROJECT_SOURCE_DIR}/media_enquiry/iio/lib)
    set(IIO_LIBS easyiio iio serialport xml2 )
endif()

include_directories(
    media_enquiry
    media_enquiry/mediactl
    ${PROJECT_SOURCE_DIR}/../rk_aiq/aiq_core
    ${PROJECT_SOURCE_DIR}/../rk_aiq/algos
    ${PROJECT_SOURCE_DIR}/../rk_aiq/algos_camgroup
    ${PROJECT_SOURCE_DIR}/../rk_aiq/common
    ${PROJECT_SOURCE_DIR}/../rk_aiq/common/linux
    ${PROJECT_SOURCE_DIR}/../rk_aiq/common/mediactl
    ${PROJECT_SOURCE_DIR}/../rk_aiq/
    ${PROJECT_SOURCE_DIR}/../rk_aiq/hwi/isp20
    ${PROJECT_SOURCE_DIR}/../rk_aiq/ipc
    ${PROJECT_SOURCE_DIR}/../rk_aiq/iq_parser
    ${PROJECT_SOURCE_DIR}/../rk_aiq/iq_parser_v2
    ${PROJECT_SOURCE_DIR}/../rk_aiq/uAPI
    ${PROJECT_SOURCE_DIR}/../rk_aiq/uAPI/include
    ${PROJECT_SOURCE_DIR}/../rk_aiq/uAPI2
    ${PROJECT_SOURCE_DIR}/../rk_aiq/ipc_server
    ${PROJECT_SOURCE_DIR}/../rk_aiq/./
    ${PROJECT_SOURCE_DIR}/../rk_aiq/xcore/
    ${PROJECT_SOURCE_DIR}/../rk_aiq/xcore/base
    ${PROJECT_SOURCE_DIR}/../rk_aiq/include
    ${PROJECT_SOURCE_DIR}/../rk_aiq/include/xcore
    ${PROJECT_SOURCE_DIR}/../rk_aiq/include/xcore/base
    ${PROJECT_SOURCE_DIR}/../rk_aiq/include/iq_parser
    ${PROJECT_SOURCE_DIR}/../rk_aiq/include/iq_parser_v2
    ${PROJECT_SOURCE_DIR}/../rk_aiq/include/uAPI
    ${PROJECT_SOURCE_DIR}/../rk_aiq/include/uAPI2
    ${PROJECT_SOURCE_DIR}/../rk_aiq/include/algos
    ${PROJECT_SOURCE_DIR}/../rk_aiq/include/algos/a3dlut
    ${PROJECT_SOURCE_DIR}/../rk_aiq/include/algos/ablc
    ${PROJECT_SOURCE_DIR}/../rk_aiq/include/algos/accm
    ${PROJECT_SOURCE_DIR}/../rk_aiq/include/algos/acgc
    ${PROJECT_SOURCE_DIR}/../rk_aiq/include/algos/acp
    ${PROJECT_SOURCE_DIR}/../rk_aiq/include/algos/adebayer
    ${PROJECT_SOURCE_DIR}/../rk_aiq/include/algos/adehaze
    ${PROJECT_SOURCE_DIR}/../rk_aiq/include/algos/adpcc
    ${PROJECT_SOURCE_DIR}/../rk_aiq/include/algos/ae
    ${PROJECT_SOURCE_DIR}/../rk_aiq/include/algos/af
    ${PROJECT_SOURCE_DIR}/../rk_aiq/include/algos/afec
    ${PROJECT_SOURCE_DIR}/../rk_aiq/include/algos/agamma
    ${PROJECT_SOURCE_DIR}/../rk_aiq/include/algos/adegamma
    ${PROJECT_SOURCE_DIR}/../rk_aiq/include/algos/agic
    ${PROJECT_SOURCE_DIR}/../rk_aiq/include/algos/amerge
    ${PROJECT_SOURCE_DIR}/../rk_aiq/include/algos/atmo
    ${PROJECT_SOURCE_DIR}/../rk_aiq/include/algos/adrc
    ${PROJECT_SOURCE_DIR}/../rk_aiq/include/algos/aie
    ${PROJECT_SOURCE_DIR}/../rk_aiq/include/algos/aldch
    ${PROJECT_SOURCE_DIR}/../rk_aiq/include/algos/alsc
    ${PROJECT_SOURCE_DIR}/../rk_aiq/include/algos/anr
    ${PROJECT_SOURCE_DIR}/../rk_aiq/include/algos/anr/tnr_md
    ${PROJECT_SOURCE_DIR}/../rk_aiq/include/algos/aorb
	${PROJECT_SOURCE_DIR}/../rk_aiq/include/algos/acsm
    ${PROJECT_SOURCE_DIR}/../rk_aiq/include/algos/asd
    ${PROJECT_SOURCE_DIR}/../rk_aiq/include/algos/asharp
    ${PROJECT_SOURCE_DIR}/../rk_aiq/include/algos/awb
    ${PROJECT_SOURCE_DIR}/../rk_aiq/include/algos/awdr
    ${PROJECT_SOURCE_DIR}/../rk_aiq/include/algos/asharp3
    ${PROJECT_SOURCE_DIR}/../rk_aiq/include/algos/aynr2
    ${PROJECT_SOURCE_DIR}/../rk_aiq/include/algos/acnr
    ${PROJECT_SOURCE_DIR}/../rk_aiq/include/algos/aeis
    ${PROJECT_SOURCE_DIR}/../rk_aiq/include/common
    ${PROJECT_SOURCE_DIR}/../rk_aiq/include/common/mediactl
    ${PROJECT_SOURCE_DIR}/../rk_aiq/include/common/gen_mesh
    ${PROJECT_SOURCE_DIR}/../rk_aiq/include/ipc_server
    ${PROJECT_SOURCE_DIR}/../rk_aiq/include/amd
    ${PROJECT_SOURCE_DIR}/../rk_aiq/include/algos/arawnr
    ${PROJECT_SOURCE_DIR}/../rk_aiq/include/algos/aynr
    ${PROJECT_SOURCE_DIR}/../rk_aiq/include/algos/auvnr
    ${PROJECT_SOURCE_DIR}/../rk_aiq/include/algos/amfnr
    ${PROJECT_SOURCE_DIR}/../rk_aiq/include/algos/again
    ${PROJECT_SOURCE_DIR}/../rk_aiq/include/algos/aynr3
    ${PROJECT_SOURCE_DIR}/../rk_aiq/include/algos/acnr2
    ${PROJECT_SOURCE_DIR}/../rk_aiq/include/algos/asharp4
    ${PROJECT_SOURCE_DIR}/../rk_aiq/include/algos/abayer2dnr2
    ${PROJECT_SOURCE_DIR}/../rk_aiq/include/algos/abayertnr2
    ${PROJECT_SOURCE_DIR}/../rk_aiq/include/algos/again2
    ${PROJECT_SOURCE_DIR}/../rk_aiq/include/algos/acac
    ${PROJECT_SOURCE_DIR}/../rk_aiq/include/algos_camgroup/ae
    ${PROJECT_SOURCE_DIR}/../rk_aiq/include/algos_camgroup/awb
    )

set(DIR_SRCS
    media_enquiry/media_enquiry.cpp
    ${PROJECT_SOURCE_DIR}/../rk_aiq/common/mediactl/mediactl.c
    media_enquiry/mediactl/v4l2subdev.c
    )

set(XCORE_SRC
    ${PROJECT_SOURCE_DIR}/../rk_aiq/xcore/xcam_common.cpp
    ${PROJECT_SOURCE_DIR}/../rk_aiq/xcore/xcam_log.cpp
    ${PROJECT_SOURCE_DIR}/../rk_aiq/xcore/xcam_buffer.cpp
    ${PROJECT_SOURCE_DIR}/../rk_aiq/xcore/video_buffer.cpp
    ${PROJECT_SOURCE_DIR}/../rk_aiq/xcore/v4l2_buffer_proxy.cpp
    ${PROJECT_SOURCE_DIR}/../rk_aiq/xcore/v4l2_device.cpp
    ${PROJECT_SOURCE_DIR}/../rk_aiq/xcore/fake_v4l2_device.cpp
    ${PROJECT_SOURCE_DIR}/../rk_aiq/xcore/buffer_pool.cpp
    ${PROJECT_SOURCE_DIR}/../rk_aiq/xcore/poll_thread.cpp
    ${PROJECT_SOURCE_DIR}/../rk_aiq/xcore/smart_buffer_priv.cpp
    ${PROJECT_SOURCE_DIR}/../rk_aiq/xcore/xcam_thread.cpp
    )



if(WIN32)
    SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/exe)
    SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/all_lib/)
    SET(CMAKE_LIBRARY_PATH ${LIBRARY_OUTPUT_PATH}/${CMAKE_BUILD_TYPE})
else()
    SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/exe/${CMAKE_BUILD_TYPE})
    SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/all_lib/${CMAKE_BUILD_TYPE})
    SET(CMAKE_LIBRARY_PATH ${LIBRARY_OUTPUT_PATH})
endif()

#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi")
#set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")
message(${CMAKE_LIBRARY_PATH})
message(${LIBRARY_OUTPUT_PATH})

add_definitions(-D_CRT_SECURE_NO_WARNINGS)

link_directories("${LIBRARY_OUTPUT_PATH}" "${RK_AIQ_LIB_DIR}" "${RK_DRM_LIB_DIR}" "${IIO_LIB_DIR}")
add_executable(media_enquiry ${DIR_SRCS} ${XCORE_SRC})
target_link_libraries(media_enquiry pthread)
