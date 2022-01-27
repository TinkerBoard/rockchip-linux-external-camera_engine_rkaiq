# Install script for directory: /work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/algos

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/build/linux/output/arm/installed")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "MinSizeRel")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/build/linux/output/arm/algos/ae/cmake_install.cmake")
  include("/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/build/linux/output/arm/algos/awb/cmake_install.cmake")
  include("/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/build/linux/output/arm/algos/af/cmake_install.cmake")
  include("/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/build/linux/output/arm/algos/aie/cmake_install.cmake")
  include("/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/build/linux/output/arm/algos/amerge/cmake_install.cmake")
  include("/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/build/linux/output/arm/algos/atmo/cmake_install.cmake")
  include("/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/build/linux/output/arm/algos/adrc/cmake_install.cmake")
  include("/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/build/linux/output/arm/algos/asd/cmake_install.cmake")
  include("/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/build/linux/output/arm/algos/acp/cmake_install.cmake")
  include("/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/build/linux/output/arm/algos/adehaze/cmake_install.cmake")
  include("/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/build/linux/output/arm/algos/a3dlut/cmake_install.cmake")
  include("/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/build/linux/output/arm/algos/ablc/cmake_install.cmake")
  include("/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/build/linux/output/arm/algos/accm/cmake_install.cmake")
  include("/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/build/linux/output/arm/algos/acgc/cmake_install.cmake")
  include("/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/build/linux/output/arm/algos/adebayer/cmake_install.cmake")
  include("/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/build/linux/output/arm/algos/adpcc/cmake_install.cmake")
  include("/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/build/linux/output/arm/algos/afec/cmake_install.cmake")
  include("/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/build/linux/output/arm/algos/agamma/cmake_install.cmake")
  include("/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/build/linux/output/arm/algos/adegamma/cmake_install.cmake")
  include("/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/build/linux/output/arm/algos/agic/cmake_install.cmake")
  include("/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/build/linux/output/arm/algos/aldch/cmake_install.cmake")
  include("/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/build/linux/output/arm/algos/alsc/cmake_install.cmake")
  include("/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/build/linux/output/arm/algos/acsm/cmake_install.cmake")
  include("/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/build/linux/output/arm/algos/awdr/cmake_install.cmake")
  include("/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/build/linux/output/arm/algos/again2/cmake_install.cmake")
  include("/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/build/linux/output/arm/algos/aynr3/cmake_install.cmake")
  include("/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/build/linux/output/arm/algos/acnr2/cmake_install.cmake")
  include("/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/build/linux/output/arm/algos/asharp4/cmake_install.cmake")
  include("/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/build/linux/output/arm/algos/abayer2dnr2/cmake_install.cmake")
  include("/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/build/linux/output/arm/algos/abayertnr2/cmake_install.cmake")
  include("/work/linux/rv1109/aiq-src/rk1109_isp_simulator/rk_aiq/build/linux/output/arm/algos/acac/cmake_install.cmake")

endif()

