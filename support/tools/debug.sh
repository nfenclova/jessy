#!/bin/bash
set -e

ODIR="$(pwd)"
SDIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd )"
PDIR="${SDIR}/../../"

cd "${PDIR}"

qemu-system-x86_64 -S -s -cdrom build/kernel.iso &
gdb -x support/gdb/default.gdb $1

cd "${ODIR}"
