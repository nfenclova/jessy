#!/bin/bash
set -e

ODIR="$(pwd)"
SDIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd )"
PDIR="${SDIR}/../../"

cd "${PDIR}"

gdb -x support/gdb/default.gdb $1

cd "${ODIR}"
