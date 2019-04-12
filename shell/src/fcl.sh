#!/bin/bash
set -e

lib_path="$(dirname $(readlink -f $0))/lib"
. "$lib_path/stdout.sh"


file_name="$1"
[[ -z "$file_name" ]] && {
  error "[arguments error]: Missing required parameters: file path."
  exit 1
}

[[ "${file_name:0:1}" = "/" ]] && file_path="$file_name" || file_path="$(pwd)/$file_name"

[[ ! -e "$file_path" ]] && {
  error "[arguments error]: File $file_name not found."
  exit 1
}

min_line="1"
max_line="$(sed -n '$=' $file_path)"
arg2="$2"
arg3="$3"
s_line="${arg2:-1}"
e_line="${arg3:-$max_line}"

expr $s_line + 0 &> /dev/null && expr $e_line + 0 &> /dev/null || {
  error "[arguments error]: The third or fourth arguments are not number."
  exit 1
}

([[ "$s_line" -gt "$e_line" ]] || [[ "$s_line" -gt "$max_line" ]] || [[ "$e_line" -lt "$min_line" ]]) && {
  error "[arguments error]: The third or fourth arguments are not legal integers."
  exit 1
}

if [ "$s_line" -lt "$min_line" ]
then
  s_line=$min_line
elif [ "$e_line" -gt "$max_line" ]
then
  e_line=$max_line
fi

sed -n "$s_line,$e_line p" $file_path
