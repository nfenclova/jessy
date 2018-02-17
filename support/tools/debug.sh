#!/bin/bash
set -e

ODIR="$(pwd)"
SDIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd )"
PDIR="$(realpath ${SDIR}/../../)"
BDIR="${PDIR}/build"

if [[ ! -d "${BDIR}" ]]; then
  "${PDIR}/support/tools/build.sh"
fi

cd ${BDIR}

make boot_debug || true

cd ${ODIR}
