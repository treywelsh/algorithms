#!/usr/bin/env bash
set -eu

CURRENT="$(readlink -f $(dirname $0))"
TOOLS="$CURRENT"

#Library
[ -f "$TOOLS/lib.bash" ] || { echo "failed to load $TOOLS/lib.bash" ; exit 1 ; }
. "$TOOLS/lib.bash"

if [ $# -lt 5 ]; then
	usage "<max jobs> <ixdpi bin> <ixdpi params and hooks> <results output dir> <pcap_dir> <...> <pcap_dir>"
fi





perf stat -r 50 $BIN > /dev/null
