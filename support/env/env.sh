ODIR="$(pwd)"
SDIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd )"
PDIR="$(realpath ${SDIR}/../../)"

alias build='${PDIR}/support/tools/build.sh'
alias debug='${PDIR}/support/tools/debug.sh'
alias run='${PDIR}/support/tools/run.sh'
