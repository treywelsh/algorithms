#!/usr/bin/env bash
set -eu

current="$(readlink -f $(dirname $0))"
tools="$(dirname $current)"

#library
[ -f "$tools/lib.bash" ] || { echo "failed to load $tools/lib.bash" ; exit 1 ; }
. "$tools/lib.bash"

if [ $# -lt 1 ]; then
	usage "<binary>"
fi

bin="$1"

#TODO       add util-linux (rpi2 package) or schedutils.
#           This enable taskset command.

#TODO FIX   perf metacommand call the right version of perf_*.*
#           associated with the current kernel (uname -r)

function perf_cmd {
   local repeat="$1"
   local bin="$2"

   #this does not work on my current rpi2 config
   perf stat -r $repeat "$bin" > /dev/null

   #this work on my current rpi2 config, last perf version used :
   #perf_3.2 stat -r 50 "$bin" > /dev/null
}
export -f perf_cmd

#Allow running on a specific core.
#Use isolcpu kernel option inorder to have a dedicated core for
#performance test :
function perf_affinity_cmd {
   local core=0
   taskset -c $core bash -c perf_cmd 50 "$bin"
}

perf_affinity_cmd
