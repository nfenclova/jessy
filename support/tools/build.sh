#!/bin/bash

set -e

ODIR="$(pwd)"
SDIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd )"
PDIR="${SDIR}/../../"

mkdir -p "${PDIR}/build"

cd "${PDIR}/build"

cmake .. \
  -DCMAKE_BUILD_TYPE=RelWithDebInfo \
  -DCMAKE_TOOLCHAIN_FILE=../cmake/Toolchains/ClangCrossToolchain.cmake

cmake --build \
  . \
  -- \
  -j$(nproc)

cd "${ODIR}"
