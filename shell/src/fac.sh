#! /bin/bash
set -e

lib_path="$(dirname $(readlink -f $0))/lib"
. "$lib_path/stdout.sh"

n="$1"
if [ -z $n ]
then
  error "[arguments error]: missing the integer as the first parameter."
  exit 1
fi

if [ $n -lt 0 ]
then
  error "[arguments error]: Negative numbers without factorial."
  exit 1
fi

rst=1
for ((i=2;i<=rst;i++)) ; do
  rst=$(echo $rst*$i | bc)
  rst=$(echo $rst | tr -d ["\\\n "])
done

echo "$n!=$rst"
