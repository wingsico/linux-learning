#!/bin/bash

lib_path="$(dirname $(readlink -f $0))/lib"
. "$lib_path/stdout.sh"


file_name="$1"
if [ -z "$file_name" ]
then
  error "[arguments error]: Missing required parameters: file path."
  exit 1
fi

file_path="$(pwd)/$file_name"

if [ ! -e "$file_path" ]
then
  error "[arguments error]: File $file_name not found."
  exit 1
fi

min_line="1"
max_line="$(sed -n '$=' $file_path)"
arg2="$2"
arg3="$3"
s_line="${arg2:-1}"
e_line="${arg3:-$max_line}"

# 判断是否为整数数字
expr $s_line + 0 &> /dev/null
s_line_flag=$?
expr $e_line + 0 &>/dev/null
e_line_flag=$?

if [ ! "$s_line_flag" -eq 0 ] || [ ! "$e_line_flag" -eq 0 ]
then
  error "[arguments error]: The third or fourth arguments are not number."
  exit 1
fi

if [ "$s_line" -gt "$e_line" ] || [ "$s_line" -gt "$max_line" ] || [ "$e_line" -lt "$min_line" ]
then
  error "[arguments error]: The third or fourth arguments are not legal integers."
  exit 1
elif [ "$s_line" -lt "$min_line" ]
then
  s_line=$min_line
elif [ "$e_line" -gt "$max_line" ]
then
  e_line=$max_line
fi

sed -n "$s_line,$e_line p" $file_path

exit 0

