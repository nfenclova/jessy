#!/bin/bash

set -e

ODIR="$(pwd)"
SDIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd )"
PDIR="${SDIR}/../../"

mkdir -p "${PDIR}"

cd "${SDIR}/build"
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=../cmake/Toolchains/ClangCrossToolchain.cmake
cmake --build . -- -j$(nproc)

cd "${ODIR}"
