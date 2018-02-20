#!/bin/bash

set -e

ODIR="$(pwd)"
SDIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd )"
PDIR="$(realpath ${SDIR}/../../)"

BDIR="${PDIR}/build"

function usage()
{
  echo "Usage: build.sh [-f]" 1>&2
  echo
  echo "  -f  Force recreation of build environment"
  exit 0
}

function create_bdir()
{
  if [[ -d "${BDIR}" ]] && [[ "${force}" != "true" ]]; then
    echo "Using existing build directory ${BDIR}. Specify '-f' to force recreation." 1>&2
  else
    rm -rf "${BDIR}"
    mkdir -p "${BDIR}"

    cd "${BDIR}"

    cmake .. \
      -DCMAKE_BUILD_TYPE=RelWithDebInfo \
      -DCMAKE_TOOLCHAIN_FILE=../cmake/Toolchains/GNUCrossToolchain.cmake
  fi
}

function build()
{
  cd "${BDIR}"
  cmake --build \
    . \
    -- \
    -j$(nproc)

  cd "${ODIR}"
}

while getopts "fh" o; do
  case "${o}" in
    f)
      force=true
      ;;
    h)
      usage
      exit 0
      ;;
    *)
      usage
      exit 1
      ;;
  esac
done

create_bdir
build
