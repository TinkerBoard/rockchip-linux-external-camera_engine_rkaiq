cmake_minimum_required(VERSION 2.8...3.22)

project(camera_engine)

set(RK_AIQ_IS_SUBDIR TRUE)

add_subdirectory(rk_aiq)
add_subdirectory(rkisp_demo)
add_subdirectory(IspFec)
add_subdirectory(smart_ir)
add_subdirectory(media_enquiry)
#add_subdirectory(rk_stream)
#add_subdirectory(rkisp_parser_demo)
if(EXISTS rkaiq_3A_sever)
    add_subdirectory(rkaiq_3A_sever)
endif()
