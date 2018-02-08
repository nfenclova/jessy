#!/bin/bash
set -e

ODIR="$(pwd)"
SDIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd )"
PDIR="${SDIR}/../../"

cd "${PDIR}"

qemu-system-x86_64 -cdrom build/kernel.iso 2>/dev/null

cd "${ODIR}"
