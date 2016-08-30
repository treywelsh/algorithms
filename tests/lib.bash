#TODO test if output is a terminal : ([ -t 1 ] && echo "terminal") > /dev/null
function err {
	echo -e "\033[1;31mERROR: $@\033[0m" >&2
	exit 1
}

function warn {
	echo -e "\033[1;31mWARNING: $@\033[0m" >&2
}

function usage {
	echo "$0 $@" >&2
	exit 1
}

function assert_exist {
	local test_opt=$1
	local dir="$2"
	local tested=""

	case "$test_opt" in 
		"-d") tested="directory";;
		"-f") tested="file";;
	esac

	[ $test_opt "$dir" ] || err "$@: <<$dir>> is not a $tested."
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

export -f err usage warn assert_exist concat
