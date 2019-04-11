#! /bin/bash


lib_path="$(dirname $(readlink -f $0))/lib"
. "$lib_path/stdout.sh"


dir="$1"
dir="${dir:-./}"

if [ ! -e $dir ]
then
  error "cannot access \"$dir\": No such file or directory"
  exit 1
elif [ ! -d $dir ]
then
  error "\"$dir\": Not a directory"
fi

ls $dir -R -A | grep '^\.[^:]*' -o
