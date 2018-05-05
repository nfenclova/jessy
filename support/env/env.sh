if [[ $JESSY_DEV_ACTIVE == "yes" ]]; then
  echo "[ERR] There is already a Jessy environment active."
else
  export JESSY_DEV_ACTIVE="yes"

  ODIR="$(pwd)"
  SDIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd )"
  PDIR="$(realpath ${SDIR}/../../)"

  alias build='${PDIR}/support/tools/build.sh'
  alias debug='${PDIR}/support/tools/debug.sh'
  alias run='${PDIR}/support/tools/run.sh'

  export ORIGINAL_PS1=$PS1
  export PS1="(jessy-dev) $PS1"


  function jessy_help()
  {
    echo "          Jessy Development Commands            "
    echo "------------------------------------------------"
    echo
    echo "build - build jessy"
    echo "debug - build jessy and start a debugger session"
    echo "run   - build and boot jessy in QEMU"
  }

  function deactivate()
  {
    unalias build debug run
    export PS1=$ORIGINAL_PS1
    unset JESSY_DEV_ACTIVE
    unset -f jessy_help
    unset -f deactivate
  }
fi
