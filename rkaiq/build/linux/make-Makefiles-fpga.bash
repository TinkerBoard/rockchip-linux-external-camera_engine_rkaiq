#!/bin/bash
# Run this from within a bash shell
# x86_64 is for simulation do not enable RK platform
export AIQ_BUILD_HOST_DIR=/home/hkj/isp2-fpga/buildroot_xhf/buildroot/output/host
TOOLCHAIN_FILE=$(pwd)/../../cmake/toolchains/arm_fpga_linux_buildroot.cmake
OUTPUT=$(pwd)/output/fpga
SOURCE_PATH=$OUTPUT/../../../../

mkdir -p $OUTPUT
pushd $OUTPUT

cmake -G "Ninja" \
    -DCMAKE_BUILD_TYPE=debug \
    -DARCH="fpga" \
    -DRKPLATFORM=OFF \
    -DCMAKE_TOOLCHAIN_FILE=$TOOLCHAIN_FILE \
    -DCMAKE_SKIP_RPATH=TRUE \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=YES \
	-DISP_HW_VERSION=${ISP_HW_VERSION} \
    $SOURCE_PATH \
&& ninja -j$(nproc)

popd
