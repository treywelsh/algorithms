function err {
	echo -e "\033[1;31mERROR: $@\033[0m" >&2
	exit 1
}

function warn {
	echo -e "\033[1;31mWARNING: $@\033[0m" >&2
}

function usage {
	echo "USAGE : $0 $@" >&2
	exit 1
}

function concat { 
	local res=""
	local sep="$1"

	shift
	res="$1"

	while [ $# -gt 1 ]
	do
		res="$1 $sep $res"
		shift
	done

	echo "$res"
}

export -f err usage warn concat
